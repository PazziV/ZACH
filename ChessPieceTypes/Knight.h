#ifndef KNIGHT_H
#define KNIGHT_H

#include </home/zach/ZACH/ChessPiece.h>

namespace cp
{
    class Knight : public ChessPiece
    {
        public:
            Knight(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
            void moveTo(Stepper steppers, Point aDesPoint);
    };
}

#endif