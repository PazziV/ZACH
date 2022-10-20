#include </home/zach/ZACH/ChessPieceTypes/Pawn.h>

using namespace cp;

Pawn::Pawn(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Pawn;

    m_MoveSet = {Point(0,2), Point(0,1), Point(1,1), Point(-1,1)};
}

vector<Point> Pawn::getPossibleMoves(array<ChessPiece*, 64> aPlayfield)
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

void Pawn::moveTo(array<ChessPiece*, 64> aPlayfield, Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves(aPlayfield);
    bool isPossible = false;
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
            isPossible = true;
    }

    if(isPossible == true)
    {

    }
    else
        return;
}