//
// Created by YUFEI GE 260825264
//
#ifndef BLACKJACK_H
#define BLACKJACK_H
#include <vector>
class Card{
    public:
     enum Rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK=10, QUEEN=10, KING=10};
     enum Type {CLUBS , DIAMONDS , HEARTS , SPADES };
     Rank rank;
     Type type;
    public:
     int getValue();//return the numerical value fo the card
     void displayCard();//print the card info
};
class Hand{
    protected:
    std::vector<Card> cards;
    public:
     void add(Card card);//add 1 card to the hand
     void clear();//removing all cards from hand
     int getTotal() const;//get the total sum of the cards numerical values
     void displayHand();//this is a helper method to display all cards on the hand
};

class Deck: public Hand{
    public:
     Deck();//helper constructor
     virtual ~Deck();//destructor
     void Populate();//create a standard deck of 52 cards
     void shuffle();//shuffle the cards
     void deal(Hand); // deal one card to a hand
};

class AbstractPlayer: public Hand{
    public:
     virtual bool isDrawing() const = 0;//indicates whether the player wants to draw another card
     bool isBusted();//returns whether the player BUSTED (>21)
};

class ComputerPlayer: public AbstractPlayer{
    public:
    bool isDrawing() const;
};

class HumanPlayer : public AbstractPlayer{
public:
    void announce(char);
    bool isDrawing() const;
};


class BlackJackGame{
    private:
     Deck m_deck;
     ComputerPlayer m_casino;
    public:
    void play();
};







#endif BLACKJACK_H
