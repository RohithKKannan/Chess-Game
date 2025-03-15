#include "header.h"

GameManager::GameManager()
{
    board = new Board();
    legalPositionData = new LegalPositionData();
}

GameManager::~GameManager()
{
    delete board;
    delete legalPositionData;
}

void GameManager::StartGame()
{
    board->ClearBoard();
    board->SetupBoard();

    board->DisplayBoard();

    isWhitesTurn = true;

    string input;

    // Select Square
    
    cout << "Select a square : ";
    cin >> input;

    while(input.length() != 2)
    {
        cout << "Invalid input! Retry : ";
        cin >> input;
    }
    
    int col = input[0] - 'A';
    int row = (input[1] - '0') - 1;

    selectedPiece = board->SelectSquare(row, col);

    if(selectedPiece == NULL)
    {
        cout << "No piece found at selected square!" << endl;
        return;
    }

    // Print Legal Moves
    
    selectedPiece->GetLegalPositions(row, col, board, legalPositionData);

    board->MarkPositions(legalPositionData);

    board->DisplayBoard();

    board->UnMarkPositions();

    // Get Destination square

    cout << "Select a destination square : ";
    cin >> input;

    while(input.length() != 2)
    {
        cout << "Invalid input! Retry : ";
        cin >> input;
    }

    col = input[0] - 'A';
    row = (input[1] - '0') - 1;

    Position* positions = legalPositionData->legalPositions;

    bool isLegal = false;

    for(int i = 0; i < legalPositionData->numberOfPositions; i++)
    {
        if(positions[i].row == row && positions[i].col == col)
        {
            isLegal = true; 
            break;
        }
    }

    if(!isLegal)
    {
        cout << "Destination is not in legalPositions!" << endl;
        return;
    }

    board->MovePieceToSquare(selectedPiece, row, col);

    board->DisplayBoard();
}

void GameManager::InitiateTurn()
{

}
