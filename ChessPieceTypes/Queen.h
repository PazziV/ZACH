#include <ChessPiece.h>

namespace cp
{
    class Queen : ChessPiece
    {
        public:
            Queen(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}