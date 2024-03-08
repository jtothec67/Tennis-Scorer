#include <iostream>
#include <ctime>

bool scoreCheck(int ans);
int getScore(int server, int scoreKeeping);
int gameCheck(int p1Score, int p2Score, bool isDeuce);
void displayScore(int p1Score, int p2Score);
int tiebreak(int server, int scoreKeeping);
void displayStats(int totalPointsPlayed, int totalp1ServePoints, int totalp2ServePoints, int totalp1ServePointsWon, int totalp2ServePointsWon, int p1GamesBroken, int p2GamesBroken);

int main()
{
	srand(time(0));
	int p1Score = 0;
	int p2Score = 0;
	bool matchWon = false;
	int p1GameScore = 0;
	int p2GameScore = 0;
	bool isDeuce = false;
	int tiebreakWinner = 0;

	int server = 0;
	int scoreKeeping = 0;

	int totalPointsPlayed = 0;
	int totalp1ServePoints = 0;
	int totalp2ServePoints = 0;
	int totalp1ServePointsWon = 0;
	int totalp2ServePointsWon = 0;
	int p1GamesBroken = 0;
	int p2GamesBroken = 0;

	do
	{
		std::cout << "Would you like to 1)enter scores manually or 2)have them randomly generated? (1 or 2): ";
		std::cin >> scoreKeeping;
		std::cout << "" << std::endl;

		if (scoreKeeping != 1 && scoreKeeping != 2)
		{
			std::cout << "That is not a valid option" << std::endl;
			std::cout << "" << std::endl;
		}
	} while (scoreKeeping != 1 && scoreKeeping != 2);

	do
	{
		std::cout << "Who is serving first? (1 or 2): ";
		std::cin >> server;
		std::cout << "" << std::endl;

		if (server != 1 && server != 2)
		{
			std::cout << "That is not a valid option" << std::endl;
			std::cout << "" << std::endl;
		}
	} while (server != 1 && server != 2);

	

	while (matchWon == false)
	{
		totalPointsPlayed++; //increase for stats at the end
		server == 1 ? totalp1ServePoints++ : totalp2ServePoints++;

		if (getScore(server, scoreKeeping) == 1) //increase score depending on who won the point
		{
			p1Score += 1;
			if (server == 1) totalp1ServePointsWon++;
		}
		else
		{
			p2Score += 1;
			if (server == 1) totalp2ServePointsWon++;
		}

		if (gameCheck(p1Score, p2Score, isDeuce) == 4) //if one player is at advantage and the other player wins
		{                                              //the points get put back to deuce (3,3)
			p1Score = 3;
			p2Score = 3;
			displayScore(p1Score, p2Score); //converts the integers used in p1Score and p2Score to tennis scoring
		}
		else if (gameCheck(p1Score, p2Score, isDeuce) == 3) //makes isDeuce variable set to true when the score
		{                                                   //is deuce (3,3)
			isDeuce = true;
			displayScore(p1Score, p2Score);
		}
		else if (!gameCheck(p1Score, p2Score, isDeuce)) //happens when it is not game or deuce
		{
			displayScore(p1Score, p2Score);
		}
		else if (gameCheck(p1Score, p2Score, isDeuce) == 1) //happens when player 1 has won a game
		{
			server == 2 ? p1GamesBroken++ : server = 1;
			p1GameScore += 1;
			std::cout << "" << std::endl;
			std::cout << "The score in games is now " << p1GameScore << "," << p2GameScore << std::endl;
			if (!((p1GameScore == 6 && p2GameScore == 6) || (p1GameScore == 6 && p2GameScore < 5) || (p2GameScore == 6 && p1GameScore < 5) || (p1GameScore == 7) || (p2GameScore == 7)))
			{
				server == 1 ? server = 2 : server = 1;
				std::cout << "It is player " << server << " to serve" << std::endl;
			}
			std::cout << "" << std::endl;
			p1Score = 0;
			p2Score = 0;
			isDeuce = false;
		}
		else if (gameCheck(p1Score, p2Score, isDeuce) == 2) //happens when player 2 has won a game
		{
			server == 1 ? p2GamesBroken++ : server = 2;
			p2GameScore += 1;
			std::cout << "" << std::endl;
			std::cout << "The score in games is now " << p1GameScore << "," << p2GameScore << std::endl;
			if (!((p1GameScore == 6 && p2GameScore == 6) || (p1GameScore == 6 && p2GameScore < 5) || (p2GameScore == 6 && p1GameScore < 5) || (p1GameScore == 7) || (p2GameScore == 7)))
			{
				server == 1 ? server = 2 : server = 1;
				std::cout << "It is player " << server << " to serve" << std::endl;
			}
			std::cout << "" << std::endl;
			p1Score = 0;
			p2Score = 0;
			isDeuce = false;
		}

		if (p1GameScore == 6 && p2GameScore == 6)
		{
			server == 1 ? server = 2 : server = 1;
			tiebreakWinner = tiebreak(server, scoreKeeping);
			std::cout << "" << std::endl;
		}

		if (tiebreakWinner == 1)
		{
			p1GameScore += 1;
		}
		else if (tiebreakWinner == 2)
		{
			p2GameScore += 1;
		}

		if (p1GameScore == 6 && p2GameScore < 5 || p1GameScore == 7) //if player 1 has reached enough games to win, a message is displayed and the program ends
		{
			std::cout << "Player 1 has won!" << std::endl;
			std::cout << "The final score was " << p1GameScore << "," << p2GameScore << std::endl;
			matchWon = true;
		}
		else if (p2GameScore == 6 && p1GameScore < 5 || p2GameScore == 7) //if player 2 has reached enough games to win, a message is displayed and the program ends
		{
			std::cout << "Player 2 has won!" << std::endl;
			std::cout << "The final score was " << p1GameScore << "," << p2GameScore << std::endl;
			matchWon = true;
		}
	}

	displayStats(totalPointsPlayed, totalp1ServePoints, totalp2ServePoints, totalp1ServePointsWon, totalp2ServePointsWon, p1GamesBroken, p2GamesBroken);
}

