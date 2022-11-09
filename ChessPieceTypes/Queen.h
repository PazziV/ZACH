#ifndef QUEEN_H
#define QUEEN_H

#include </home/zach/ZACH/ChessPiece.h>

namespace cp
{
    class Queen : public ChessPiece
    {
        public:
            Queen(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
            void moveTo(Point aDesPoint);
    };
}

#endif