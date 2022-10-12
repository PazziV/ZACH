#include <ChessPiece.h>

namespace cp
{
    class Knight : ChessPiece
    {
        public:
            Knight(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}