int getScore(int server, int scoreKeeping) //checks to see if option entered was valid and then returns the option entered if it is
{
	int wonPoint = 0;

	if (scoreKeeping == 1) //manual score keeping
	{
		do
		{
			std::cout << "Who won the last point? (1 or 2): ";
			std::cin >> wonPoint;

			if (scoreCheck(wonPoint) == false)
			{
				std::cout << "That is not a valid option" << std::endl;
			}
		} while (scoreCheck(wonPoint) == false);
	}
	else //automatic score keeping
	{
		wonPoint = 1 + (rand() % 10); //random number between 1 and 10
		if (wonPoint > 4)
		{
			wonPoint = server;
		}
		else
		{
			server == 1 ? wonPoint = 2 : wonPoint = 1;
		}
	}

	return wonPoint;
}

bool scoreCheck(int ans) //used in getScore() to check if the value entered is not 1 or 2
{
	bool score = true;

	if (ans != 1 && ans != 2)
	{
		score = false;
	}

	return score;
}

int gameCheck(int p1Score, int p2Score, bool isDeuce) //looks at the score and directs the program based on what
{                                                     //the score is
	if (p1Score == 3 && p2Score == 3) //this is deuce
	{
		return 3;
	}
	else if (p1Score == 4 && isDeuce == false || p1Score == 5 && isDeuce == true) //player 1 wins the game
	{
		return 1;
	}
	else if (p2Score == 4 && isDeuce == false || p2Score == 5 && isDeuce == true) //player 2 wins the game
	{
		return 2;
	}
	else if (p1Score == 4 && p2Score == 4 && isDeuce == true) //when one player was at advantage and the other
	{                                                         //player wins a point
		return 4;
	}
	else if ((p1Score == 4 || p2Score == 4) && isDeuce == true || p1Score < 4 && p2Score < 4) //a player goes to advantage,
	{																						  //or nothing special with the score
		return 0;
	}

	return -1; //something has broken
}

