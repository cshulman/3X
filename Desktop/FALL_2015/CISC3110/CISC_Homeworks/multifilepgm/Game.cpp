#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Player.h"
#include "Game.h"

using namespace std;
/*********
*GAME.cpp*
**********/
Game :: Game()
{

	for(int i=0; i<places; i++)
		board[i]=Nothing;
	
	board[1]=loseTurn; board[3]=goAgain; board[5]=moveBtwo; board[10]=moveThree;
	board[13]=SWITCH; board[15]=loseTurn; board[18]=goAgain; board[21]=moveBtwo;
	
	die=0;
	lap=1;
	winner=false;
}

// this function displays the board & explains the game rules
void Game :: displayRules ()
{
        cout<<"Welcome to 3X! The game where you will experience ups, downs and everything in between."<<endl;
        cout<<"The board is set up as follows:"<<endl;

        for(int i=0; i<places; i++)//board setup
		{
			cout<<setw(12);
			cout<<"Space# "<<i+1<<"= "<<board[i]<<"\t";
		}	
		              
        cout<<endl<<endl;
        cout<<"0 represents an obstacle free space."<<endl;
        cout<<"10 represents a 'Lose Turn' obstacle."<<endl;
        cout<<"20 represents a 'Go again' obstacle. "<<endl;
        cout<<"3 represents a 'Move Forward Three' obstacle"<<endl;
        cout<<"22 represents a 'Move Back Two' obstacle"<<endl;
        cout<<"And 8 represents a 'Switch' obstacle."<<endl;
        cout<<"The object of the game is to be the first player to cross the board 3 times."<<endl;
        cout<<"If you land on a space with an obstacle, (listed above) you must do said action."<<endl<<endl;
}

//asks user to input how many players will be playing the game
void Game :: howmanyPlrs()
{
   int num_players;
    cout<<"How many players will be playing 3X! ?"<<endl;
    cin>>num_players;
	//checks that a number between 2-6 has been entered
    while(num_players<2 || num_players>6)
    {
            cout<<"This game only accommodates 2-6 players."<<endl;
            cout<<"Please renter the amount of players."<<endl;
            cin>>num_players;
    }
	//sets the number of players (only time, and only place this can happen)
	setnumPlrs(num_players);
}

//this function asks the user to input the name of all player's
string * Game :: getnamePlayers()
{
    int i=0;
	string *players;
	players= new string[numPlrs];
	//inputs the name the user enters in a string array
    for(i=0; i<numPlrs; i++)
    {
        cout<<"What is the name of player# "<<i+1<<"?"<<endl;
        cin>>players[i];
    }
	return players;
}

//a die roll is simulated
int Game :: rollDie(string player)
{
    int result;
    string pic="☆";
    result = rand()%6+1;
        cout << "\t"<<pic<<" "<<player<<" rolled a " << result << "." <<endl;
    return (result);
}

//the players roll a die to determine the playing order
void Game :: roll4first(string *splayers)
{
    bool swap;
	int i, tempDie;
	string tempPlayer;
	//This array keeps track of the die outcomes
	int *outcome;
	outcome= new int[numPlrs];

    cout<<endl<<"All players will roll to determine the order that they will play in."<<endl;
	//players all roll the dice
    for(i=0; i<numPlrs; i++)
         outcome[i]= rollDie(splayers[i]);

	do
	{
		swap=false;

		for(i=0; i<numPlrs; i++)
			if(outcome[i] < outcome[i+1])
			{
				//swap die outcome
				tempDie=outcome[i];
				outcome[i]=outcome[i+1];
				outcome[i+1]=tempDie;
				//swap player
				tempPlayer=splayers[i];
				splayers[i]=splayers[i+1];
				splayers[i+1]=tempPlayer;
				swap=true;
			}

	}while(swap!=false);

	delete [] outcome;
}

//sets the players name
void Game :: setPlayers(string *strplrs)
{
	int i;
	
	for(i=0; i<numPlrs; i++)
		players[i].setName(strplrs[i]);
	
	//Prints the order that the players will play
		cout<<endl<<"The players will be playing in this order:"<<endl;
		for(i=0; i<numPlrs; i++)
			cout<<"Playing in position "<<i+1<<" is: "<<players[i].getName()<<"."<<endl;
}

