#include </home/zach/ZACH/ChessPieceTypes/Knight.h>

using namespace cp;

Knight::Knight(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Knight;

    m_MoveSet = {Point(1,2), Point(2,1), Point(-1,2), Point(-2,1), Point(-1,-2), Point(-2,-1), Point(1,-2), Point(2,-1)};
}

vector<Point> Knight::getPossibleMoves(vector<ChessPiece> aPlayfield)
{
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

void Knight::moveTo(array<ChessPiece*, 64> aPlayfield, Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves(aPlayfield);
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
            this.m_pos = aDesPoint;
    }
}