#include </home/zach/ZACH/ChessPiece.h>

Stepper* ChessPiece::steppers = 0;
array<ChessPiece*, 64>* ChessPiece::playField = 0;

ChessPiece::ChessPiece()
{
    m_type = PieceType::none;
    m_col = Color::blank;
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
        if((*playField)[i]->m_pos == aPoint)
            pos = i;
    }
    m_type = (*playField)[pos]->m_type;
    m_col = (*playField)[pos]->m_col;
}

void ChessPiece::moveTo(Point aDesPoint)
{
    //debug shit
    printf("Entered moveTo in ChessPiece.cpp\n");
    //----------
}

void ChessPiece::conPrintBoard()    //print Board to Console
{
    for(int i = 0; i < 64; i++)
        {
            if(i % 8 == 0)
                printf("\n");
            switch((*playField)[i]->m_type)
            {
                case PieceType::Rook:
                {
                    printf("T ");
                    break;
                }
                case PieceType::Knight:
                {
                    printf("P ");
                    break;
                }
                case PieceType::Bishop:
                {
                    printf("L ");
                    break;
                }
                case PieceType::Pawn:
                {
                    printf("B ");
                    break;
                }
                case PieceType::Queen:
                {
                    printf("Q ");
                    break;
                }
                case PieceType::King:
                {
                    printf("K ");
                    break;
                }
            }
        }
}