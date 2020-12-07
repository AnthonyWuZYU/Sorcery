#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"
#include "graveyard.h"

int main () {
	//istream *in = nullptr;
    
	cin.exceptions( ios::failbit|ios::eofbit );
	string player1_name;
	string player2_name;
	
	int turn = 0;	

	try {
		//get player1's name 
		while ( player1_name.empty() ) {
			cout << "Player 1: ";
			getline( cin , player1_name);
			if ( player1_name.empty() ) cerr << "Player name cannot be empty" << endl;
		}
		Player player1{player1_name};
		
		//get player2's name 
		while ( player2_name.empty() ) {
        		cout << "Player 2: ";
        		getline( cin , player2_name);
			if ( player1_name.empty() ) cerr << "Player name cannot be empty" << endl;
        	}
        	Player player2{player2_name};
		
		string cmd;
		string option;
		cout << "Player 1's turn" << endl;
    		bool quit = false;

		while (cin >> cmd) {
			if (cmd == "help") {
				cout << "Commands: help -- Display this message." << endl;
				cout << "          end  -- End the current player's turn." << endl;
				cout << "          quit -- End the game." << endl;
				cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
				cout << "          attack minion -- Orders minion to attack the opponent." << endl;
				cout << "          play card [target-player target-card] -- ";
				cout << "Play card, optionally targeting target-card owned by target-player." << endl;
				cout << "          use minion [target-player target-card] -- "; 
				cout << "Use minion's special ability, optionally targeting target-card owned by target-player." << endl;
				cout << "          inspect minion -- View a minion's card and all enchantments on that minion." << endl;
				cout << "          hand -- Describe all cards in your hand." << endl;
				cout << "          board -- Describe all cards on the board." << endl;
			} else if (cmd == "quit") {
				quit = true;
		
			} else {
				cerr << "Invalid command." << endl;
				cerr << "Type \"help\" to show all possible command." << endl;
			}
			
			if (quit) break;
			cout << "Player " << turn + 1 << "'s turn:" << endl
		}



	} catch (ios::failure) {}
}


