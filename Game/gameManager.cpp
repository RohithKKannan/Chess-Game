#include <iostream>

#include "../Core/core.h"
#include "gameManager.h"
#include "../Board/square.h"
#include "../Board/board.h"
#include "../Pieces/piece.h"

using namespace std;

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
        if(!Game())
            return;

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

bool GameManager::Game()
{
    bool isRunning = true;

    board = new Board();
    board->SetupBoard();

    currentGameState = GameState::WhiteTurn;

    while (isRunning)
    {
        board->ResetAllPieceInfo();

        board->PreprocessAllPieceAttacks();

        board->SetAllPieceLegalMoves();

        board->TrackBoardState(board->GetBoardState());

        if (board->CheckForDraw())
            currentGameState = GameState::Draw;

        switch (currentGameState)
        {
        case WhiteTurn:
            if (!board->CheckIfAnyLegalMovesAvailable(currentGameState == GameState::WhiteTurn))
            {
                if (board->GetKing(currentGameState == GameState::WhiteTurn)->GetIsInCheck())
                {
                    cout << "White King is in check, and there are no other moves!" << endl;
                    currentGameState = GameState::BlackWins;
                    break;
                }
                else
                {
                    currentGameState = GameState::Stalemate;
                    cout << "No Legal moves available for " << (currentGameState == GameState::WhiteTurn ? "White " : "Black ") << endl;
                    break;
                }
            }

            if(!InitiateTurn())
                return false;

            board->ResetPawnsTwoStepsMove(false);
            currentGameState = GameState::BlackTurn;
            break;
        case BlackTurn:
            if (!board->CheckIfAnyLegalMovesAvailable(currentGameState == GameState::WhiteTurn))
            {
                if (board->GetKing(currentGameState == GameState::WhiteTurn)->GetIsInCheck())
                {
                    cout << "Black King is in check, and there are no other moves!" << endl;
                    currentGameState = GameState::WhiteWins;
                    break;
                }
                else
                {
                    currentGameState = GameState::Stalemate;
                    cout << "No Legal moves available for " << (currentGameState == GameState::WhiteTurn ? "White " : "Black ") << endl;
                    break;
                }
            }

            if(!InitiateTurn())
                return false;

            board->ResetPawnsTwoStepsMove(true);
            currentGameState = GameState::WhiteTurn;
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

    return true;
}

bool GameManager::InitiateTurn()
{
    while (true)
    {
        cout << (currentGameState == WhiteTurn ? "White's turn!" : "Black's turn!") << endl;

        board->DisplayBoard();

        // Get Input - Select Square
        selectedSquare = SelectSquareFromInput();

        // Select Piece
        if (selectedSquare->GetPiece() == NULL)
        {
            cout << "No piece found at square! Pick valid square!" << endl;
        }
        else
        {
            selectedPiece = selectedSquare->GetPiece();

            if (selectedPiece->GetIsWhite() != (currentGameState == WhiteTurn))
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
        selectedSquare = SelectSquareFromInput();

        bool isLegal = false;

        for (int i = 0; i < selectedPiece->GetLegalPositionData()->numberOfPositions; i++)
        {
            if (positions[i].row == selectedSquare->GetPosition()->row && positions[i].col == selectedSquare->GetPosition()->col)
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

    if(!board->MovePieceToSquare(selectedPiece, selectedSquare->GetPosition()->row, selectedSquare->GetPosition()->col))
    {
        cout << "Error moving piece!" << endl;
        return false;
    }

    board->ExecuteCommands();

    board->UnMarkPositions();

    board->DisplayBoard();

    return true;
}

void GameManager::InitGame()
{
	board = new Board();
	board->SetupBoard();
}

void GameManager::Update(spn::Canvas* canvas)
{
	board->DisplayBoard(canvas);
}

void GameManager::ProcessInput(const SDL_Event* sdl_event)
{
	
}

Square *GameManager::SelectSquareFromInput()
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

            selectedSquare = board->GetSquare(row, col);

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
    *row = (*input)[1] - '1';       // '1' → 0, '2' → 1, ..., '8' → 7

    return true;
}
