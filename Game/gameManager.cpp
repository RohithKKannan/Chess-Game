#include <iostream>

#include "../Core/core.h"
#include "gameManager.h"
#include "../Board/square.h"
#include "../Board/board.h"
#include "../Pieces/piece.h"

using namespace std;

GameManager::GameManager()
{
	currentGameState = WhiteTurn;
	currentInputState = Idle;
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
	
	currentGameState = Menu;
}

void GameManager::Update(spn::Canvas* canvas)
{
	switch(currentGameState)
	{
		case Menu:
			canvas->DrawText("2D Chess Game", 100, 50);
			canvas->DrawText("Click to Start", 100, 70);
			break;
		case WhiteTurn:
		case BlackTurn: 
			canvas->DrawText(currentGameState == WhiteTurn ? "White's Turn" : "Black's Turn", 100, 50);
			board->DisplayBoard(canvas);
			break;
		case Stalemate:
			canvas->DrawText("Stalemate! Game Over!", 100, 50);
			break;
		case WhiteWins:
		case BlackWins:
			canvas->DrawText(currentGameState == WhiteWins ? "White Wins!" : "Black Wins!", 100, 50);
			break;
		case Draw:
			canvas->DrawText("It's a Draw!", 100, 50);
	}
}

void GameManager::ProcessInput(const SDL_Event* event)
{
	switch (event->type) {
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (event->button.button == SDL_BUTTON_LEFT) {
//				std::cout << "left: ";
				ProcessMouseClick(event->motion.x, event->motion.y);
			}
			else if (event->button.button == SDL_BUTTON_RIGHT) {
//				std::cout << "right : ";
			}
//			std::cout << event->motion.x <<", " << event->motion.y << "\n";
			return;
		default:
			return;
	}
}

void GameManager::GUIStartGame()
{
    currentGameState = WhiteTurn;
    
    GUIInitiateTurn();
}

void GameManager::GUIInitiateTurn()
{
	board->ResetAllPieceInfo();

    board->PreprocessAllPieceAttacks();

    board->SetAllPieceLegalMoves();

    board->TrackBoardState(board->GetBoardState());

    if (board->CheckForDraw())
    {
    	currentGameState = GameState::Draw;
    	return;
	}
	
	switch (currentGameState)
    {
    case WhiteTurn:
        if (!board->CheckIfAnyLegalMovesAvailable(currentGameState == GameState::WhiteTurn))
        {
            if (board->GetKing(currentGameState == GameState::WhiteTurn)->GetIsInCheck())
            {
                cout << "White King is in check, and there are no other moves!" << endl;
                currentGameState = GameState::BlackWins;
                return;
            }
            else
            {
                currentGameState = GameState::Stalemate;
                cout << "No Legal moves available for " << (currentGameState == GameState::WhiteTurn ? "White " : "Black ") << endl;
                return;
            }
        }

        board->ResetPawnsTwoStepsMove(false);
        currentGameState = GameState::BlackTurn;
        currentInputState = WaitingForSourceSelect;
        return;
        
    case BlackTurn:
        if (!board->CheckIfAnyLegalMovesAvailable(currentGameState == GameState::WhiteTurn))
        {
            if (board->GetKing(currentGameState == GameState::WhiteTurn)->GetIsInCheck())
            {
                cout << "Black King is in check, and there are no other moves!" << endl;
                currentGameState = GameState::WhiteWins;
                return;
            }
            else
            {
                currentGameState = GameState::Stalemate;
                cout << "No Legal moves available for " << (currentGameState == GameState::WhiteTurn ? "White " : "Black ") << endl;
                return;
            }
        }

        board->ResetPawnsTwoStepsMove(true);
        currentGameState = GameState::WhiteTurn;
        currentInputState = WaitingForSourceSelect;
        return;
    }
}

void GameManager::GUIEndGame()
{
	
}

void GameManager::ProcessMouseClick(int xCoord, int yCoord)
{
	if(currentGameState == Menu)
		GUIStartGame();
	else if(currentGameState == WhiteTurn || currentGameState == BlackTurn)
		SelectSquareAt(xCoord, yCoord);
}

void GameManager::SelectSquareAt(int xCoord, int yCoord)
{
	Square* square = board->GetSquareAtCoords(xCoord, yCoord);
	
	if(currentInputState == WaitingForSourceSelect)
	{
		SourceSelected(square);
	}
	else if(currentInputState == WaitingForDestinationSelect)
	{
		DestinationSelected(square);
	}
}

void GameManager::SourceSelected(Square* square)
{
	Piece* piece = nullptr;
	
	piece = square->GetPiece();
	
	if(piece == nullptr)
	{
		cout << "Selected square is empty! Select valid source";
	}
	else
	{
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
        	PieceSelected(piece);
		}
	}
}

void GameManager::PieceSelected(Piece* piece)
{
	
}

void GameManager::DestinationSelected(Square* square)
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
