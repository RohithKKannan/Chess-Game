#include "header.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
    delete board;
}

void GameManager::StartGame()
{
    bool playAgain = true;

    while (playAgain)
    {
        Game();

        cout << "Game complete!" << endl;

        char choice;

        cin.clear();

        cout << "Do you want to play again? (y/n): " << flush;
        cin >> choice;

        if (choice == 'n' || choice == 'N')
        {
            playAgain = false;
        }
    }
}

void GameManager::Game()
{
    bool isRunning = true;

    board = new Board();
    board->SetupBoard();

    currentGameState = WhiteTurn;

    while (isRunning)
    {
        board->ResetAllPieceInfo();

        board->PreprocessAllAttacks();

        board->SetAllLegalMoves();

        board->CheckForDraw();

        switch (currentGameState)
        {
        case WhiteTurn:
            if (!board->CheckIfAnyLegalMovesAvailable(currentGameState == WhiteTurn))
            {
                if (board->GetKing(currentGameState == WhiteTurn)->GetIsInCheck())
                {
                    cout << "White King is in check, and there are no other moves!" << endl;
                    currentGameState = BlackWins;
                    break;
                }
                else
                {
                    currentGameState = Stalemate;
                    cout << "No Legal moves available for " << (currentGameState == WhiteTurn ? "White " : "Black ") << endl;
                    break;
                }
            }

            InitiateTurn();
            currentGameState = BlackTurn;
            break;
        case BlackTurn:
            if (!board->CheckIfAnyLegalMovesAvailable(currentGameState == WhiteTurn))
            {
                if (board->GetKing(currentGameState == WhiteTurn)->GetIsInCheck())
                {
                    cout << "Black King is in check, and there are no other moves!" << endl;
                    currentGameState = WhiteWins;
                    break;
                }
                else
                {
                    currentGameState = Stalemate;
                    cout << "No Legal moves available for " << (currentGameState == WhiteTurn ? "White " : "Black ") << endl;
                    break;
                }
            }

            InitiateTurn();
            currentGameState = WhiteTurn;
            break;
        case Stalemate:
            cout << "Game ended in Stalemate!" << endl;
            isRunning = false;
            break;
        case WhiteWins:
            cout << "White wins the game!" << endl;
            isRunning = false;
            break;
        case BlackWins:
            cout << "Black wins the game!" << endl;
            isRunning = false;
            break;
        case Draw:
            cout << "The game ends in a Draw!" << endl;
            isRunning = false;
            break;
        }
    }

    delete board;
    board = nullptr;
}

void GameManager::InitiateTurn()
{
    while (true)
    {
        cout << (currentGameState == WhiteTurn ? "White's turn!" : "Black's turn!") << endl;

        board->DisplayBoard();

        // Get Input - Select Square
        selectedSquare = SelectSquare();

        // Select Piece
        if (selectedSquare->piece == NULL)
        {
            cout << "No piece found at square! Pick valid square!" << endl;
        }
        else
        {
            selectedPiece = selectedSquare->piece;

            if (selectedPiece->GetIsWhite() != currentGameState == WhiteTurn)
            {
                cout << "Select a square that has a " << (currentGameState == WhiteTurn ? "White" : "Black") << " piece!" << endl;
            }
            else if (selectedPiece->GetLegalPositionData()->numberOfPositions == 0)
            {
                cout << "Selected piece cant move! Pick valid square!" << endl;
            }
            else
            {
                break;
            }
        }
    };

    cout << "Square selected!";

    // Display Legal Moves
    board->MarkPositions(selectedPiece->GetLegalPositionData());

    Position *positions = selectedPiece->GetLegalPositionData()->legalPositions;

    while (true)
    {
        board->DisplayBoard();

        // Get Input - Destination Square
        selectedSquare = SelectSquare();

        bool isLegal = false;

        for (int i = 0; i < selectedPiece->GetLegalPositionData()->numberOfPositions; i++)
        {
            if (positions[i].row == selectedSquare->GetPosition().row && positions[i].col == selectedSquare->GetPosition().col)
            {
                isLegal = true;
                break;
            }
        }

        if (!isLegal)
        {
            cout << "Destination is not in legalPositions! Pick valid square!" << endl;
        }
        else
        {
            break;
        }
    }

    board->MovePieceToSquare(selectedPiece, selectedSquare->GetPosition().row, selectedSquare->GetPosition().col);

    board->UnMarkPositions();

    board->DisplayBoard();
}

Square *GameManager::SelectSquare()
{
    string input;
    int row, col;

    while (true)
    {
        cout << "Select a square (e.g., D5): ";
        cin >> input;

        if (ParseInput(&input, &row, &col))
        {
            cout << "Selected : " << row << " " << col << endl;

            selectedSquare = board->SelectSquare(row, col);

            if (selectedSquare == nullptr)
            {
                cout << "Select valid square! Try again." << endl;
            }
            else
            {
                break;
            }
        }
    }

    return selectedSquare;
}

bool GameManager::ParseInput(string *input, int *row, int *col)
{
    if (input->length() != 2 || (*input)[0] < 'A' || (*input)[0] > 'H' || (*input)[1] < '1' || (*input)[1] > '8')
    {
        return false;
    }

    *col = (*input)[0] - 'A';       // 'A' → 0, 'B' → 1, ..., 'H' → 7
    *row = ((*input)[1] - '0') - 1; // '1' → 0, '2' → 1, ..., '8' → 7

    return true;
}
