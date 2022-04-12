#include <iostream>
#include <fstream>
using namespace std;

static const int DECK_SIZE = 60;

static const int CARD_NAME_SIZE = 64;
static const int PLAYER_NAME_SIZE = 128;
static const int COLOR_NAME_SIZE = 8;

static const int COMMAND_SIZE = 4096;
static const int COLORS_COUNT = 5;

static const int CARDS_MAX_COUNT = 32768;
static const int PLAYERS_MAX_COUNT = 128;
static const int DECKS_MAX_COUNT = 128;

static const char* PLAYERS_FILE = "players.dat";
static const char* CARDS_FILE = "cards.dat";
static const char* DECKS_FILE = "decks.dat";
static const char* REPORT_FILE = "report.txt";

struct Card
{
	unsigned short id;
	char name[CARD_NAME_SIZE];
	char color[COLOR_NAME_SIZE];
};

struct Player
{
	unsigned short id;
	char name[PLAYER_NAME_SIZE];
};

struct Deck
{
	unsigned short playerId;
	unsigned short cardIds[DECK_SIZE];
	char color[COLOR_NAME_SIZE];
};

unsigned short getCountOfStructs(const char* src, int sizeOfStruckt);
Card* loadCardsFromDB(int cardsCount);
Player* loadPlayersFromDB(int playersCount);
Deck* loadDecksFromDB(int decksCount);
bool executeCommand(char* commandLine, Card* allCards, Player* allPlayers, Deck* allDecks, unsigned short& cardsInDB, unsigned short& playersInDB, unsigned short& decksInDB);
bool createPlayer(Player* allPlayers, unsigned short& playersInDB);
bool createCard(Card* allCards, unsigned short& cardsInDB);
bool createDeck(Card* allCards, Player* allPlayers, Deck* allDecks, unsigned short& cardsInDB, unsigned short& playersInDB, unsigned short& decksInDB);
bool createReport(Card* allCards, Player* allPlayers, Deck* allDecks, unsigned short& decksInDB);
bool isCardExistInDB(char* cardName, Card* allCards, unsigned short& cardsInDB);
bool isPlayerExistInDB(char* playerName, Player* allPlayers, unsigned short& playersInDB);
int getPlayerId(char* playerName, Player* allPlayers, unsigned short& playersInDB);
int getCardId(char* cardName, Card* allCards, unsigned short& cardsInDB);
char* getColorOfDeck(const Deck& deck, Card* allCards);
int getMostCommonCardIndex(Deck* allDecks, unsigned short& decksInDB);
int getColorIndex(char* color);
void createFileIfNotExist(const char* src);
void writeCardToDB(const Card& card);
void writePlayerToDB(const Player& player);
void writeDeckToDB(const Deck& deck);

Card* loadCardsFromDB(int cardsCount)
{
	Card* allCards = new (std::nothrow) Card[CARDS_MAX_COUNT];

	if (!allCards)
	{
		cerr << "Cannot alocate array with size of " << CARDS_MAX_COUNT << " Cards" << endl;
		delete[] allCards;
		exit(0);
	}
	ifstream is(CARDS_FILE, ios::binary);
	if (is.good())
	{
		is.read((char*)allCards, cardsCount * sizeof(Card));

		if (is.good())
			cout << "Successfully read the cards from the data base." << endl;
		else
		{
			is.close();
			cerr << "Failed to read the cards from the data base." << endl;
			delete[] allCards;
			exit(0);
		}
	}
	else
	{
		is.close();
		cerr << "Failed to open " << CARDS_FILE << " file." << endl;
		delete[] allCards;
		exit(0);
	}

	return allCards;
}

