#pragma once

class Board;

class Command
{
    protected:
        Board* board;
    public:
        Command(Board *board) 
        {
            this->board = board;
        };
        virtual ~Command() {};

        virtual bool Execute() = 0;
        virtual bool Undo() = 0;
};
