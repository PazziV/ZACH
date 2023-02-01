#include </home/zach/ZACH/ChessPiece.h>

Stepper* ChessPiece::steppers = 0;
array<ChessPiece*, 64>* ChessPiece::playField = 0;

ChessPiece::ChessPiece()
{

}

ChessPiece::ChessPiece(int aArrPos)
{
    m_type = PieceType::none;
    m_col = Color::blank;
    int x,y;
    
    if(aArrPos <= 7)
    {
        y = 0;
        x = aArrPos;
    }
    else if(aArrPos <= 15)
    {
        y = 1;
        x = (aArrPos-8);
    }
    else if(aArrPos <= 23)
    {
        y = 2;
        x = (aArrPos-16);
    }
    else if(aArrPos <= 31)
    {
        y = 3;
        x = (aArrPos-24);
    }
    else if(aArrPos <= 39)
    {
        y = 4;
        x = (aArrPos-32);
    }
    else if(aArrPos <= 47)
    {
        y = 5;
        x = (aArrPos-40);
    }
    else if(aArrPos <= 55)
    {
        y = 6;
        x = (aArrPos-48);
    }
    else if(aArrPos <= 63)
    {
        y = 7;
        x = (aArrPos-56);
    }

    m_pos = Point(x,y);
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

void ChessPiece::printPieceInfo()
{
    printf("*****Piece Info*****\n");
    printf("Color: ");
    switch(m_col)
    {
        case Color::blank:
        {
            printf("none\n");
            break;
        }
        case Color::Black:
        {
            printf("Black\n");
            break;
        }
        case Color::White:
        {
            printf("White\n");
            break;
        }
    }
    printf("Type: ");
    switch(m_type)
    {
        case PieceType::none:
        {
            printf("none\n");
            break;
        }
        case PieceType::Rook:
        {
            printf("Rook\n");
            break;
        }
        case PieceType::Knight:
        {
            printf("Knight\n");
            break;
        }
        case PieceType::Bishop:
        {
            printf("Bishop\n");
            break;
        }
        case PieceType::Pawn:
        {
            printf("Pawn\n");
            break;
        }
        case PieceType::Queen:
        {
            printf("Queen\n");
            break;
        }
        case PieceType::King:
        {
            printf("King\n");
            break;
        }
    }
    printf("Point: x=%d, y=%d\n", m_pos.x, m_pos.y);
    printf("********************\n");
}

void ChessPiece::magnetOn()
{
    
}

void ChessPiece::magnetOff()
{

}