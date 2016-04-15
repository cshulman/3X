#include <iostream>
#include "Player.h"

/***********
*PLAYER.cpp*
************/

//default constructor
Player :: Player()
{
	rounds=0;
	location=1;
	space=0;
	loseAturn=0;
}
//displays the location of the player calling the function
bool Player :: showState()const
{
	bool win=false;

    if(rounds==3)
		win=true;
    else
        cout<<name<<" has completed the board "<<rounds<<" time/s, and is at space# "<<space<<"."<<endl;

	return win;
}
//moves the player along the board based on the dice roll
void Player :: Move(int Die)
{
	location+=Die;//moves the player's location the amount of spaces that they rolled
	rounds=location/places; space=location%places;//calculates rounds & spaces

	//if space is 0, means they are on space 24 so it must be adjusted accordingly
	if(space==0)
    {
        space=24;
        rounds--;
    }
}
//Compares the call player's space with all other player's space to determine if any players are ahead.
int Player :: ifSwitch(const int &callPindex, Player *players, const int &num_plrs)
{
    int j, playerMspace=callPindex, mostSpace=space;

	//checks if any other player's space is greater, than the player calling.
    for(j=0; j<num_plrs; j++)
    {
		//if it found a player that is farther along than the call player this occurs
        if (mostSpace<players[j].getSpace())
        {
			//stores that players index number here
            playerMspace=j;
			mostSpace=players[j].getSpace();
//**********//I tried to get rid of either of these 2 lines, but I couldn't figure it out.
			//I'm trying to find the player that is farthest, so I need a variable for location
//**********//& a variable to keep track of which player is the farthest
        }
    }

	//if no one is ahead this occurs
    if(space>=mostSpace)
		{
        	cout<<"Since there aren't any players ahead of "<<name<<", he/she will not switch."<<endl;
			playerMspace=callPindex;
			//this is necessary if there is another player at the same space
		}

	//if yes, that player's index is returned
    else
        cout<<name<<" will switch places with "<<players[playerMspace].getName()<<", Since he/she is the farthest."<<endl;

	return playerMspace;
}
//initiates a switch between the player on the SWITCH space & the player that is farthest ahead
void Player :: Switch(Player *players, const int &otherPindex, int &moved)
{
    int result=0;
	moved=0;

	location=(location-14)+ players[otherPindex].getSpace();
	space= players[otherPindex].getSpace();
	players[otherPindex].setLocation(players[otherPindex].getLocation()-players[otherPindex].getSpace() +14);
	players[otherPindex].setSpace(14);

	//displays the other player's new location
    cout<<endl<<"\tAfter switching places with "<<name<<", "<<players[otherPindex].getName()<<"'s location is:"<<endl;
    players[otherPindex].Move(result);
    players[otherPindex].showState();

	//displayes the call player's new location
    cout<<"\tThe new location for  "<<name<<" is:"<<endl;
    Move(result);
    showState();//shows where the player that initiated the switch is located after Switch.

	moved=(space-14);
}