Deck* loadDecksFromDB(int decksCount)
{
	Deck* allDecks = new (std::nothrow) Deck[DECKS_MAX_COUNT];

	if (!allDecks)
	{
		cerr << "Cannot alocate array with size of " << DECKS_MAX_COUNT << " Decks" << endl;
		delete[] allDecks;
		exit(0);
	}

	ifstream is(DECKS_FILE, ios::binary);

	if (is.good())
	{
		is.read((char*)allDecks, decksCount * sizeof(Deck));

		if (is.good())
			cout << "Successfully read the decks from the data base." << endl;
		else
		{
			is.close();
			cerr << "Failed to read the decks from the data base." << endl;
			delete[] allDecks;
			exit(0);
		}
	}
	else
	{
		is.close();
		cerr << "Failed open " << DECKS_FILE << " file." << endl;
		delete[] allDecks;
		exit(0);
	}

	return allDecks;
}

Player* loadPlayersFromDB(int playersCount)
{
	Player* allPlayers = new (std::nothrow) Player[PLAYERS_MAX_COUNT];

	if (!allPlayers)
	{
		cerr << "Cannot alocate array with size of " << PLAYERS_MAX_COUNT << " Players" << endl;
		delete[] allPlayers;
		exit(0);
	}

	ifstream is(PLAYERS_FILE, ios::binary);
	if (is.good())
	{
		is.read((char*)allPlayers, playersCount * sizeof(Player));

		if (is.good())
			cout << "Successfully read the players from the data base." << endl;
		else
		{
			is.close();
			cerr << "Failed to read the players from the data base." << endl;
			delete[] allPlayers;
			exit(0);
		}
	}
	else
	{
		is.close();
		cerr << "Failed open " << PLAYERS_FILE << " file." << endl;
		delete[] allPlayers;
		exit(0);
	}
	return allPlayers;
}

unsigned short getCountOfStructs(const char* fileName, int sizeOfStruct)
{
	createFileIfNotExist(fileName);
	ifstream is(fileName, ios::binary);
	int count = 0;
	if (is.good())
	{
		is.seekg(0, is.end);
		int structs = is.tellg() / sizeOfStruct;
		is.seekg(0, is.beg);

		count = structs;
		is.close();
	}
	else
	{
		is.close();
		cerr << "Failed to open the " << fileName << " file." << endl;
		exit(0);
	}

	return count;
}

void createFileIfNotExist(const char* src)
{
	ofstream f(src, ios::app);
	f.close();
}

bool executeCommand(char* commandLine, Card* allCards, Player* allPlayers, Deck* allDecks, unsigned short& cardsInDB, unsigned short& playersInDB, unsigned short& decksInDB)
{
	if (strlen(commandLine) == 0)
		return false;

	char* command = strtok(commandLine, " ");

	if (strcmp(command, "cc") == 0)
		return createCard(allCards, cardsInDB);
	else if (strcmp(command, "cp") == 0)
		return createPlayer(allPlayers, playersInDB);
	else if (strcmp(command, "cd") == 0)
		return createDeck(allCards, allPlayers, allDecks, cardsInDB, playersInDB, decksInDB);
	else if (strcmp(command, "report") == 0)
		return createReport(allCards, allPlayers, allDecks, decksInDB);

	return false;
}

bool createCard(Card* allCards, unsigned short& cardsInDB)
{
	char cardParams[COLOR_NAME_SIZE + CARD_NAME_SIZE];
	cin.getline(cardParams, COLOR_NAME_SIZE + CARD_NAME_SIZE);

	char* cardColor = strtok(cardParams, " ");
	char* cardName = strtok(NULL, "\n");

	if (getColorIndex(cardColor) == -1)
		return false;

	if (strlen(cardName) >= CARD_NAME_SIZE)
	{
		cerr << "Card name cannot be more than " << CARD_NAME_SIZE << " characters." << endl;
		return false;
	}

	if (isCardExistInDB(cardName, allCards, cardsInDB))
		return true;

	Card card;
	strcpy(card.color, cardColor);
	strcpy(card.name, cardName);
	card.id = cardsInDB++;

	allCards[card.id] = card;

	writeCardToDB(card);

	return true;
}

