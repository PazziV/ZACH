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

            //move virtually
            int alt, neu;
            for(alt = 0; alt < 64; alt++)
            {
                if((*playField)[alt]->m_pos == this->m_pos)
                    break;
            }
            printf("alt: %d\n", alt);
            printf("ALTpos: %d/%d\n", (*playField)[alt]->m_pos.x, (*playField)[alt]->m_pos.y);
            Point oldPos = (*playField)[alt]->m_pos;
            for(neu = 0; neu < 64; neu++)
            {
                if((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            printf("neu: %d\n", neu);
            printf("NEUpos: %d/%d\n", (*playField)[neu]->m_pos.x, (*playField)[neu]->m_pos.y);

            printf("THISpos: %d/%d\n", this->m_pos.x, this->m_pos.y);
            this->m_pos = aDesPoint;
            (*playField)[alt]->m_pos = oldPos;
            printf("ALT=>Type: %d, Col: %d, Pos: %d/%d\n", (*playField)[alt]->m_type, (*playField)[alt]->m_col,
                                                           (*playField)[alt]->m_pos.x, (*playField)[alt]->m_pos.y);
            printf("THISpos: %d/%d\n", this->m_pos.x, this->m_pos.y);
            (*playField)[neu] = this;
            printf("THIS=>Type: %d, Col: %d, Pos: %d/%d\n", this->m_type, this->m_col, this->m_pos.x, this->m_pos.y);
            printf("NEU=>Type: %d, Col: %d, Pos: %d/%d\n", (*playField)[neu]->m_type, (*playField)[neu]->m_col,
                                                           (*playField)[neu]->m_pos.x, (*playField)[neu]->m_pos.y);
            (*playField)[alt]->m_type = PieceType::none;
            (*playField)[alt]->m_col = Color::blank;
            printf("ALT=>Type: %d, Col: %d, Pos: %d/%d\n", (*playField)[alt]->m_type, (*playField)[alt]->m_col,
                                                           (*playField)[alt]->m_pos.x, (*playField)[alt]->m_pos.y);
            
            steppers->currPoint = this->m_pos; 
        }
    }
}