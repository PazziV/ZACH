#ifndef PAWN_H
#define PAWN_H

#include </home/zach/ZACH/ChessPiece.h>

namespace cp
{
    class Pawn : public ChessPiece
    {
        public:
            Pawn(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(array<ChessPiece*, 64> aPlayfield);
            void moveTo(Point aDesPoint);
    };
}

#endif