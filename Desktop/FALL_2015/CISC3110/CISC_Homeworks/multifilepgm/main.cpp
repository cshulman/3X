#include <iostream>
#include "Player.h"
#include "Game.h"

using namespace std;

/******
* MAIN*
*******/
int main()
{
    int i=0;
	string *strPlrs, pic="♔", Pwinner;
	Game game;//sets up a "board/game" so player's can play.
	
	//seeding so the dice can work in the future
	srand(time(NULL));

    // the game is set up by the upcoming functions:
//////PUT ALL THIS IN A SETUPGAME FUNCTION	
	//will display the game rules & the board setup.
    game.displayRules();
    //calls the function that asks the user to input the number of player.
	game.howmanyPlrs();
	//calls the function to input the names of the players into the string array, which is dynamicaly allocated
    strPlrs=game.getnamePlayers();
	//calls the function to determine the playing order, & sorts the array @param, into said order.
	game.roll4first(strPlrs);
	//fills the sorted array into the array of Player objects (Game member)
	game.setPlayers(strPlrs);
	
	cout<<"All Players begin at space#1."<<endl<<endl;
    cout<<endl<<pic<<pic<<"\tLET THE GAME BEGIN!!\t"<<pic<<pic<<endl<<endl;

	//in each lap, each player gets one turn (unless they landed on loseAturn previously or land on rollAgain)
	//the players will play until a winner is declared. 
	while(game.getWinner()==false)
	{
		cout<<endl<<"-------------------- LAP # "<<game.getLap()<<" --------------------"<<endl;
		Pwinner=game.mainPlay();
		game.addLap();
	}
		

	cout<<endl<<pic<<" "<<pic<<" Congratulations!! ";
	cout<<Pwinner<<" has completed the board 3 times and is the winner!"<<pic<<" "<<pic<<endl;
    
	return 0;
}