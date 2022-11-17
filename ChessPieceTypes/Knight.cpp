#include </home/zach/ZACH/ChessPieceTypes/Knight.h>

using namespace cp;

Knight::Knight(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Knight;

    m_MoveSet = {Point(1,2), Point(2,1), Point(-1,2), Point(-2,1), Point(-1,-2), Point(-2,-1), Point(1,-2), Point(2,-1)};
}

vector<Point> Knight::getPossibleMoves()
{
    vector<Point> possibleMoves;
    Point desPoint; // Destination Point

    for(int a = 0; a < m_MoveSet.size(); a++)
    {
        desPoint = m_pos + m_MoveSet[a];
        if(desPoint.x <= 7 && desPoint.x >= 0 && desPoint.y <= 7 && desPoint.y >= 0)
        {
            ChessPiece occupant;
            occupant.GetPieceType(desPoint);

            if(occupant.m_col != this->m_col)
            {
                if(occupant.m_type != PieceType::King)
                    possibleMoves.push_back(desPoint);
            }
        }
    }

    return possibleMoves;
}

void Knight::moveTo(Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves();
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
        {
            int ydiff = aDesPoint.y - this->m_pos.y;
            int xdiff = aDesPoint.x - this->m_pos.x;
            int diagonal = round((sqrt(2*(fieldSize*fieldSize))));

            // ****** Move diagonal to first corner ******
            if(xdiff > 0 && ydiff < 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalRF);
            }
            else if(xdiff > 0 && ydiff > 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalRB);
            }
            else if(xdiff < 0 && ydiff > 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalLB);
            }
            else if(xdiff < 0 && ydiff < 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalLF);
            }

            // ****** Move straight to next corner ******
            if(abs(xdiff) > abs(ydiff) && xdiff > 0)
            {
                steppers->moveByMM(fieldSize, Direction::Right);
            }
            else if(abs(xdiff) > abs(ydiff) && xdiff < 0)
            {
                steppers->moveByMM(fieldSize, Direction::Left);
            }
            else if(abs(xdiff) < abs(ydiff) && ydiff < 0)
            {
                steppers->moveByMM(fieldSize, Direction::Forwards);
            }
            else if(abs(xdiff) < abs(ydiff) && ydiff < 0)
            {
                steppers->moveByMM(fieldSize, Direction::Backwards);
            }

            // ****** Move diagonal to center of field ******
            if(xdiff > 0 && ydiff < 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalRF);
            }
            else if(xdiff > 0 && ydiff > 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalRB);
            }
            else if(xdiff < 0 && ydiff > 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalLB);
            }
            else if(xdiff < 0 && ydiff < 0)
            {
                steppers->moveByMM(diagonal/2, Direction::DiagonalLF);
            }

            this->m_pos = aDesPoint;
        } 
    }
}