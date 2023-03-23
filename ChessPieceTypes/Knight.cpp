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
            ChessPiece occupant;
            occupant.GetPieceType(aDesPoint);

            if(occupant.m_col != Color::blank)
                occupant.removeCapturedPiece();
                
            steppers->moveToPoint(m_pos);
            time_sleep(0.5);

            int ydiff = aDesPoint.y - this->m_pos.y;
            int xdiff = aDesPoint.x - this->m_pos.x;
            float diagonal = (sqrt(2*(fieldSize*fieldSize)));

            gpioWrite(MAGNET_PIN, PI_LOW);
            time_sleep(0.5);
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
            gpioWrite(MAGNET_PIN, PI_HIGH);
            time_sleep(0.5);

            // move virtually
            int neu;
            for (neu = 0; neu < 64; neu++)
            {
                if ((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            delete (*playField)[neu];
            (*playField)[neu] = new Knight(m_col, aDesPoint);
            m_type = PieceType::none;
            m_col = Color::blank;
            
            steppers->currPoint = aDesPoint;
        } 
    }
}