bool isCardExistInDB(char* cardName, Card* allCards, unsigned short& cardsInDB)
{
	for (size_t i = 0; i < cardsInDB; i++)
	{
		if (strcmp(allCards[i].name, cardName) == 0)
			return true;
	}

	return false;
}

bool createPlayer(Player* allPlayers, unsigned short& playersInDB)
{
	char playerName[PLAYER_NAME_SIZE];
	cin.getline(playerName, PLAYER_NAME_SIZE);

	if (strlen(playerName) >= PLAYER_NAME_SIZE)
	{
		cerr << "Player name cannot be more than " << PLAYER_NAME_SIZE << " characters." << endl;
		return false;
	}

	if (isPlayerExistInDB(playerName, allPlayers, playersInDB))
		return true;

	Player player;
	strcpy(player.name, playerName);
	player.id = playersInDB++;

	allPlayers[player.id] = player;

	writePlayerToDB(player);

	return true;
}

bool isPlayerExistInDB(char* playerName, Player* allPlayers, unsigned short& playersInDB)
{
	for (size_t i = 0; i < playersInDB; i++)
	{
		if (strcmp(allPlayers[i].name, playerName) == 0)
			return true;
	}

	return false;
}

bool createDeck(Card* allCards, Player* allPlayers, Deck* allDecks, unsigned short& cardsInDB, unsigned short& playersInDB, unsigned short& decksInDB)
{
	char playerName[PLAYER_NAME_SIZE];
	cin.getline(playerName, PLAYER_NAME_SIZE);

	if (!isPlayerExistInDB(playerName, allPlayers, playersInDB))
		return false;

	Deck deck;
	deck.playerId = getPlayerId(playerName, allPlayers, playersInDB);

	for (size_t i = 0; i < DECK_SIZE; i++)
	{
		char cardName[CARD_NAME_SIZE];
		cin.getline(cardName, CARD_NAME_SIZE);

		if (strlen(cardName) == 0)
		{
			cout << "Deck should contain exactly " << DECK_SIZE << " cards not " << i << endl;
			return false;
		}

		int cardId = getCardId(cardName, allCards, cardsInDB);

		if (cardId == -1)
			return false;

		deck.cardIds[i] = cardId;
	}

	strcpy(deck.color, getColorOfDeck(deck, allCards));
	allDecks[decksInDB] = deck;
	decksInDB++;

	writeDeckToDB(deck);

	return true;
}

int getPlayerId(char* playerName, Player* allPlayers, unsigned short& playersInDB)
{
	for (size_t i = 0; i < playersInDB; i++)
	{
		if (strcmp(allPlayers[i].name, playerName) == 0)
			return allPlayers[i].id;
	}

	return -1;
}

int getCardId(char* cardName, Card* allCards, unsigned short& cardsInDB)
{
	for (size_t i = 0; i < cardsInDB; i++)
	{
		if (strcmp(allCards[i].name, cardName) == 0)
			return allCards[i].id;
	}

	return -1;
}

char* getColorOfDeck(const Deck& deck, Card* allCards)
{
	// Red, Black, Blue, White, Green
	int colors[] = { 0, 0, 0, 0, 0 };

	for (size_t i = 0; i < DECK_SIZE; i++)
	{
		char* currentCardColor = allCards[deck.cardIds[i]].color;

		if (strcmp(currentCardColor, "Red") == 0)
			colors[0]++;
		else if (strcmp(currentCardColor, "Black") == 0)
			colors[1]++;
		else if (strcmp(currentCardColor, "Blue") == 0)
			colors[2]++;
		else if (strcmp(currentCardColor, "White") == 0)
			colors[3]++;
		else if (strcmp(currentCardColor, "Green") == 0)
			colors[4]++;
		else
			cerr << "Invalid card color " << currentCardColor << endl;
	}

	int cardsCount = -1;
	int index = -1;

	for (size_t i = 0; i < COLORS_COUNT; i++)
	{
		if (colors[i] > cardsCount)
		{
			cardsCount = colors[i];
			index = i;
		}
	}

	switch (index)
	{
	case 0: return "Red"; break;
	case 1: return "Black"; break;
	case 2: return "Blue"; break;
	case 3: return "White"; break;
	case 4: return "Green"; break;
	default: std::cerr << "Invalid color index" << std::endl; return NULL; break;
	}
}

