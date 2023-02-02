#include </home/zach/ZACH/ChessPieceTypes/Pawn.h>

using namespace cp;

Pawn::Pawn(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Pawn;

    m_MoveSet = {Point(0, 2), Point(0, 1), Point(1, 1), Point(-1, 1)};
}

vector<Point> Pawn::getPossibleMoves()
{
    // only standard moves, no "en passant" (maybe at a later point)
    vector<Point> possibleMoves;
    Point desPoint; // Destination Point

    for (int a = 0; a < m_MoveSet.size(); a++)
    {
        if (m_col == Color::Black && m_pos.y != 1 && a == 0)
            a++; // only allow to move 2 fields if Pawn is at starting Point
        else if (m_col == Color::White && m_pos.y != 6 && a == 0)
            a++;

        if (m_col == Color::Black)
            desPoint = m_pos + m_MoveSet[a];
        else if (m_col == Color::White)
            desPoint = m_pos - m_MoveSet[a];

        if (desPoint.x <= 7 && desPoint.x >= 0 && desPoint.y <= 7 && desPoint.y >= 0)
        {
            ChessPiece occupant;
            occupant.GetPieceType(desPoint);
            if (occupant.m_col != m_col)
            {
                if (occupant.m_type != PieceType::King)
                    possibleMoves.push_back(desPoint);
            }
        }
    }
    return possibleMoves;
}

void Pawn::moveTo(Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves();

    for (int i = 0; i < possibleMoves.size(); i++)
    {
        if (aDesPoint == possibleMoves[i])
        {
            steppers->moveToPoint(m_pos);
            time_sleep(1);

            if (this->m_pos.x == aDesPoint.x)
            {
                int diff = aDesPoint.y - this->m_pos.y;
                if (diff > 0)
                {
                    steppers->moveByMM(abs(diff) * fieldSize, Direction::Backwards);
                }
                else if (diff < 0)
                {
                    steppers->moveByMM(abs(diff) * fieldSize, Direction::Forwards);
                }
            }
            else
            {
                int diagonal = round((sqrt(2 * (fieldSize * fieldSize))));
                if (this->m_col == Color::White)
                {
                    if (aDesPoint.x > this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalRF);
                    }
                    else if (aDesPoint.x < this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalLF);
                    }
                }
                else if (this->m_col == Color::Black)
                {
                    if (aDesPoint.x > this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalRB);
                    }
                    else if (aDesPoint.x < this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalLB);
                    }
                }
            }

            // move virtually
            int neu;
            for (neu = 0; neu < 64; neu++)
            {
                if ((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            delete (*playField)[neu];
            (*playField)[neu] = new Pawn(m_col, aDesPoint);
            m_type = PieceType::none;
            m_col = Color::blank;
            
            steppers->currPoint = aDesPoint;
        }
    }
}