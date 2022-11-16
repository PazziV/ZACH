#ifndef ROOK_H
#define ROOK_H

#include </home/zach/ZACH/ChessPiece.h>

namespace cp
{
    class Rook : public ChessPiece
    {
        public:
            Rook(Color aCol, Point aPos);
            vector<Point> getPossibleMoves();
            void moveTo(Point aDesPoint);
    };
}

#endif