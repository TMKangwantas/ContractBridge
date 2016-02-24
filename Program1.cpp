/*
 * Program1.cpp
 *
 *  Created on: Feb 3, 2016
 *      Author: Mark
 */
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main()
{
	int numHands = 0; //The number of valid hands
	int hand = 13; //The correct number of cards in a valid hand
	int cards = 0; //Cards in your hand currently. CANNOT EXCEED 13
	vector<string> bridge; //The bridge is what cards are in your current hand
	string input;
	string card;
	bool duplicate;
	while(true)
	{
		int ace = 0, king = 0, queen = 0, jack = 0, d = 0, c = 0, s = 0, h = 0;


		while(cards <= hand) //While the amount of cards is less than 13
		{
			int points = 0; /*Keeping points of the current valid hand
							 *it's inside this while loop because then it
							 *doesn't need to get reset every time a new valid
							 *hand comes in
							 */

			getline(cin,input);

			if (input != ".")
			{
				if(cin.peek() == EOF)
				{
					return 0;
				}

				replace(input.begin(), input.end(), ',', ' ');

				stringstream iss;
				string temp;

				iss.str(input);

				while (getline(iss, temp, ' '))
				{
					bridge.push_back(temp);
				}

				cards = bridge.size();

				for (vector<string>::const_iterator alpha = bridge.begin(); alpha != bridge.end(); alpha++)
				{
					string beta;
					beta = *alpha;
					//BAD FORMATTING
					if ((beta[0] == 'D') | (beta[0] == 'C') | (beta[0] == 'S') | (beta[0] == 'H')
							| (beta[beta.length()-1] == '.'))
					{
						cout << "BAD FORMAT" << endl;
						bridge.clear();
						cards = 0;
						break;
					}
				}
			}

			if (cards == 0)
				break;

			if (input == ".") //if the user will no longer input any cards
			{
 				if (bridge.size() > 1)
				{
					card = bridge[0];
					if (islower(card[0]))
					{

						cards = 0;
						bridge.clear();
						cout << "BAD FORMAT" << endl;
						break;
					}
				}
				if ((cards > hand) || (cards < hand))	//count amount of cards in hand, if invalid number,
																		//then break out of loop and start over
				{
					cout << "WRONG NUMBER OF CARDS" << endl;
					bridge.clear();
					cards = 0;
					break;
				}

				for (int i = 0; i < hand; i++)
				{
					card = (bridge[i]);

					//BAD FORMATTING
					if ((card[0] == 'D') || (card[0] == 'C')
							|| (card[0] == 'S') || (card[0] == 'H') ||
							(islower(card[0])) || (islower(card[card.length()-1]))
							|| (card[card.length()-1] == '.'))
					{
						cout << "BAD FORMAT" << endl;
						bridge.clear();
						cards = 0;
						break;
					}
				}

				if (cards == 0)
					break;

				vector<string> temp;

				for (vector<string>::const_iterator it = bridge.begin(); it != bridge.end(); it++)
				{
					card = *it;
					duplicate = (find(temp.begin(),temp.end(), card) != temp.end());

					if(temp.empty())
					{
						temp.push_back(card);
					}

					else
					{
						if (duplicate)
						{
							bridge.clear();
							cards = 0;
							cout << "DUPLICATE CARDS" << endl;
							break;
						}
						else
							temp.push_back(card);
					}
				}
				if (cards == 0)
					break;

				if (cards == hand) //if there are 13 cards in your hand; valid hand

				//******************************************
				//Start counting points and stuff
				//******************************************

				{
					numHands++;
					for (vector<string>::const_iterator it = bridge.begin(); it != bridge.end(); it++)
					{

						string mu; //mu is the card through each iteration
						mu = *it;
						//Checks the type of the card

						if(mu[0] == 'A') //check to see if card is an Ace
							ace++;
						else if (mu[0] == 'K') //check for King
							king++;
						else if (mu[0] == 'Q') //check for Queen
							queen++;
						else if (mu[0] == 'J') //check for Jack
							jack++;

						if(mu[mu.length()-1] == 'D') //check to see if card is a Diamond
							d++;
						else if (mu[mu.length()-1] == 'C') //check for Club
							c++;
						else if (mu[mu.length()-1] == 'S') //check for Spade
							s++;
						else if (mu[mu.length()-1] == 'H') //check for Heart
							h++;
					}
						/*
						 * Counting the points
						 */
						if(ace == 0)
							points--;
						else if(ace == 4)
							points++;


						if (ace >= 1 && ace != 4)
							points += (ace*4);
						if (king >= 1)
							points += (3*king);
						if (queen >= 1)
							points += (2*queen);
						if (jack >= 1)
							points += jack;


						if(king == 1)
							points--;
						if(queen == 1)
							points--;
						if(jack == 1)
							points--;

						if (d == 0)
							points += 3;
						if (c == 0)
							points += 3;
						if (s == 0)
							points += 3;
						if (h == 0)
							points += 3;


						if (d == 1)
							points += 2;
						if (c == 1)
							points += 2;
						if (s == 1)
							points += 2;
						if (h == 1)
							points += 2;

						if (d == 2)
							points ++;
						if (c == 2)
							points ++;
						if (s == 2)
							points ++;
						if (h == 2)
							points ++;


						if (d > 4)
						{
							points += (d-4);
						}
						else if (c > 4)
						{
							points += (c-4);
						}
						else if (s > 4)
						{
							points += (s-4);
						}
						else if (h > 4)
						{
							points += (h-4);
						}


						cout << "HAND " << numHands << " TOTAL POINTS " << points << endl;
						cards = 0;
						bridge.clear();
						break;

					}
				}

			if (cards > hand)
			{
				cout << "WRONG NUMBER OF CARDS" << endl;
				bridge.clear();
				cards = 0;
				break;
			}
//			while(iss >> card)
//			{
//
////				//duplicate is a boolean to check if the card is in the vector
////				duplicate = (find(bridge.begin(), bridge.end(), card) != bridge.end());
////
//
//
////				//DUPLICATE
////				if (duplicate) //if duplicate is true, then throw the error and clear the vector
////				{
////					cout << "DUPLICATE CARDS" << endl;
////					bridge.clear();
////					cards = 0;
////					break;
////				}
//				if (bridge.empty())
//				{
//					bridge.push_back(card);
//					cards++;
//					continue;
//				}
//				else
//				{
//					bridge.push_back(card);
//					cards++; //valid card gets added to hand, # of cards +1
//					continue;
//				}
//			}
		}

		if (cin.peek() == EOF)
		{
			return 0;
		}
	}
	return 0;

}
