#include </home/zach/ZACH/ChessPieceTypes/Pawn.h>

using namespace cp;

Pawn::Pawn(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::Pawn;

    m_MoveSet = {Point(0,2), Point(0,1), Point(1,1), Point(-1,1)};
}

vector<Point> Pawn::getPossibleMoves()
{
    //only standard moves, no "en passant" (maybe at a later point)
    vector<Point> possibleMoves;
    Point desPoint; // Destination Point

    for(int a = 0; a < m_MoveSet.size(); a++)
    {
        if(this->m_col == Color::Black)
            desPoint = m_pos + m_MoveSet[a];
        else if(this->m_col == Color::White)
            desPoint = m_pos - m_MoveSet[a];

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

void Pawn::moveTo(Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves();

    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
        {
            if(this->m_pos.x == aDesPoint.x)
            {
                int diff = aDesPoint.y - this->m_pos.y;
                if(diff > 0)
                {
                     steppers->moveByMM(abs(diff)*fieldSize, Direction::Backwards);  
                }                                                                              
                else if(diff < 0)
                {
                    steppers->moveByMM(abs(diff)*fieldSize, Direction::Forwards);
                }
            }
            else
            {
                /*
                if(aDesPoint.x > this->m_pos.x)   // Move half field to side
                    Stepper::moveByMM(0.5*ChessPiece::fieldSize, Direction::Right);
                else if(aDesPoint.x < this->m_pos.x)
                    Stepper::moveByMM(0.5*ChessPiece::fieldSize, Direction::Left);

                if(this->m_col == Color::White)
                {
                    Stepper::moveByMM(ChessPiece::fieldSize, Direction::Forwards);
                }
                else if(this->m_col == Color::Black)
                {
                    Stepper::moveByMM(ChessPiece::fieldSize, Direction::Backwards);
                }

                if(aDesPoint.x > this->m_pos.x)   // Move to center
                    Stepper::moveByMM(0.5*ChessPiece::fieldSize, Direction::Right);
                else if(aDesPoint.x < this->m_pos.x)
                    Stepper::moveByMM(0.5*ChessPiece::fieldSize, Direction::Left);
                */

               int diagonal = round((sqrt(2*(fieldSize*fieldSize))));
               if(this->m_col == Color::White)
               {
                    if(aDesPoint.x > this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalRF);
                    }
                    else if(aDesPoint.x < this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalLF);
                    }
               }
               else if(this->m_col == Color::Black)
               {
                    if(aDesPoint.x > this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalRB);
                    }
                    else if(aDesPoint.x < this->m_pos.x)
                    {
                        steppers->moveByMM(diagonal, Direction::DiagonalLB);
                    }
               }
            }
            //move virtually
            int neu,alt;
            for(neu = 0; neu < 64; neu++)
            {
                if((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            printf("neu: %d\n", neu);
            printf("test %d %d\n", (*playField)[neu]->m_col, m_col);
            (*playField)[neu]->m_col = m_col;
            printf("käse\n");
            (*playField)[neu]->m_type = m_type;
            printf("schinken\n");
            (*playField)[neu]->m_pos = aDesPoint;
            printf("schmutz\n");
            m_type = PieceType::none;
            m_col = Color::blank;
            printf("NEU=>Type: %d, Col: %d, Pos: %d/%d\n", (*playField)[neu]->m_type, (*playField)[neu]->m_col,
                                                           (*playField)[neu]->m_pos.x, (*playField)[neu]->m_pos.y);
            for(alt = 0; alt < 64; alt++)
            {
                if((*playField)[alt]->m_pos == m_pos)
                    break;
            }
            printf("alt: %d\n", alt);
            printf("ALT=>Type: %d, Col: %d, Pos: %d/%d\n", (*playField)[alt]->m_type, (*playField)[alt]->m_col,
                                                           (*playField)[alt]->m_pos.x, (*playField)[alt]->m_pos.y);
            printf("THIS(ALT)=>Type: %d, Col: %d, Pos: %d/%d\n", m_type, m_col,m_pos.x, m_pos.y);                                               
            steppers->currPoint = aDesPoint;
        }
    }
}