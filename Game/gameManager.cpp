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

	if(!whiteQueenImage.CreateFromPng("res/Game/queen.png"))
		std::cout << "Error creating image for piece! W Queen" << std::endl;
	
	if(!blackQueenImage.CreateFromPng("res/Game/queen1.png"))
		std::cout << "Error creating image for piece! B Queen" << std::endl;
			
	if(!whiteBishopImage.CreateFromPng("res/Game/bishop.png"))
		std::cout << "Error creating image for piece! W Bishop" << std::endl;
		
	if(!blackBishopImage.CreateFromPng("res/Game/bishop1.png"))
		std::cout << "Error creating image for piece! B Bishop" << std::endl;
		
	if(!whiteKnightImage.CreateFromPng("res/Game/knight.png"))
		std::cout << "Error creating image for piece! W Knight" << std::endl;
	
	if(!blackKnightImage.CreateFromPng("res/Game/knight1.png"))
		std::cout << "Error creating image for piece! B Knight" << std::endl;
		
	if(!whiteRookImage.CreateFromPng("res/Game/rook.png"))
		std::cout << "Error creating image for piece! W Rook" << std::endl;
	
	if(!blackRookImage.CreateFromPng("res/Game/rook1.png"))
		std::cout << "Error creating image for piece! B Rook" << std::endl;
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

    board = new Board(this);
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

void GameManager::InitGame()
{
	board = new Board(this);
	board->SetupBoard();
	
	currentGameState = Menu;
}

void GameManager::Update(spn::Canvas* canvas)
{
	canvas->Clear();
	switch(currentGameState)
	{
		case Menu:
			canvas->DrawText("2D Chess Game", 100, 50);
			canvas->DrawText("Click to Start", 100, 70);
			break;
		case WhiteTurn:
		case BlackTurn: 
			canvas->DrawText(currentGameState == WhiteTurn ? "White's Turn" : "Black's Turn", 500, 50);
			canvas->EnableAlphaBlending(currentInputState == WaitingForDestinationSelect);
			board->DisplayBoard(canvas);
			if(currentInputState == WaitingForPromotionSelect)
				DisplayPromotionPopup(canvas);
			break;
		case Stalemate:
			canvas->DrawText("Stalemate! Game Over!", 100, 50);
			canvas->DrawText("Click to play again", 100, 70);
			break;
		case WhiteWins:
		case BlackWins:
			canvas->DrawText(currentGameState == WhiteWins ? "White Wins!" : "Black Wins!", 100, 50);
			canvas->DrawText("Click to play again", 100, 70);
			break;
		case Draw:
			canvas->DrawText("It's a Draw!", 100, 50);
			canvas->DrawText("Click to play again", 100, 70);
			break;
		case Error:
			canvas->DrawText("Error!", 100, 50);
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
    
    currentInputState = Idle;
    
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
        
        cout << "White's Turn" << endl;

//        board->ResetPawnsTwoStepsMove(false);
//        currentGameState = GameState::BlackTurn;

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
        
        cout << "Black's Turn" << endl;

//        board->ResetPawnsTwoStepsMove(true);
//        currentGameState = GameState::WhiteTurn;

        currentInputState = WaitingForSourceSelect;
        return;
    }
}

void GameManager::GUIEndGame()
{
	delete board;
	
	InitGame();
}

void GameManager::ProcessMouseClick(int xCoord, int yCoord)
{
	if(currentGameState == Menu)
		GUIStartGame();
	else if(currentGameState == WhiteTurn || currentGameState == BlackTurn)
		SelectSquareAt(xCoord, yCoord);
	else
		GUIEndGame();
}

