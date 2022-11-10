#include </home/zach/ZACH/ChessPiece.h>

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

vector<Point> ChessPiece::getPossibleMoves(array<ChessPiece*, 64> aPlayfield)
{
    vector<Point> tmp = {};
    return tmp;
}

void ChessPiece::GetPieceType(array<ChessPiece*, 64> aPlayfield, Point aPoint)
{
    int pos = 0;
    for(int i = 0; i < 64; i++)
    {
        if(aPlayfield[i]->m_pos == aPoint)
            pos = i;
    }
    m_type = aPlayfield[pos]->m_type;
    m_col = aPlayfield[pos]->m_col;
}

void ChessPiece::moveTo(Stepper steppers, Point aDesPoint)
{
}