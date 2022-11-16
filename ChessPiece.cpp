#include </home/zach/ZACH/ChessPiece.h>

Stepper* ChessPiece::steppers = 0;
array<ChessPiece*, 64>* ChessPiece::playField = 0;

ChessPiece::ChessPiece()
{
    m_type = PieceType::none;
}

ChessPiece::ChessPiece(Color aCol, PieceType aType, Point aPos)
{
    m_type = aType;
    m_col = aCol;
    m_pos = aPos;
}

vector<Point> ChessPiece::getPossibleMoves()
{
    vector<Point> tmp = {};
    return tmp;
}

void ChessPiece::GetPieceType(Point aPoint)
{
    int pos = 0;
    for(int i = 0; i < 64; i++)
    {
        if(playfield[i]->m_pos == aPoint)
            pos = i;
    }
    m_type = playfield[pos]->m_type;
    m_col = playfield[pos]->m_col;
}

void ChessPiece::moveTo(Point aDesPoint)
{
}