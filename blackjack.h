#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <iostream>
#include <random>
#include <string>

#define RESET "\033[0m"
#define WHITE_BG "\033[47m"
#define RED_CARD "\033[1;47;31m"
#define BLACK_CARD "\033[1;47;30m"

inline void shuffleCards(std::string array[], int size) {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, size - 1);

    for (int i = 0; i < size; ++i) {
        int swap_index = distribution(generator);
        std::swap(array[i], array[swap_index]);
    }
}

inline void printCardNumber(const std::string& card, bool top) {
    char value = card[0] == '1' ? '0' : card[0];
    std::string color = (card.back() == 'D' || card.back() == 'H') ? RED_CARD : BLACK_CARD;
    if (top) {
        std::cout << color << "  " << value << "       " << RESET;
    } else {
        std::cout << color << "       " << value << "  " << RESET;
    }
}

inline void printCardPattern(const std::string& card, int line) {
    std::string color = (card.back() == 'D' || card.back() == 'H') ? RED_CARD : BLACK_CARD;
    switch (line) {
        case 1: std::cout << color << (card.back() == 'D' || card.back() == 'S' ? "    /\\    " : "   _  _   ") << RESET; break;
        case 2: std::cout << color << (card.back() == 'D' ? "   /  \\   " : card.back() == 'H' ? "  ( \\/ )  " : card.back() == 'C' ? "   (  )   " : "   /  \\   ") << RESET; break;
        case 3: std::cout << color << (card.back() == 'D' || card.back() == 'H' ? "   \\  /   " : "  (____)  ") << RESET; break;
        case 4: std::cout << color << (card.back() == 'D' || card.back() == 'H' ? "    \\/    " : "    ||    ") << RESET; break;
    }
}

inline void printHand(const std::string currentHand[], int cardHandSize) {
    for (int i = 0; i < cardHandSize; ++i) std::cout << WHITE_BG << "          " << RESET << (i < cardHandSize - 1 ? " " : "");
    std::cout << std::endl;

    for (int i = 0; i < cardHandSize; ++i) printCardNumber(currentHand[i], true);
    std::cout << std::endl;

    for (int line = 1; line <= 4; ++line) {
        for (int i = 0; i < cardHandSize; ++i) {
            printCardPattern(currentHand[i], line);
            if (i < cardHandSize - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < cardHandSize; ++i) printCardNumber(currentHand[i], false);
    std::cout << std::endl;

    for (int i = 0; i < cardHandSize; ++i) std::cout << WHITE_BG << "          " << RESET << (i < cardHandSize - 1 ? " " : "");
    std::cout << std::endl;
}

inline int calculatePoints(const std::string currentHand[], int cardHandSize) {
    int playerScore = 0;
    int aceCount = 0;

    for (int i = 0; i < cardHandSize; ++i) {
        char cardValue = currentHand[i][0];
        if (cardValue == 'A') {
            playerScore += 11;
            aceCount++;
        } else if (cardValue == 'K' || cardValue == 'Q' || cardValue == 'J' || currentHand[i].length() == 3) {
            playerScore += 10;
        } else {
            playerScore += cardValue - '0';
        }
    }

    while (playerScore > 21 && aceCount > 0) {
        playerScore -= 10;
        aceCount--;
    }

    return playerScore;
}

#endif // BLACKJACK_H
