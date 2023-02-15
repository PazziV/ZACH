#include </home/zach/ZACH/ChessPieceTypes/King.h>

using namespace cp;

King::King(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::King;

    m_MoveSet = {Point(0,1), Point(0,-1), Point(1,0), Point(-1,0), Point(1,1), Point(-1,1), Point(1,-1), Point(-1,-1)};
}

vector<Point> King::getPossibleMoves()
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

void King::moveTo(Point aDesPoint)
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
            time_sleep(1);
            
            gpioWrite(MAGNET_PIN, PI_HIGH);
            if((aDesPoint.x != this->m_pos.x && aDesPoint.y == this->m_pos.y) || (aDesPoint.x == this->m_pos.x && aDesPoint.y != this->m_pos.y)) // move straight
            {
                if(aDesPoint.x == this->m_pos.x)
                {
                    if(aDesPoint.y > this->m_pos.y)
                    {
                        steppers->moveByMM(fieldSize, Direction::Backwards);
                    }
                    else if(aDesPoint.y < this->m_pos.y)
                    {
                        steppers->moveByMM(fieldSize, Direction::Forwards);
                    }
                }    
                else    
                {
                    if(aDesPoint.x > this->m_pos.x)
                    {
                        steppers->moveByMM(fieldSize, Direction::Right);
                    }
                    else if(aDesPoint.x < this->m_pos.x)
                    {
                        steppers->moveByMM(fieldSize, Direction::Left);
                    }
                }   
            }
            else // move diagonal
            {
                float diagonal = (sqrt(2*(fieldSize*fieldSize)));

                if(aDesPoint.x > this->m_pos.x)
                {
                    if(aDesPoint.y > this->m_pos.y)
                        steppers->moveByMM(diagonal, Direction::DiagonalRB);
                    else
                        steppers->moveByMM(diagonal, Direction::DiagonalRF);
                }
                else
                {
                    if(aDesPoint.y > this->m_pos.y)
                        steppers->moveByMM(diagonal, Direction::DiagonalLB);
                    else
                        steppers->moveByMM(diagonal, Direction::DiagonalLF);
                }
            }
            gpioWrite(MAGNET_PIN, PI_LOW);
            
            // move virtually
            int neu;
            for (neu = 0; neu < 64; neu++)
            {
                if ((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            delete (*playField)[neu];
            (*playField)[neu] = new King(m_col, aDesPoint);
            m_type = PieceType::none;
            m_col = Color::blank;
            
            steppers->currPoint = aDesPoint;
        }
    }
}