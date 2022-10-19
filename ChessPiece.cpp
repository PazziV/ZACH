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

vector<Point> ChessPiece::getPossibleMoves(vector<ChessPiece> aPlayfield)
{

}

void ChessPiece::GetPieceType(vector<ChessPiece> aPlayfield, Point aPoint)
{
    int pos = 0;
    for(int i = 0; i < aPlayfield.size(); i++)
    {
        if(aPlayfield[i].m_pos == aPoint)
            pos = i;
    }
    m_type = aPlayfield[pos].m_type;
    m_col = aPlayfield[pos].m_col;
}

void ChessPiece::moveTo(Point aDesPoint)