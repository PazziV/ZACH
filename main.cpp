#include <iostream>
#include <vector>
#include </home/zach/ZACH/ChessPiece.h>
#include </home/zach/ZACH/ChessPieceTypes/Pawn.h>
#include </home/zach/ZACH/ChessPieceTypes/Bishop.h>
#include </home/zach/ZACH/ChessPieceTypes/Rook.h>
#include </home/zach/ZACH/ChessPieceTypes/Knight.h>
#include </home/zach/ZACH/ChessPieceTypes/Queen.h>
#include </home/zach/ZACH/ChessPieceTypes/King.h>
#include </home/zach/ZACH/Stepper.h>
#include <array>

using namespace std;

array<ChessPiece*, 64> playField;

Stepper steppers;
ChessPiece tempPiece;


void resetBoard();
void conPrintBoard();

void Test1();
void Test2();
void Test3();

int main()
{
    printf("start\n");

    tempPiece.steppers = &steppers;
    tempPiece.playField = &playField;

    //resetBoard();
    steppers.currPoint = Point(0,7); //steppers.calibrate();

    steppers.stepperTest();
    time_sleep(1);

    //Test3();
    steppers.moveByMM(50, Direction::DiagonalRF);

    steppers.moveToPoint(Point(0,7));

    //while(1){}
    
    return 1;
}

void Test1()
{
    playField[48] = new cp::Pawn(Color::White, Point(0,6));
    for(int i = 0; i <= 63; i++)
    {
        if(i != 48)
            playField[i] = new ChessPiece(i);
    }

    playField[48]->printPieceInfo();
    playField[48]->moveTo(Point(0,4));
    conPrintBoard();
    printf("Move 1 done\n");
    time_sleep(5);

    playField[32]->printPieceInfo();
    playField[32]->moveTo(Point(0,3));
    conPrintBoard();
    printf("Move 2 done\n");
    time_sleep(5);

    playField[24]->printPieceInfo();
    playField[24]->moveTo(Point(0,1));
    conPrintBoard();
    printf("Move 3 done\n");
    time_sleep(5);

    playField[24]->printPieceInfo();
    playField[24]->moveTo(Point(0,2));
    conPrintBoard();
    printf("Move 5 done\n");
    time_sleep(5);

    playField[16]->printPieceInfo();
    playField[16]->moveTo(Point(0,1));
    conPrintBoard();
    printf("Move 6 done\n");
}

void Test2()
{
    resetBoard();

    for(int i = 48; i < 56; i++)
    {
        playField[i]->printPieceInfo();
        playField[i]->moveTo(Point((i-48), 4));
        conPrintBoard();
        time_sleep(2);
    }
    playField[56]->moveTo(Point(0,5));
    conPrintBoard();
    time_sleep(3);

    playField[57]->moveTo(Point(2,5));
    conPrintBoard();
    time_sleep(3);

    playField[58]->moveTo(Point(4,5));
    conPrintBoard();
    time_sleep(3);

    playField[59]->moveTo(Point(2,6));
    conPrintBoard();
    time_sleep(3);

    playField[50]->moveTo(Point(0,6));
    conPrintBoard();
    time_sleep(3);

    playField[60]->moveTo(Point(3,7));
    conPrintBoard();
    time_sleep(3);
}

void Test3()
{
    playField[35] = new cp::Bishop(Color::White, Point(3,4));
    for(int i = 0; i <= 63; i++)
    {
        if(i != 35)
            playField[i] = new ChessPiece(i);
    }

    playField[35]->printPieceInfo();
    playField[35]->moveTo(Point(7,0));
    conPrintBoard();
    printf("Move 1 done\n");
    time_sleep(3);

    playField[7]->printPieceInfo();
    playField[7]->moveTo(Point(3,4));
    conPrintBoard();
    printf("Move 2 done\n");
    time_sleep(3);

    playField[35]->printPieceInfo();
    playField[35]->moveTo(Point(0,1));
    conPrintBoard();
    printf("Move 3 done\n");
    time_sleep(3);

    playField[8]->printPieceInfo();
    playField[8]->moveTo(Point(6,7));
    conPrintBoard();
    printf("Move 4 done\n");
    time_sleep(3);

    playField[62]->printPieceInfo();
    playField[62]->moveTo(Point(6,0));
    conPrintBoard();
    printf("Move 5 done\n");
    time_sleep(3);

    playField[62]->printPieceInfo();
    playField[62]->moveTo(Point(0,7));
    conPrintBoard();
    printf("Move 6 done\n");
    time_sleep(3);

    playField[62]->printPieceInfo();
    playField[62]->moveTo(Point(0,3));
    conPrintBoard();
    printf("Move 7 done\n");
    time_sleep(3);
}

void resetBoard()
{
    for(int a = 0; a < 64; a++) // delete every piece
        delete playField[a];

    // set pieces to starting positions
    playField[0] = new cp::Rook(Color::Black, Point(0,0)); playField[7] = new cp::Rook(Color::Black, Point(7,0));
    playField[1] = new cp::Knight(Color::Black, Point(1,0)); playField[6] = new cp::Knight(Color::Black, Point(6,0));
    playField[2] = new cp::Bishop(Color::Black, Point(2,0)); playField[5] = new cp::Bishop(Color::Black, Point(5,0));
    playField[3] = new cp::Queen(Color::Black, Point(3,0));
    playField[4] = new cp::King(Color::Black, Point(4,0));
    for(int i = 8; i <= 15; i++)
        playField[i] = new cp::Pawn(Color::Black, Point((i-8),1));

    for(int i = 16; i <= 55; i++) 
    {
        playField[i] = new ChessPiece(i);   // empty fields
    }

    playField[56] = new cp::Rook(Color::White, Point(0,7)); playField[63] = new cp::Rook(Color::White, Point(7,7));
    playField[57] = new cp::Knight(Color::White, Point(1,7)); playField[62] = new cp::Knight(Color::White, Point(6,7));
    playField[58] = new cp::Bishop(Color::White, Point(2,7)); playField[61] = new cp::Bishop(Color::White, Point(5,7));
    playField[59] = new cp::Queen(Color::White, Point(3,7)); playField[60] = new cp::King(Color::White, Point(4,7));
    for(int i = 48; i <= 55; i++)
        playField[i] = new cp::Pawn(Color::White, Point((i-48),6));
}

void conPrintBoard()    //print Board to Console
{
    for(int i = 0; i < 64; i++) //print piece type
        {
            if(i % 8 == 0)
                printf("\n*");
            switch(playField[i]->m_type)
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
                case PieceType::none:
                {
                    printf("  ");
                    break;
                }
            }
        }
    printf("\n");

    // for(int i = 0; i < 64; i++) // print color of piece
    // {
    //     if(i % 8 == 0)
    //         printf("\n");
    //     switch(playField[i]->m_col)
    //     {
    //         case Color::Black:
    //         {
    //             printf("B ");
    //             break;
    //         }
    //         case Color::White:
    //         {
    //             printf("W ");
    //             break;
    //         }
    //         case Color::blank:
    //         {
    //             printf("  ");
    //             break;
    //         }
    //     }
    // }
    // printf("\n");
}