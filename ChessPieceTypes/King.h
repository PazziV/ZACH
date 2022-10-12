#ifndef KING_H
#define KING_H

#include </home/zach/ZACH/ChessPiece.h>

namespace cp
{
    class King : public ChessPiece
    {
        public:
            King(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}

#endif