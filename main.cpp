#include <iostream>
#include <vector>
#include <Point.h>
#include <ChessPiece.h>
#include <Pawn.h>
#include <Bishop.h>
#include <Rook.h>
#include <Knight.h>
#include <Queen.h>
#include <King.h>
#include <array>
// include Stepper Control

using namespace std;

array<ChessPiece*, 64> playField;

void resetBoard();

void main()
{
    while(1)
    {

    }
}

void resetBoard()
{
    for(int a = 0; a < 64; a++) // delete every piece
        delete playField[a];



    playField[0] = new cp::Rook(Color::Black, Point(0,0)); playField[7] = new cp::Rook(Color::Black, Point(7,0));
    playField[1] = new cp::Knight(Color::Black, Point(1,0)); playField[6] = new cp::Knight(Color::Black, Point(6,0));
    playField[2] = new cp::Bishop(Color::Black, Point(2,0)); playField[5] = new cp::Bishop(Color::Black, Point(5,0));
    playField[3] = new cp::Queen(Color::Black, Point(3,0));
    playField[4] = new cp::King(Color::Black, Point(4,0));
    for(int i = 8; i <= 15; i++)
        playField[i] = new cp::Pawn(Color::Black, Point((i-8),1));

    playField[56] = new cp::Rook(Color::White, Point(0,7)); playField[60] = new cp::Rook(Color::White, Point(7,7));
    playField[57] = new cp::Knight(Color::White, Point(1,7)); playField[61] = new cp::Knight(Color::White, Point(6,7));
    playField[58] = new cp::Bishop(Color::White, Point(2,7)); playField[62] = new cp::Bishop(Color::White, Point(5,7));
    playField[59] = new cp::Queen(Color::White, Point(3,7)); playField[63] = new cp::King(Color::White, Point(4,7));
    for(int i = 48; i <= 55; i++)
        playField[i] = new cp::Pawn(Color::White, Point((i-48),6));

    // WENN FIGUREN VOM FELD GENOMMEN WERDEN AUS ARRAY DELETEN!!!!!!!!!! ==> delete playField[x];
}