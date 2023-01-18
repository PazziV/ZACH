#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include </home/zach/ZACH/Point.h>
#include </home/zach/ZACH/Stepper.h>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

enum Color{
    Black = 0,
    White,
    blank
};

enum PieceType{
    none = 0,
    Pawn,   //Bauer
    Bishop,     //Läufer
    Knight,     //Pferd
    Rook,       //Turm
    Queen,
    King
};

class ChessPiece
{
    public:
        Point m_pos;
        Color m_col;
        PieceType m_type;
        vector<Point> m_MoveSet;

        static Stepper* steppers;
        static array<ChessPiece*, 64>* playField;

        ChessPiece();
        ChessPiece(Color aCol, PieceType aType, Point aPos);
        virtual vector<Point> getPossibleMoves();
        void GetPieceType(Point aPoint);
        virtual void moveTo(Point aDesPoint);
        void conPrintBoard();
};

#endif