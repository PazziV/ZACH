#include <array>
#include <iostream>
#include <vector>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "ChessPiece.h"
#include "ChessPieceTypes/Bishop.h"
#include "ChessPieceTypes/King.h"
#include "ChessPieceTypes/Knight.h"
#include "ChessPieceTypes/Pawn.h"
#include "ChessPieceTypes/Queen.h"
#include "ChessPieceTypes/Rook.h"
#include "Stepper.h"

using namespace std;

typedef websocketpp::server<websocketpp::config::asio> server;

enum command {
	RESET = 0,
	SYNC,
	GETMOVES,
	MOVE
};

array<ChessPiece*, 64> playField;

Stepper steppers;
ChessPiece tempPiece;

void resetBoard();
void conPrintBoard();

string socketGetBoard();
string socketGetMoves(vector<string> msgVec);
void movePiece(vector<string> msgVec);

vector<string> split(string input, char seperator);

int main()
{
	printf("start\n");

	tempPiece.steppers = &steppers;
	tempPiece.playField = &playField;

	resetBoard();
	conPrintBoard();
	steppers.calibrate();

	//-----WebSocket Communication-----
	server endpoint;
	endpoint.set_access_channels(websocketpp::log::alevel::all);
	endpoint.init_asio();   // initialize server

	//message handler for incoming messages
	endpoint.set_message_handler([&endpoint](websocketpp::connection_hdl hdl, server::message_ptr msg) {
		printf("[Received]: %s \n", msg->get_payload().c_str());
		//endpoint.send(hdl, msg->get_payload(), msg->get_opcode());   // echo the message back

		vector<string> msgVec = split(msg->get_payload().c_str(), ' ');
		string message;
		switch (stoi(msgVec[0])) {  // msgVec[0] ==> command
			case command::RESET:
				resetBoard();
				message = "0 " + socketGetBoard();
				endpoint.send(hdl, message, msg->get_opcode());
				steppers.calibrate();
				break;
			case command::SYNC:
				message = "1 " + socketGetBoard();
				endpoint.send(hdl, message, msg->get_opcode());
				break;
			case command::GETMOVES:
				message = "2" + socketGetMoves(msgVec);
				endpoint.send(hdl, message, msg->get_opcode());
				break;
			case command::MOVE:
				movePiece(msgVec);
				break;
			}
		});

	endpoint.listen(9002); // listen on port 9002
	endpoint.start_accept(); // start server
	endpoint.run(); // run I/O service loop

	return 0;
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
    printf("******conPrintBoard******\n");
    for(int i = 0; i < 64; i++)
        {
            if(i % 8 == 0)
                printf("\n*");
            switch(playField[i]->m_type)
            {
                case PieceType::Rook:
                {
                    printf("T");
                    break;
                }
                case PieceType::Knight:
                {
                    printf("P");
                    break;
                }
                case PieceType::Bishop:
                {
                    printf("L");
                    break;
                }
                case PieceType::Pawn:
                {
                    printf("B");
                    break;
                }
                case PieceType::Queen:
                {
                    printf("Q");
                    break;
                }
                case PieceType::King:
                {
                    printf("K");
                    break;
                }
                case PieceType::none:
                {
                    printf(" ");
                    break;
                }
            }
            switch(playField[i]->m_col)
            {
                case Color::Black:
                {
                    printf("B ");
                    break;
                }
                case Color::White:
                {
                    printf("W ");
                    break;
                }
                case Color::blank:
                {
                    printf("  ");
                    break;
                }
            }
        }
    printf("\n*************************\n");    
    printf("\n");
}

string socketGetBoard()
{
	string board;
	for (int i = 0; i < 64; i++)
	{
		switch (playField[i]->m_col)
		{
		case Color::Black:
		{
			board += "0";
			break;
		}
		case Color::White:
		{
			board += "1";
			break;
		}
		case Color::blank:
		{
			board += "2";
			break;
		}
		}
		switch (playField[i]->m_type)
		{
		case PieceType::none:
		{
			board += "0 ";
			break;
		}
		case PieceType::Pawn:
		{
			board += "1 ";
			break;
		}
		case PieceType::Bishop:
		{
			board += "2 ";
			break;
		}
		case PieceType::Knight:
		{
			board += "3 ";
			break;
		}
		case PieceType::Rook:
		{
			board += "4 ";
			break;
		}
		case PieceType::Queen:
		{
			board += "5 ";
			break;
		}
		case PieceType::King:
		{
			board += "6 ";
			break;
		}
		}
	}
	return board;
}

string socketGetMoves(vector<string> msgVec)   // msgVec[1] ==> selected Piece
{
	vector<Point> moves = playField[stoi(msgVec[1])]->getPossibleMoves();
	string positions;
	for (int i = 0; i < moves.size(); i++)
	{
		for (int a = 0; a < 64; a++)
		{
			if (playField[a]->m_pos == moves[i])
				positions += " " + to_string(a);
		}
	}
	return positions;
}

void movePiece(vector<string> msgVec)  // msgVec[1] ==> pos. selected piece; [2] ==> destination pos
{
	Point des = playField[stoi(msgVec[2])]->m_pos;
	playField[stoi(msgVec[1])]->printPieceInfo();
	playField[stoi(msgVec[1])]->moveTo(des);
	conPrintBoard();
}

vector<string> split(string input, char seperator)
{
	vector<string> output;
	string temp;
	for (int i = 0; i <= input.length(); i++)
	{
		if (input[i] == seperator || i >= input.length())
		{
			output.push_back(temp);
			temp.erase();
		}
		else
			temp += input[i];
	}
	return output;
}