bool createReport(Card* allCards, Player* allPlayers, Deck* allDecks, unsigned short& decksInDB)
{
	createFileIfNotExist(REPORT_FILE);

	ofstream os(REPORT_FILE, ios::trunc);

	if (!os)
	{
		os.close();
		return false;
	}

	for (size_t i = 0; i < COLORS_COUNT; i++)
	{
		switch (i)
		{
		case 0: os << "Red" << std::endl; break;
		case 1: os << "Black" << std::endl; break;
		case 2: os << "Blue" << std::endl; break;
		case 3: os << "White" << std::endl; break;
		case 4: os << "Green" << std::endl; break;
		}

		for (size_t j = 0; j < decksInDB; j++)
		{
			if (getColorIndex(allDecks[j].color) == i)
			{
				Player player = allPlayers[allDecks[j].playerId];
				Card firstCard = allCards[allDecks[j].cardIds[0]];

				os << "\t";
				os
					<< "Owner: " << player.name
					<< " Card: " << firstCard.name
					<< " Color: " << firstCard.color << endl;
			}
		}
	}

	os << endl;

	Card mostCommonCard = allCards[getMostCommonCardIndex(allDecks, decksInDB)];

	os << "Most common card: " << mostCommonCard.name
		<< " Color: " << mostCommonCard.color << endl;

	os.close();
	return true;
}

int getColorIndex(char* color)
{
	if (strcmp(color, "Red") == 0)
		return 0;
	else if (strcmp(color, "Black") == 0)
		return 1;
	else if (strcmp(color, "Blue") == 0)
		return 2;
	else if (strcmp(color, "White") == 0)
		return 3;
	else if (strcmp(color, "Green") == 0)
		return 4;
	else
	{
		cerr << "Invalid color " << color << endl;
		return -1;
	}
}

int getMostCommonCardIndex(Deck* allDecks, unsigned short& decksInDB)
{
	int* histogramOfCards = new (std::nothrow) int[CARDS_MAX_COUNT] { 0 };

	if (!histogramOfCards)
	{
		cerr << "Cannot alocate array with size of " << CARDS_MAX_COUNT << " integers" << endl;
		delete[] histogramOfCards;
		exit(0);
	}

	//Count sort (histogram)
	for (size_t deckIndex = 0; deckIndex < decksInDB; deckIndex++)
	{
		for (size_t cardIndex = 0; cardIndex < DECK_SIZE; cardIndex++)
		{
			histogramOfCards[allDecks[deckIndex].cardIds[cardIndex]]++;
		}
	}

	int index = -1;
	int value = -1;

	for (size_t i = 0; i < COLORS_COUNT; i++)
	{
		if (value < histogramOfCards[i])
		{
			value = histogramOfCards[i];
			index = i;
		}
	}

	delete[] histogramOfCards;

	return index;
}

void writeCardToDB(const Card& card)
{
	ofstream s("cards.dat", ios::binary | ios::app);
	s.write((char*)&card, sizeof(Card));
	s.close();
}

void writePlayerToDB(const Player& player)
{
	ofstream s("players.dat", ios::binary | ios::app);
	s.write((char*)&player, sizeof(Player));
	s.close();
}

void writeDeckToDB(const Deck& deck)
{
	ofstream s("decks.dat", ios::binary | ios::app);
	s.write((char*)&deck, sizeof(Deck));
	s.close();
}
