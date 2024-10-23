#include <iostream>
#include <random>
#include "blackjack.h"

using namespace std;

const int INITIAL_HAND_SIZE = 2;
const int MAX_HAND_SIZE = 21;

void initializeHand(string hand[], int& handSize, string cardsArray[], int& cardIndex) {
    for (int i = 0; i < INITIAL_HAND_SIZE; ++i) {
        hand[handSize++] = cardsArray[cardIndex++];
    }
}

bool playerTurn(string currentHand[], int& cardHandSize, string cardsArray[], int& cDelt) {
    while (true) {
        system("clear");
        printHand(currentHand, cardHandSize);
        int playerScore = calculatePoints(currentHand, cardHandSize);
        cout << "Your Hand: " << playerScore << endl;

        if (playerScore >= 21) {
            return false;
        }

        cout << "Another Card? ([Y]/N): ";
        string choice;
        getline(cin, choice);
        
        if (toupper(choice[0]) == 'N') {
            return true;
        }

        currentHand[cardHandSize++] = cardsArray[cDelt++];
    }
}

void dealerTurn(string dealerCurrentHand[], int& dealerCardHandSize, string cardsArray[], int& cDelt) {
    while (true) {
        int dealerScore = calculatePoints(dealerCurrentHand, dealerCardHandSize);
        if (dealerScore < 17) {
            dealerCurrentHand[dealerCardHandSize++] = cardsArray[cDelt++];
        } else {
            break;
        }
    }
}

int main() {
    string cardsArray[52] = {
        "AH", "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "10H", "JH", "QH", "KH",
        "AD", "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "10D", "JD", "QD", "KD",
        "AS", "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "10S", "JS", "QS", "KS",
        "AC", "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "10C", "JC", "QC", "KC"
    };

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> dist(0, 51);

    while (true) {
        shuffleCards(cardsArray, 52);
        system("clear");

        int cDelt = 0;
        string currentHand[MAX_HAND_SIZE];
        int cardHandSize = 0;
        initializeHand(currentHand, cardHandSize, cardsArray, cDelt);

        if (!playerTurn(currentHand, cardHandSize, cardsArray, cDelt)) {
            cout << "You bust or hit 21!" << endl;
            continue;
        }

        string dealerCurrentHand[MAX_HAND_SIZE];
        int dealerCardHandSize = 0;
        initializeHand(dealerCurrentHand, dealerCardHandSize, cardsArray, cDelt);

        dealerTurn(dealerCurrentHand, dealerCardHandSize, cardsArray, cDelt);
        int dealerScore = calculatePoints(dealerCurrentHand, dealerCardHandSize);

        cout << "Dealer's Hand: " << dealerScore << endl;
        printHand(dealerCurrentHand, dealerCardHandSize);
        
        string outcome = determineOutcome(currentHand, cardHandSize, dealerCurrentHand, dealerCardHandSize);
        cout << outcome << endl;

        cout << "Play again ([Y]/N): ";
        string choice;
        getline(cin, choice);
        if (toupper(choice[0]) == 'N') {
            break;
        }
    }

    return 0;
}
