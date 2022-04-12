#include <iostream>
#include "Header.h"
using namespace std;


int main()
{
	unsigned short cardsInDB = getCountOfStructs(CARDS_FILE, sizeof(Card));
	Card* allCards = loadCardsFromDB(cardsInDB);

	unsigned short playersInDB = getCountOfStructs(PLAYERS_FILE, sizeof(Player));
	Player* allPlayers = loadPlayersFromDB(playersInDB);

	unsigned short decksInDB = getCountOfStructs(DECKS_FILE, sizeof(Deck));
	Deck* allDecks = loadDecksFromDB(decksInDB);

	char command[COMMAND_SIZE];

	while (true)
	{
		cin.getline(command, COMMAND_SIZE);
		if (!executeCommand(command,
			allCards, allPlayers, allDecks,
			cardsInDB, playersInDB, decksInDB))
			break;
	}

	delete[] allCards;
	delete[] allPlayers;
	delete[] allDecks;

	system("pause");
	return 0;
}

