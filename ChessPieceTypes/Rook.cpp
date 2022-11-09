#include </home/zach/ZACH/ChessPieceTypes/Rook.h>

using namespace cp;

Rook::Rook(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Rook;

    m_MoveSet = {Point(0,1), Point(0,2), Point(0,3), Point(0,4), Point(0,5), Point(0,6), Point(0,7),
                 Point(0,-1), Point(0,-2), Point(0,-3), Point(0,-4), Point(0,-5), Point(0,-6), Point(0,-7),
                 Point(1,0), Point(2,0), Point(3,0), Point(4,0), Point(5,0), Point(6,0), Point(7,0),
                 Point(-1,0), Point(-2,0), Point(-3,0), Point(-4,0), Point(-5,0), Point(-6,0), Point(-7,0)};
}

vector<Point> Rook::getPossibleMoves(vector<ChessPiece> aPlayfield)
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

void Rook::moveTo(Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves(aPlayfield);
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
        {
            if(aDesPoint.x != this.m_pos.x)
            {
                int ydiff = aDesPoint.y - this.m_pos.y;
                if(ydiff > 0)
                {
                    Stepper::moveByMM(abs(ydiff)*ChessPiece::fieldSize, Direction::Backwards);
                }
                else if(ydiff < 0)
                {
                    Stepper::moveByMM(abs(ydiff)*ChessPiece::fieldSize, Direction::Forwards);
                }
            }    
            else
            {
                int xdiff = aDesPoint.x - this.m_pos.x;
                if(xdiff > 0)
                {
                    Stepper::moveByMM(abs(xdiff)*ChessPiece::fieldSize, Direction::Right);
                }
                else if(xdiff < 0)
                {
                    Stepper::moveByMM(abs(xdiff)*ChessPiece::fieldSize, Direction::Left);
                }
            }    
        }
    }
}