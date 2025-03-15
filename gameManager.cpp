#include "header.h"

GameManager::GameManager()
{
    board = new Board();
}

GameManager::~GameManager()
{
    delete board;
}

void GameManager::StartGame()
{
    board->ClearBoard();
    board->SetupBoard();

    board->DisplayBoard();

    isWhitesTurn = true;

    string input;
    int row, col;

    // Select Square
    
    cout << "Select a square : ";
    cin >> input;

    while(input.length() != 2)
    {
        cout << "Invalid input! Retry : ";
        cin >> input;
    }
    
    col = input[0] - 'A';
    row = (input[1] - '0') - 1;

    selectedPiece = board->SelectSquare(row, col);

    if(selectedPiece == NULL)
    {
        cout << "No piece found at selected square!" << endl;
        return;
    }

    // Print Legal Moves
    
    selectedPiece->RefreshLegalPositions(board);

    LegalPositionData* legalPositionData = selectedPiece->GetLegalPositionData();

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

    if(legalPositionData->numberOfPositions == 0)
    {
        cout << "No more moves!" << endl;
        return;
    }

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
