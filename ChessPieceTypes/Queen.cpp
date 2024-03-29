#include </home/zach/ZACH/ChessPieceTypes/Queen.h>

using namespace cp;

Queen::Queen(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Queen;

    m_MoveSet = {Point(1,1), Point(2,2), Point(3,3), Point(4,4), Point(5,5), Point(6,6), Point(7,7),
                 Point(-1,-1), Point(-2,-2), Point(-3,-3), Point(-4,-4), Point(-5,-5), Point(-6,-6), Point(-7,-7),
                 Point(-1,1), Point(-2,2), Point(-3,3), Point(-4,4), Point(-5,5), Point(-6,6), Point(-7,7),
                 Point(1,-1), Point(2,-2), Point(3,-3), Point(4,-4), Point(5,-5), Point(6,-6), Point(7,-7),
                 Point(0,1), Point(0,2), Point(0,3), Point(0,4), Point(0,5), Point(0,6), Point(0,7),
                 Point(0,-1), Point(0,-2), Point(0,-3), Point(0,-4), Point(0,-5), Point(0,-6), Point(0,-7),
                 Point(1,0), Point(2,0), Point(3,0), Point(4,0), Point(5,0), Point(6,0), Point(7,0),
                 Point(-1,0), Point(-2,0), Point(-3,0), Point(-4,0), Point(-5,0), Point(-6,0), Point(-7,0)};
}

vector<Point> Queen::getPossibleMoves()
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

            bool blocked = false;
            //-----check for blocked straight path-----
            if (desPoint.x == m_pos.x && desPoint.y < m_pos.y)
            {
                for (int i = m_pos.y; i > desPoint.y; i--)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(m_pos.x, i));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                }
            }
            else if (desPoint.x == m_pos.x && desPoint.y > m_pos.y)
            {
                for (int i = m_pos.y; i < desPoint.y; i++)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(m_pos.x, i));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                }
            }
            else if (desPoint.y == m_pos.y && desPoint.x < m_pos.x)
            {
                for (int i = m_pos.x; i > desPoint.x; i--)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(i, m_pos.y));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                }
            }
            else if (desPoint.y == m_pos.y && desPoint.x > m_pos.x)
            {
                for (int i = m_pos.x; i < desPoint.x; i++)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(i, m_pos.y));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                }
            }
            //-----check for blocked diagonal path-----
            else if (desPoint.x < m_pos.x && desPoint.y < m_pos.y)
            {
                int x = m_pos.x, y = m_pos.y;
                while (desPoint.x < x)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(x, y));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                    x--; y--;
                }
            }
            else if (desPoint.x < m_pos.x && desPoint.y > m_pos.y)
            {
                int x = m_pos.x, y = m_pos.y;
                while (desPoint.x < x)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(x, y));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                    x--; y++;
                }
            }
            else if (desPoint.x > m_pos.x && desPoint.y < m_pos.y)
            {
                int x = m_pos.x, y = m_pos.y;
                while (desPoint.x > x)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(x, y));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                    x++; y--;
                }
            }
            else if (desPoint.x > m_pos.x && desPoint.y > m_pos.y)
            {
                int x = m_pos.x, y = m_pos.y;
                while (desPoint.x > x)
                {
                    ChessPiece temp;
                    temp.GetPieceType(Point(x, y));
                    if (temp.m_pos != m_pos && temp.m_col != Color::blank)
                    {
                        blocked = true;
                        break;
                    }
                    x++; y++;
                }
            }

            if(occupant.m_col != this->m_col && blocked == false)
            {
                if(occupant.m_type != PieceType::King)
                    possibleMoves.push_back(desPoint);
            }
        }
    }

    return possibleMoves;
}

void Queen::moveTo(Point aDesPoint)
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
            
            gpioPWM(MAGNET_PIN, PWM_VAL);
            time_sleep(0.5);
            if((aDesPoint.x != this->m_pos.x && aDesPoint.y == this->m_pos.y) || (aDesPoint.x == this->m_pos.x && aDesPoint.y != this->m_pos.y)) // move straight
            {
                if(aDesPoint.x == this->m_pos.x)
                {
                    int ydiff = aDesPoint.y - this->m_pos.y;
                    if(ydiff > 0)
                    {
                        steppers->moveByMM(abs(ydiff)*fieldSize, Direction::Backwards);
                    }
                    else if(ydiff < 0)
                    {
                        steppers->moveByMM(abs(ydiff)*fieldSize, Direction::Forwards);
                    }
                }    
                else    
                {
                    int xdiff = aDesPoint.x - this->m_pos.x;
                    if(xdiff > 0)
                    {
                        steppers->moveByMM(abs(xdiff)*fieldSize, Direction::Right);
                    }
                    else if(xdiff < 0)
                    {
                        steppers->moveByMM(abs(xdiff)*fieldSize, Direction::Left);
                    }
                }   
            }
            else // move diagonal
            {
                int diff = aDesPoint.x - this->m_pos.x;
                printf("diff: %d\n", diff);
                float diagonal = abs(diff)*(sqrt(2*(fieldSize*fieldSize)));
                printf("diagonal: %d\n", diagonal);

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
            time_sleep(0.5);
            gpioWrite(MAGNET_PIN, PI_HIGH);

            // move virtually
            int neu, alt;
            for (neu = 0; neu < 64; neu++)
            {
                if ((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            delete (*playField)[neu];
            (*playField)[neu] = new Queen(m_col, aDesPoint);
            m_type = PieceType::none;
            m_col = Color::blank;
            
            steppers->currPoint = aDesPoint;
        }
    }
}
