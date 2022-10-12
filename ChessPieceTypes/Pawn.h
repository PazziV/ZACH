#include <ChessPiece.h>

namespace cp
{
    class Pawn : ChessPiece
    {
        public:
            Pawn(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}