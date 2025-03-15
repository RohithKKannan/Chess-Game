#include "header.h"

int main()
{
    GameManager *gameManager = new GameManager();

    gameManager->StartGame();

    delete gameManager;
}