void displayScore(int p1Score, int p2Score) //converts the linear integers into tennis scoring
{
	int p1Display = 0;
	int p2Display = 0;
	bool p1Adv = false;
	bool p2Adv = false;

	switch (p1Score) {
	case 1:
		p1Display = 15;
		break;
	case 2:
		p1Display = 30;
		break;
	case 3:
		p1Display = 40;
		break;
	case 4:
		p1Adv = true; //unable to store "Adv" in an integer so have to do it this way using an if statement later
		break;
	}

	switch (p2Score) {
	case 1:
		p2Display = 15;
		break;
	case 2:
		p2Display = 30;
		break;
	case 3:
		p2Display = 40;
		break;
	case 4:
		p2Adv = true;
		break;
	}


	if (p1Adv == true) //player 1 has advantage
	{
		std::cout << "Adv," << p2Display << std::endl;
	}
	else if (p2Adv == true) //player 2 has advantage
	{
		std::cout << p1Display << ",Adv" << std::endl;
	}
	else //normal point
	{
		std::cout << p1Display << "," << p2Display << std::endl;
	}
}

int tiebreak(int server, int scoreKeeping)
{
	std::cout << "A tiebreak to 7 will now be played" << std::endl;
	std::cout << "player " << server << " will server first" << std::endl;
	std::cout << "" << std::endl;

	int servesInRow = 1;
	int p1Score = 0;
	int p2Score = 0;

	while (true)
	{
		servesInRow++;

		if (getScore(server, scoreKeeping) == 1) //increase score depending on who won the point
		{
			p1Score += 1;
		}
		else
		{
			p2Score += 1;
		}

		std::cout << p1Score << "," << p2Score << std::endl;

		if (p1Score == 7 && p2Score < 6)
		{
			return 1;
		}
		else if (p2Score == 7 && p1Score < 6)
		{
			return 2;
		}

		if (p2Score > 5 && p1Score > 5)
		{
			if ((p1Score - 2) == p2Score)
			{
				return 1;
			}
			else if ((p2Score - 2) == p1Score)
			{
				return 2;
			}
		}

		if (servesInRow == 2 && server == 1)
		{
			server = 2;
			servesInRow = 0;
			std::cout << "" << std::endl;
			std::cout << "Player " << server << " to serve" << std::endl;
		}
		else if (servesInRow == 2 && server == 2)
		{
			server = 1;
			servesInRow = 0;
			std::cout << "" << std::endl;
			std::cout << "Player " << server << " to serve" << std::endl;
		}
	}
}

void displayStats(int totalPointsPlayed, int totalp1ServePoints, int totalp2ServePoints, int totalp1ServePointsWon, int totalp2ServePointsWon, int p1GamesBroken, int p2GamesBroken)
{
	std::cout << "" << std::endl;
	std::cout << "" << std::endl;
	std::cout << totalPointsPlayed << " points were played in total" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Player 1 won " << totalp1ServePointsWon + (totalp2ServePoints - totalp2ServePointsWon) << " total points - " << (float(totalp1ServePointsWon + (totalp2ServePoints - totalp2ServePointsWon)) / float(totalPointsPlayed)) * 100 << "%" << std::endl;
	std::cout << "Player 2 won " << totalp2ServePointsWon + (totalp1ServePoints - totalp1ServePointsWon) << " total points - " << (float(totalp2ServePointsWon + (totalp1ServePoints - totalp1ServePointsWon)) / float(totalPointsPlayed)) * 100 << "%" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Player 1 won " << totalp1ServePointsWon << " service points out of " << totalp1ServePoints << " - " << (float(totalp1ServePointsWon) / float(totalp1ServePoints)) * 100 << "%" << std::endl;
	std::cout << "Player 2 won " << totalp2ServePointsWon << " service points out of " << totalp2ServePoints << " - " << (float(totalp2ServePointsWon) / float(totalp2ServePoints)) * 100 << "%" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "Player 1 broke " << p1GamesBroken << " games" << std::endl;
	std::cout << "Player 2 broke " << p2GamesBroken << " games" << std::endl;
}