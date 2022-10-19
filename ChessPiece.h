#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <iostream>
#include </home/zach/ZACH/Point.h>
#include <vector>

using namespace std;

enum Color{
    Black = 0,
    White
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

        ChessPiece();
        ChessPiece(Color aCol, PieceType aType, Point aPos);
        virtual vector<Point> getPossibleMoves(vector<ChessPiece> aPlayfield);
        void GetPieceType(vector<ChessPiece> aPlayfield, Point aPoint);
        void moveTo(Point aDesPoint);
};

#endif