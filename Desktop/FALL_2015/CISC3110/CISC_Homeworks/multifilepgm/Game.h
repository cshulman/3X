#ifndef GAME_H
#define GAME_H

#include "PLAYER.h"

using namespace std;

//declares the board obstacles as const values
const int places=24, goAgain=20, loseTurn=10, moveThree=3, moveBtwo= 22, SWITCH=8, Nothing=0;

/*************************
* GAME CLASS DECLARATION *
**************************/
class Game
{
	private:
	int board[places];
	int numPlrs;
	int die;
	int lap;
	Player players[6];//since this game can only accommodate up to 6 players
	bool winner;

	void setnumPlrs(int num_plrs)
		{ numPlrs=num_plrs; }
		//sets the number of players to what the user entered
	void setWinner(bool);
        //sets the winner every time a player moves on the board
	
	public:
		//default constructer
		Game ();
			//sets up the "Board".
			
		//accessors
		void displayRules();
			//this function displays the rules & board setup
		int getnumPlrs()const
			{ return numPlrs; }
				//returns the number of players whenever called
		int rollDie(string);
			// simulates a die roll & returns the outcome.
			//@ param-name of the player, so can print the outcome message
		int getLap()const
			{ return lap; }
				//returns what lap the players are on
		bool getWinner()const
			{ return winner; }
				//returns false if no one won yet, and true if a winner has been chosen

		//mutators and other functions
		void howmanyPlrs();
			//asks the user how many players will play, & returns the int amount
        string * getnamePlayers();
            //gets the name of the players from the user
		void roll4first(string *splayers);
			// determines who will play first or second & returns an array with the players in correct playing order.
			//@params-string-all players (not in order)
		void addLap()
			{ lap++; }
				//adds one to lap each call
		void setPlayers(string *);
			//sets the players name, based on the playing order
		string mainPlay();
            //plays the game and calls functions when necessary.
			//returns the name of the winner
		void play(const int &);
            // @params-call player's index
};
#endif
