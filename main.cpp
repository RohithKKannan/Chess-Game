#include "header.h"

int main()
{
    Board *board = new Board();
    board->ClearBoard();
    board->SetupBoard();

    board->DisplayBoard();

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

    Piece *selectedPiece = board->SelectSquare(row, col);

    if(selectedPiece == NULL)
    {
        cout << "No piece found at selected square!" << endl;
        return 0;
    }

    // Print Legal Moves

    LegalPositions *legalPositions = selectedPiece->GetLegalPositions(row, col);

    if(legalPositions == nullptr)
        return 0;

    board->MarkPositions(legalPositions);

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

    Position* positions = legalPositions->positions;

    bool isLegal = false;

    for(int i = 0; i < legalPositions->numberOfPositions; i++)
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
        return 0;
    }

    board->MovePieceToSquare(selectedPiece, row, col);

    board->DisplayBoard();

    delete board;
}
