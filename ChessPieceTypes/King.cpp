#include </home/zach/ZACH/ChessPieceTypes/King.h>

using namespace cp;

King::King(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::King;

    m_MoveSet = {Point(0,1), Point(0,-1), Point(1,0), Point(-1,0), Point(1,1), Point(-1,1), Point(1,-1), Point(-1,-1)};
}

vector<Point> King::getPossibleMoves(vector<ChessPiece> aPlayfield)
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

void King::moveTo(array<ChessPiece*, 64> aPlayfield, Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves(aPlayfield);
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
            this.m_pos = aDesPoint;
    }
}