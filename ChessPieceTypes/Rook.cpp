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

vector<Point> Rook::getPossibleMoves()
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

void Rook::moveTo(Point aDesPoint)
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
            
            gpioWrite(MAGNET_PIN, PI_LOW);
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
            gpioWrite(MAGNET_PIN, PI_HIGH);

             // move virtually
            int neu;
            for (neu = 0; neu < 64; neu++)
            {
                if ((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            delete (*playField)[neu];
            (*playField)[neu] = new Rook(m_col, aDesPoint);
            m_type = PieceType::none;
            m_col = Color::blank;
            
            steppers->currPoint = aDesPoint;
        }
    }
}