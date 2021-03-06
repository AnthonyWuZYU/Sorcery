#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"
#include "graveyard.h"
using namespace std;

void print_centre_graphic();
void print_top_border();
void print_bot_border();
void print_player(Player *player, int num);

int main(int argc, char *argv[])
{
	//istream *in = nullptr;
	string deck1_name = "default.deck";
	string deck2_name = "default.deck";
	string file_name = "";
	bool file = false;
	bool test = false;
	for (int i = 1; i < argc; i++)
	{
		stringstream arg(argv[i]);
		if (arg.str() == "-deck1" && i < argc - 1)
		{
			deck1_name = argv[i + 1];
		}
		if (arg.str() == "-deck2" && i < argc - 1)
		{
			deck2_name = argv[i + 1];
		}
		if (arg.str() == "-testing")
		{
			test = true;
		}
		if (arg.str() == "-init" && i < argc - 1)
		{
			file_name = argv[i + 1];
			file = true;
		}
	}

	ifstream in_file;
	if (file)
	{
		in_file = ifstream{file_name};
	}

	cin.exceptions(ios::failbit | ios::eofbit);
	string player1_name;
	string player2_name;

	try
	{
		if (!file)
		{
			//get player1's name
			while (player1_name.empty())
			{
				cout << "Player 1: ";
				getline(cin, player1_name);
				if (player1_name.empty())
					cerr << "Player name cannot be empty" << endl;
			}
			//get player2's name
			while (player2_name.empty())
			{
				cout << "Player 2: ";
				getline(cin, player2_name);
				if (player1_name.empty())
					cerr << "Player name cannot be empty" << endl;
			}
		}
		else
		{
			in_file >> player1_name;
			in_file >> player2_name;
		}

		Player player1{player1_name};
		Player player2{player2_name};

		// set opponent to each other
		player1.setOpp(&player2);
		player2.setOpp(&player1);

		// load deck
		Deck deck1 = Deck{deck1_name, test};
		Deck deck2 = Deck{deck2_name, test};
		Hand hand1, hand2;
		Graveyard grave1, grave2;

		Board board1 = Board{&deck1, &grave1, &hand1};
		Board board2 = Board{&deck2, &grave2, &hand2};

		player1.setBoard(&board1);
		player2.setBoard(&board2);

		string cmd;
		string option;
		unsigned int pos = 0;
		bool quit = false;

		// cursor set the player1 as the initial player
		Player *cur = player2.getOpp();
		// game start and magic add 1 each turn, the magic fill to its max
		cout << cur->getName() << "'s turn" << endl;
		cur->addMaxMagic(1);
		cur->setMagic(cur->getMaxMagic());
		cur->draw();

		while (true)
		{
			if (file && !in_file.eof())
			{
				in_file >> cmd;
			}
			else
			{
				cin >> cmd;
			}

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
				cur->getBoard()->trigger(cur, "end");
				cur = cur->getOpp();
				cur->addMaxMagic(1);
				cur->setMagic(cur->getMaxMagic());
				cur->reset_action();

				// draw cards
				cur->draw();

				// start of turn effect
				cur->getBoard()->trigger(cur, "start");
			}
			else if (cmd == "attack")
			{
				int j = 1000;
				if (file && !in_file.fail())
				{
					in_file >> pos;
				}
				else
				{
					cin >> pos;
				}

				if (cur->getOpp()->getBoard()->get_field().empty())
				{
					cur->minion_attack(pos - 1);
				}
				else
				{
					if (file && !in_file.fail())
					{
						in_file >> j;
					}
					else
					{
						cin >> j;
					}
					cur->minion_attack(pos - 1, j - 1);
				}
				if (cur->getOpp()->getLife() <= 0)
				{
					print_top_border();
					if (cur->getName() == player1_name)
					{
						print_player(cur, 1);
						cout << *cur->getBoard();
						print_centre_graphic();
						cout << *cur->getOpp()->getBoard();
						print_player(cur->getOpp(), 2);
					}
					else
					{
						print_player(cur->getOpp(), 1);
						cout << *cur->getOpp()->getBoard();
						print_centre_graphic();
						cout << *cur->getBoard();
						print_player(cur, 2);
					}
					print_bot_border();
					cout << cur->getName() << " won!" << endl;
					quit = true;
				}
			}
			else if (cmd == "board")
			{
				// show board
				print_top_border();

				if (cur->getName() == player1_name)
				{
					print_player(cur, 1);
					cout << *cur->getBoard();
					print_centre_graphic();
					cout << *cur->getOpp()->getBoard();
					print_player(cur->getOpp(), 2);
				}
				else
				{
					print_player(cur->getOpp(), 1);
					cout << *cur->getOpp()->getBoard();
					print_centre_graphic();
					cout << *cur->getBoard();
					print_player(cur, 2);
				}
				print_bot_border();
			}
			else if (cmd == "inspect")
			{
				if (file && !in_file.fail())
				{
					in_file >> pos;
				}
				else
				{
					cin >> pos;
				}
				if (pos <= cur->getBoard()->get_field().size() && pos > 0)
				{
					cur->getBoard()->get_card_field(pos - 1)->print(cout);
					Minion *target = dynamic_cast<Minion *>(cur->getBoard()->get_card_field(pos - 1));

					vector<vector<string>> to_print;
					for (auto it : target->get_enchant())
					{
						Enchant *enchant = dynamic_cast<Enchant *>(it);
						if (enchant->get_ability() == " ")
						{
							string atk, def;
							if (enchant->get_addAtk() > 0)
							{
								atk = "+";
								atk += to_string(enchant->get_addAtk());
							}
							else if (enchant->get_addAtk() < 0)
							{
								atk = to_string(enchant->get_addAtk());
							}
							else
							{
								atk = "*";
								atk += to_string(enchant->get_mulAtk());
							}
							if (enchant->get_addDef() > 0)
							{
								def = "+";
								def += to_string(enchant->get_addDef());
							}
							else if (enchant->get_addDef() < 0)
							{
								def = to_string(enchant->get_addDef());
							}
							else
							{
								def = "*";
								def += to_string(enchant->get_mulDef());
							}
							to_print.emplace_back(display_enchantment_attack_defence(enchant->get_name(), enchant->get_cost(), enchant->get_ability(), atk, def));
						}
						else
						{
							to_print.emplace_back(display_enchantment(enchant->get_name(), enchant->get_cost(), enchant->get_ability()));
						}
					}

					for (int i = 0; i < 11; i++)
					{
						for (auto it : to_print)
						{
							cout << it[i];
						}
						cout << endl;
					}
				}
				else
				{
					cerr << "No minion in this position" << endl;
				}
			}
			else if (cmd == "use")
			{
				if (file && !in_file.fail())
				{
					in_file >> pos;
				}
				else
				{
					cin >> pos;
				}
				bool silence = false;
				unsigned int field_size = cur->getBoard()->get_field().size();
				if (pos <= field_size && pos > 0)
				{
					Minion *temp_m = dynamic_cast<Minion *>(cur->getBoard()->get_card_field(pos - 1));
					for (auto it : temp_m->get_enchant())
					{
						if (it->get_name() == "Silence")
							silence = true;
					}
					if (!silence)
					{
						if (temp_m->get_action() != 0)
						{
							if (cur->getMagic() >= temp_m->get_activate_cost() || test)
							{
								if (temp_m->use_ability(cur)) {
									temp_m->set_action(0);
								}
							}
							else
							{
								cerr << "Not enough magic" << endl;
							}
						}
						else
						{
							cerr << "Minion doesn't have any actions" << endl;
						}
					}
					else
					{
						cerr << "The minion is silenced, can not use its ability" << endl;
					}
					temp_m = nullptr;
					delete temp_m;
				}
				else
				{
					cerr << "Wrong index" << endl;
				}
			}
			else if (cmd == "play")
			{
				if (file && !in_file.fail())
				{
					in_file >> pos;
				}
				else
				{
					cin >> pos;
				}
				cur->play_card(pos - 1, test);
			}
			else if (cmd == "quit")
			{
				quit = true;
			}
			else if (cmd == "draw" && test)
			{
				cur->draw();
			}
			else if (cmd == "discard" && test)
			{
				if (file && !in_file.fail())
				{
					in_file >> pos;
				}
				else
				{
					cin >> pos;
				}
				cur->getBoard()->get_hand()->remove(pos - 1);
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
		cerr << "failure" << endl;
	}
}

void print_centre_graphic()
{
	for (auto it : CENTRE_GRAPHIC)
	{
		cout << it << endl;
	}
}

void print_top_border()
{
	cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
	for (int i = 0; i < 165; i++)
	{
		cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
}

void print_bot_border()
{
	cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
	for (int i = 0; i < 165; i++)
	{
		cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
	}
	cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

void print_player(Player *player, int num)
{
	vector<vector<string>> to_print;

	if (player->getBoard()->get_ritual() != nullptr)
	{
		Ritual *temp = dynamic_cast<Ritual *>(player->getBoard()->get_ritual());
		to_print.emplace_back(display_ritual(temp->get_name(), temp->get_cost(), temp->getActivationCost(), temp->get_ability(),
											 temp->getCharges()));
	}
	else
	{
		to_print.emplace_back(CARD_TEMPLATE_BORDER);
	}
	to_print.emplace_back(CARD_TEMPLATE_EMPTY);
	to_print.emplace_back(display_player_card(num, player->getName(), player->getLife(), player->getMagic()));
	to_print.emplace_back(CARD_TEMPLATE_EMPTY);
	to_print.emplace_back(CARD_TEMPLATE_BORDER);

	for (int i = 0; i < 11; i++)
	{
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
		for (auto it : to_print)
		{
			cout << it[i];
		}
		cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
	}
}
