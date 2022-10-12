#include <ChessPiece.h>

namespace cp
{
    class Rook : ChessPiece
    {
        public:
            Rook(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}