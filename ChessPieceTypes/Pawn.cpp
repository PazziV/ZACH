#include </home/zach/ZACH/ChessPieceTypes/Pawn.h>

using namespace cp;

Pawn::Pawn(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Pawn;

    m_MoveSet = {Point(0,2), Point(0,1), Point(1,1), Point(-1,1)};
}

vector<Point> Pawn::getPossibleMoves(vector<ChessPiece> aPlayfield)
{
    //only standard moves, no "en passant" (maybe at a later point)
    vector<Point> possibleMoves;
    Point desPoint; // Destination Point

    for(int a = 0; a < m_MoveSet.size(); a++)
    {
        desPoint = m_pos + m_MoveSet[a];
        if(desPoint.x <= 7 && desPoint.x >= 0 && desPoint.y <= 7 && desPoint.y >= 0)
        {
            ChessPiece occupant;
            occupant.GetPieceType(aPlayfield, desPoint);

            if(occupant.m_col != this->m_col)
            {
                if(occupant.m_type != PieceType::King)
                    possibleMoves.push_back(desPoint);
            }
        }
    }

    return possibleMoves;
}