void GameManager::SelectSquareAt(int xCoord, int yCoord)
{
	if(currentInputState == WaitingForPromotionSelect)
	{
		PromotePieceSelected(xCoord, yCoord);
		return;
	}
			
	Square* square = board->GetSquareAtCoords(xCoord, yCoord);
	
	if(square == nullptr)
		return;
	
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
		cout << "Selected square is empty! Select valid source" << endl;
	}
	else
	{
		cout << "Piece selected : " << endl;
    	piece->PrintPiece();
    	cout << endl;
			
		if (piece->GetIsWhite() != (currentGameState == WhiteTurn))
        {
            cout << "Select a square that has a " << (currentGameState == WhiteTurn ? "White" : "Black") << " piece!" << endl;
        }
        else if (piece->GetLegalPositionData()->numberOfPositions == 0)
        {
        	cout << "selected piece Legal move count : " << piece->GetLegalPositionData()->numberOfPositions << endl;
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
	selectedPiece = piece;
	
	board->MarkPositions(selectedPiece->GetLegalPositionData());
	
	currentInputState = WaitingForDestinationSelect;
}

void GameManager::DestinationSelected(Square* square)
{
	selectedSquare = square;
	
	Position *positions = selectedPiece->GetLegalPositionData()->legalPositions;
	
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
        selectedSquare = nullptr;
        return;
    }
    
    currentInputState = Idle;
    
    if(board->MovePieceToSquare(selectedPiece, selectedSquare->GetPosition()->row, selectedSquare->GetPosition()->col))
    {
    	MoveComplete();
    }
    else
    {
    	cout << "Error moving piece!" << endl;
        currentGameState = Error;
        return;
	}
}

void GameManager::MoveComplete()
{
	if(!board->ExecuteCommands())
		return;

    board->UnMarkPositions();
    
    if(currentInputState == WaitingForPromotionSelect)
    	return;
    
    if(currentGameState == WhiteTurn)
    {
    	board->ResetPawnsTwoStepsMove(false);
    	currentGameState = BlackTurn;
	}
	else if(currentGameState == BlackTurn)
	{
		board->ResetPawnsTwoStepsMove(true);
		currentGameState = WhiteTurn;
	}

	GUIInitiateTurn();
}

void GameManager::InitiatePromotePawn()
{
	currentInputState = WaitingForPromotionSelect;
}

void GameManager::PromotePieceSelected(int xCoord, int yCoord)
{
	cout << "Promoting Piece at : " << xCoord << " " << yCoord << endl;
	
	int offset = 10;
	int tileSize = 60;
	
	int xPos, yPos;
	xPos = xCoord / tileSize;
	
	int screenY = yCoord / tileSize;
	yPos = BOARD_SIZE - 1 - screenY;
	
	cout << "Translated to : " << xPos << " " << yPos << " " << endl;
	
	if(xPos == 8)
	{
		switch(yPos)
		{
			case 5: board->PromotePawn(PieceType::Queen); break;
			case 4: board->PromotePawn(PieceType::Rook); break;
			case 3: board->PromotePawn(PieceType::Bishop); break;
			case 2: board->PromotePawn(PieceType::Knight); break;
		}
	}
}

void GameManager::DisplayPromotionPopup(spn::Canvas* canvas)
{
	canvas->DrawText("Choose a piece", 500, 70);
	canvas->DrawText("to promote to:", 500, 90);
	
	bool isWhite = currentGameState == WhiteTurn;
	
	int xPos, yPos;
		
	int offset = 10;
	
	int tileSize = 60;
	
	// Queen
	xPos = 8;
	yPos = 2;
	
	xPos = (xPos * tileSize) + offset;
	yPos = (yPos * tileSize) + offset;
	canvas->DrawImage(isWhite ? &whiteQueenImage : &blackQueenImage, xPos, yPos);
	
	// Rook
	yPos = 3;
	
	yPos = (yPos * tileSize) + offset;
	canvas->DrawImage(isWhite ? &whiteRookImage : &blackRookImage, xPos, yPos);
	
	// Bishop
	yPos = 4;
	
	yPos = (yPos * tileSize) + offset;
	canvas->DrawImage(isWhite ? &whiteBishopImage : &blackBishopImage, xPos, yPos);
	
	// Knight
	yPos = 5;
	
	yPos = (yPos * tileSize) + offset;
	canvas->DrawImage(isWhite ? &whiteKnightImage : &blackKnightImage, xPos, yPos);
}

void GameManager::PromotionComplete()
{
	board->ExecuteCommands();
		
	currentInputState = Idle;
	
	if(currentGameState == WhiteTurn)
    {
    	board->ResetPawnsTwoStepsMove(false);
    	currentGameState = BlackTurn;
	}
	else if(currentGameState == BlackTurn)
	{
		board->ResetPawnsTwoStepsMove(true);
		currentGameState = WhiteTurn;
	}

	GUIInitiateTurn();
}
