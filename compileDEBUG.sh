#!/bin/bash
g++ -g -o main Point.cpp Stepper.cpp ChessPiece.cpp ChessPieceTypes/Bishop.cpp ChessPieceTypes/King.cpp ChessPieceTypes/Knight.cpp ChessPieceTypes/Pawn.cpp ChessPieceTypes/Queen.cpp ChessPieceTypes/Rook.cpp main.cpp -lpigpio -pthread
