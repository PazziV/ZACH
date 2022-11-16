#include </home/zach/ZACH/ChessPieceTypes/King.h>

using namespace cp;

King::King(Color aCol, Point aPos)
{
    m_col = aCol;
    m_pos = aPos;
    m_type = PieceType::King;

    m_MoveSet = {Point(0,1), Point(0,-1), Point(1,0), Point(-1,0), Point(1,1), Point(-1,1), Point(1,-1), Point(-1,-1)};
}

vector<Point> King::getPossibleMoves(vector<ChessPiece> aPlayfield)
{
    vector<Point> possibleMoves;
    Point desPoint; // Destination Point

    for(int a = 0; a < m_MoveSet.size(); a++)
    {
        desPoint = m_pos + m_MoveSet[a];
        if(desPoint.x <= 7 && desPoint.x >= 0 && desPoint.y <= 7 && desPoint.y >= 0)
        {
            ChessPiece occupant;
            occupant.GetPieceType(aPlayfield, desPoint);

            if(occupant.m_col != this->m_col)
            {
                if(occupant.m_type != PieceType::King)
                    possibleMoves.push_back(desPoint);
            }
        }
    }

    return possibleMoves;
}

void King::moveTo(Stepper steppers, Point aDesPoint)
{
    vector<Point> possibleMoves = getPossibleMoves(aPlayfield);
    for(int i = 0; i < possibleMoves.size(); i++)
    {
        if(aDesPoint == possibleMoves[i])
        {
            if((aDesPoint.x != this.m_pos.x && aDesPoint.y == this.m_pos.y) || (aDesPoint.x == this.m_pos.x && aDesPoint.y != this.m_pos.y)) // move straight
            {
                if(aDesPoint.x == this.m_pos.x)
                {
                    if(aDesPoint.y > this.m_pos.y)
                    {
                        steppers.moveByMM(ChessPiece::fieldSize, Direction::Backwards);
                    }
                    else if(aDesPoint.y < this.m_pos.y)
                    {
                        steppers.moveByMM(absChessPiece::fieldSize, Direction::Forwards);
                    }
                }    
                else    
                {
                    if(aDesPos.x > this.m_pos.x)
                    {
                        steppers.moveByMM(ChessPiece::fieldSize, Direction::Right);
                    }
                    else if(aDesPos < this.m_pos.x)
                    {
                        steppers.moveByMM(absChessPiece::fieldSize, Direction::Left);
                    }
                }   
            }
            else // move diagonal
            {
                int diagonal = round((sqrt(2*(fieldSize*fieldSize))));

                if(aDesPoint.x > this.m_pos.x)
                {
                    if(aDesPoint.y > this.pos.y)
                        steppers.moveByMM(diagonal, Direction::DiagonalRB);
                    else
                        steppers.moveByMM(diagonal, Direction::DiagonalRF);
                }
                else
                {
                    if(aDesPoint.y > this.pos.y)
                        steppers.moveByMM(diagonal, Direction::DiagonalLB);
                    else
                        steppers.moveByMM(diagonal, Direction::DiagonalLF);
                }
            }
            this.m_pos = aDesPoint;
        }
    }
}