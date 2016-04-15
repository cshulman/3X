1#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;
/***************************
* PLAYER CLASS DECLARATION *
****************************/
class Player
{
	private:
    	string name;
		int rounds;
    	int location;
    	int space;
    	bool loseAturn;

	public:
	//constructor
	Player ();
		//sets everything to 0, except space, to 1

	//accessors
	string getName()const
		{return name;}
			//returns the name of a player
	int getRounds()const
		{return rounds;}
			//returns the number of rounds
	int getLocation()const
		{return location;}
			//returns the total location
	int getSpace()const
		{return space;}
			//returns the space
	bool getLoseAturn()const
		{return loseAturn;}
			//returns true if player landed on loseAturn, else returns false
	bool showState()const;
			//prints outcome of move, i.e where players are located
			//returns true if a winner has been found, else false

	//mutators
	void setName(string n)
		{ name =n; }
			//sets the player's name to the value passed @param
	void satRounds(int r)
		{ rounds =r; }
			//sets the player's rounds to the value passed @param
	void setLocation(int l)
		{ location=l; }
			//sets the player's location to the value passed @param
	void setSpace(int s)
		{ space =s; }
			//sets the player's space to the value passed @param
	void setLoseAturn(bool lose)
		{ loseAturn=lose; }
			//sets loseAturn to the value passed @parame
	void Move(int);
			//moves the player along the board based on the die roll
			//@param-die result
	int ifSwitch(const int &, Player *, const int &);
			// compares the call player to all other players to determine if a switch occurs.
			//i.e, someone is ahead of the call player.
			//Returns: the call player's index if none are ahead. Else the index of the player that is farthest on the board.
			//@params-const int, call Player's index, Player *(to the array of Player objects, for comparison)
			//const int-number of players
	void Switch(Player *, const int &, int &);
			// Switches the call player with the other player passed
			//@params-Player* (to the array of player objects) & other player's index
			//and the amount of spaces the other player moved back.
};
#endif
