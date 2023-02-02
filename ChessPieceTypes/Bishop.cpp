#include </home/zach/ZACH/ChessPieceTypes/Bishop.h>

using namespace cp;

Bishop::Bishop(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Bishop;

    m_MoveSet = {Point(1,1), Point(2,2), Point(3,3), Point(4,4), Point(5,5), Point(6,6), Point(7,7),
                 Point(-1,-1), Point(-2,-2), Point(-3,-3), Point(-4,-4), Point(-5,-5), Point(-6,-6), Point(-7,-7),
                 Point(-1,1), Point(-2,2), Point(-3,3), Point(-4,4), Point(-5,5), Point(-6,6), Point(-7,7),
                 Point(1,-1), Point(2,-2), Point(3,-3), Point(4,-4), Point(5,-5), Point(6,-6), Point(7,-7)};
}

vector<Point> Bishop::getPossibleMoves()
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

void Bishop::moveTo(Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves();
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
        {
            steppers->moveToPoint(m_pos);
            time_sleep(1);
            
            int diff = aDesPoint.x - this->m_pos.x;
            int diagonal = round(abs(diff)*(sqrt(2*(fieldSize*fieldSize))));

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

            // move virtually
            int neu;
            for (neu = 0; neu < 64; neu++)
            {
                if ((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            delete (*playField)[neu];
            (*playField)[neu] = new Bishop(m_col, aDesPoint);
            m_type = PieceType::none;
            m_col = Color::blank;
            
            steppers->currPoint = aDesPoint;
        }
    }
}