//the "main play" occurs here.
string Game :: mainPlay()
{
    int i=0;
    int test=0;
    string pic="♔", Pwin;
    
    for(i=0; i<numPlrs; i++)
    {
        if(winner==false)
        {
            //initiates a lose turn, if needed
            if(players[i].getLoseAturn()==1)				{
                cout<<"Since "<<players[i].getName()<<" landed on a loseAturn space last turn, they will lose a turn now."<<endl;
                players[i].setLoseAturn(0);
            }
            //the regular play will occur
            else
            {
                //player i rolls the die.
                die=rollDie(players[i].getName());
                //moves player i after a die roll, using the result of the die
                players[i].Move(die);
                //prints where player i is located.
                winner=players[i].showState();
                //Plays the game for player i's round, if he did not win
                if(winner==false)
                    play(i);
            }
            Pwin=players[i].getName();	
        }
    }
    
    return Pwin;
}

//the "individual player" play occurs here
void Game :: play(const int &callPindex)
{
    int result=0, check=0, aheadPindex=callPindex, moved=0;
////////////////////////////////////////////////////////////////////////
//try doing switch & case, default

    do
	{
		 //this play occurs if goAgain is the space player i landed on
		if(board[players[callPindex].getSpace() -1]==goAgain)
        {
            cout<<players[callPindex].getName()<<" landed on a 'Go Again' space, and will now roll again."<<endl;
            result=rollDie(players[callPindex].getName());//player that landed on goAgain rolls the die again.
            players[callPindex].Move(result);//moves the player after a die roll
            winner=players[callPindex].showState();//prints where the player is located.
            //not necessary to call the play function again because in this loop it will recheck the board
        }
		//this play occurs if moveThree is the space player i landed on
        else if(board[players[callPindex].getSpace() -1]==moveThree)
        {
            result=3;
            cout<<players[callPindex].getName()<<" landed on a 'Move Forward Three' space, and will now advance three spaces."<<endl;
            players[callPindex].Move(result);//player that landed on moveThree moves forward 3.
            cout<<endl<<"\tAfter Move Forward Three:"<<endl;
            winner=players[callPindex].showState();//prints where the player is located.
            //not necessary to call the play function again because in this loop it will recheck the board
        }
		//this play occurs if moveBtwo is the space player i landed on
        else if(board[players[callPindex].getSpace() -1]==moveBtwo)
        {
            result=-2;
            cout<<players[callPindex].getName()<<" landed on a 'Move Back Two' space, and will now move back two spaces."<<endl;
            players[callPindex].Move(result);//player that landed on moveBtwo, moves back 2 spaces.
            cout<<endl<<"\tAfter Move Back Two:"<<endl;
            winner=players[callPindex].showState();//prints where the player is located.
            //not necessary to call the play function again because in this loop it will recheck the board
        }
		//this play occurs if Switch is the space player i landed on
        else if(board[players[callPindex].getSpace() -1]==SWITCH)
        {
			cout<<players[callPindex].getName();
			cout<<" landed on a 'Switch' space, and will now have the opportunity to switch places with another player."<<endl;
			//sends players to the ifSwitch function to determine if the player calls the switch will occur, and returns the player.
			aheadPindex= players[callPindex].ifSwitch(callPindex, players, numPlrs);

				//if it returns a player number (to switch with), this occurs
                if(aheadPindex!=callPindex)
                    	players[callPindex].Switch(players, aheadPindex, moved);
                //else, will return call Player's index & break
				else
                    break;//no other option, otherwise will continue running forever
        }
		//this play occurs if loseTurn is the space player i landed on
        else if (board[players[callPindex].getSpace() -1]==loseTurn)
        {
            players[callPindex].setLoseAturn(true);
			cout<<players[callPindex].getName()<<" landed on a lose turn obstacle, and will lose a turn accordingly"<<endl;
        }
	//ends this loop if the board space is: loseTurn, or Nothing && if the rounds are >3
    }while((board[players[callPindex].getSpace() -1]==goAgain) || (board[players[callPindex].getSpace() -1]==moveThree) || (board[players[callPindex].getSpace() -1]==moveBtwo) || (board[players[callPindex].getSpace() -1]==SWITCH));

		//if there is no obstacle, will just print this & the next player will go
		//needed && to prevent this message from being displayed if the player completes 3X whilst in the loop
    	if((board[players[callPindex].getSpace() -1]==Nothing) && (winner==false))
            cout<<players[callPindex].getName()<<" did not land on any obstacles."<<endl;

}
