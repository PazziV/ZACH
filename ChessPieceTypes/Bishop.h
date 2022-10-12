#include <ChessPiece.h>

namespace cp
{
    class Bishop : ChessPiece
    {
        public:
            Bishop(Color aCol, Point aPos);
            vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
    };
}