#ifndef ROOK_H
#define ROOK_H

#include </home/zach/ZACH/ChessPiece.h>

namespace cp
{
    class Rook : public ChessPiece
    {
        public:
            Rook(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
            void moveTo(Stepper steppers, Point aDesPoint);
    };
}

#endif