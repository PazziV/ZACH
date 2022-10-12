#include <ChessPiece.h>

namespace cp
{
    class King : ChessPiece
    {
        public:
            King(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}