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

void print_centre_graphic();
void print_top_border();
void print_bot_border();
void print_player1(Player* player);
void print_player2(Player* player);

int main()
{
	//istream *in = nullptr;

	cin.exceptions(ios::failbit | ios::eofbit);
	string player1_name;
	string player2_name;

	try
	{
		//get player1's name
		while (player1_name.empty())
		{
			cout << "Player 1: ";
			getline(cin, player1_name);
			if (player1_name.empty())
				cerr << "Player name cannot be empty" << endl;
		}
		Player player1{player1_name};

		//get player2's name
		while (player2_name.empty())
		{
			cout << "Player 2: ";
			getline(cin, player2_name);
			if (player1_name.empty())
				cerr << "Player name cannot be empty" << endl;
		}
		Player player2{player2_name};

		// set opponent to each other
		player1.setOpp(&player2);
		player2.setOpp(&player1);

		// load deck
		Deck deck1 = Deck{"default.deck"};
		Deck deck2 = Deck{"default.deck"};
		Hand hand1, hand2;
		Graveyard grave1, grave2;

		//cout << deck1.pop().get_Name() << endl;

		Board board1 = Board{&deck1, &grave1, &hand1};
		Board board2 = Board{&deck2, &grave2, &hand2};

		player1.setBoard(&board1);
		player2.setBoard(&board2);

		string cmd;
		string option;

		int pos;

		// cursor set the player1 as the initial player
		Player *cur = player2.getOpp();

		// game start and magic add 1 each turn, the magic fill to its max
		cout << cur->getName() << "'s turn" << endl;
		cur->addMaxMagic(1);
		cur->setMagic(cur->getMaxMagic());
		cur->draw();
		//cout << "Card:" << cur->getBoard()->get_card_hand(0).get_Name() << endl;

		bool quit = false;

		while (cin >> cmd)
		{

			if (cmd == "help")
			{
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
			}
			else if (cmd == "hand")
			{
				// Displays cards in hand
				cout << *cur->getBoard()->get_hand() << endl;
				
			}
			else if (cmd == "end")
			{
				// end of turn effect
				cur = cur->getOpp();
				cur->addMaxMagic(1);
				cur->setMagic(cur->getMaxMagic());

				// draw cards
				cur->draw();

				// start of turn effect

			}
			else if (cmd == "attack")
			{
				int j = 1000;
				cin >> pos;
				cin >> j;
				
				// i(pos) th minion attack
				// if attack i j
				cur->minion_attack(pos, j);
				
			}
			else if (cmd == "hand")
			{
				// show hands
			}
			else if (cmd == "board")
			{
				// show board
				cout << *cur->getBoard();
				print_centre_graphic();
				cout << *cur->getOpp()->getBoard();
			}
			else if (cmd == "inspect")
			{
				cin >> pos;
				// inspect i(pos) th
			}
			else if (cmd == "use")
			{
				cin >> pos;
				// use i(pos) th
			}
			else if (cmd == "play")
			{
				cin >> pos;
				// use i(pos) th
				// if play i p t
				cur->play_card(pos);
			}
			else if (cmd == "quit")
			{
				quit = true;
			}
			else
			{
				cerr << "Invalid command." << endl;
				cerr << "Type \"help\" to show all possible command." << endl;
			}

			if (quit)
				break;

			cout << cur->getName() << "'s turn" << endl;
		}
	}
	catch (ios::failure)
	{
	}
}


void print_centre_graphic() {
	for (auto it: CENTRE_GRAPHIC) {
		cout << it << endl;
	}
}

void print_top_border() {

}

void print_bot_border() {

}
void print_player1(Player* player) {

}

void print_player2(Player* player) {

}
