#include "header.h"

int main()
{
    Board *board = new Board();
    board->ClearBoard();
    board->SetupBoard();

    board->DisplayBoard();

    // Select Square

    string input;
    cin >> input;

    if(input.length() != 2)
        return 0;
    
    int column = input[0] - 'A';
    int row = (input[1] - '0') - 1;

    Piece *selectedPiece = board->SelectSquare(row, column);

    if(selectedPiece == NULL)
        return 0;

    // Print Legal Moves

    LegalPositions *legalPositions = selectedPiece->GetLegalPositions(row, column);

    if(legalPositions == nullptr)
        return 0;

    board->MarkPositions(legalPositions);

    board->DisplayBoard();

    delete board;
}
