#ifndef BISHOP_H
#define BISHOP_H

#include </home/zach/ZACH/ChessPiece.h>

namespace cp
{
    class Bishop : public ChessPiece
    {
        public:
            Bishop(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}

#endif