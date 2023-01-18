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
    //debug shit
    printf("Entered getPossibleMoves in Pawn\n");
    //----------

    //only standard moves, no "en passant" (maybe at a later point)
    vector<Point> possibleMoves;
    Point desPoint; // Destination Point

    for(int a = 0; a < m_MoveSet.size(); a++)
    {
        //debug shit
        if(a == 0)
            printf("Entered for loop. m_MoveSet.size = %d\n", m_MoveSet.size());
        //----------

        if(this->m_col == Color::Black)
            desPoint = m_pos + m_MoveSet[a];
        else if(this->m_col == Color::White)
            desPoint = m_pos - m_MoveSet[a];
        //debug shit
        printf("desPoint: %d, %d\n", desPoint.x, desPoint.y);
        //----------
        if(desPoint.x <= 7 && desPoint.x >= 0 && desPoint.y <= 7 && desPoint.y >= 0)
        {
            //debug shit
            printf("Entered desPoint if\n");
            //----------

            ChessPiece occupant;
            occupant.GetPieceType(desPoint);

            //debug shit
            printf("this color: %d, occupant color: %d\n", this->m_col, occupant.m_col);
            //----------

            if(occupant.m_col != this->m_col)
            {
                //debug shit
                printf("occupant is enemy\n");
                //----------

                if(occupant.m_type != PieceType::King)
                    possibleMoves.push_back(desPoint);
            }

            //debug shit
            printf("leaving desPoint if\n");
            //----------
        }
    }

    //debug shit
    printf("getPossibleMoves done\n");
    //----------

    return possibleMoves;
}

void Pawn::moveTo(Point aDesPoint)
{
    //debug shit
    printf("Entered moveTo of Pawn\n");
    //----------

    vector<Point> possibleMoves = getPossibleMoves();
    
    //debug shit
    printf("possibleMove.size = %d\n", possibleMoves.size());
    //----------
    
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        //debug shit
        if(i == 0)
        {
            printf("Entered for loop\n");
        }
        //----------

        if(aDesPoint == possibleMoves[i])
        {
            //debug shit
            printf("aDesPoint == possibleMoves[i]\n");
            //----------

            if(this->m_pos.x == aDesPoint.x)
            {
                //debug shit
                printf("this->m_posx == aDesPoint.x\n");
                //----------

                int diff = aDesPoint.y - this->m_pos.y;
                if(diff > 0)
                {
                    //debug shit
                    printf("diff > 0: %d\n", diff);
                    //----------

                    steppers->moveByMM(abs(diff)*fieldSize, Direction::Backwards);  
                }                                                                              
                else if(diff < 0)
                {
                    //debug shit
                    printf("diff < 0: %d\n", diff);
                    //----------

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
                    //debug shit
                    printf("White\n");
                    //----------

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
                    //debug shit
                    printf("Black\n");
                    //----------

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
            int alt, neu;
            for(alt = 0; alt < 64; alt++)
            {
                if((*playField)[alt]->m_pos == this->m_pos)
                    break;
            }
            for(neu = 0; neu < 64; neu++)
            {
                if((*playField)[neu]->m_pos == aDesPoint)
                    break;
            }
            (*playField)[neu] = this;
            this->m_pos = aDesPoint;
            (*playField)[alt]->m_type = PieceType::none;
            (*playField)[alt]->m_col = Color::blank;
        }
    }

    //debug shit
    printf("moveTo of Pawn done\n");
    //----------
}