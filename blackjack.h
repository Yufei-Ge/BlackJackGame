//
// Created by YUFEI GE 260825264
//
//#ifndef COMP322_ASSN2_BLACKJACK_H
//#define COMP322_ASSN2_BLACKJACK_H
class Card{
    private:
     enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
     enum type {CLUBS, DIAMONDS, HEARTS, SPADES};
    public:
     int getValue(rank);//return the numerical value fo the card
     void displayCard();//print the card info
};
class Hand{
    private:
     Card cards;
    public:
     void add();//add card to the hand
     void clear();//removing all cards from hand
     int getTotal();//get the total sum of the cards numerical values
};

class Deck: public Hand{ //I decided to make Deck an inheritence from Hand
    public:
     void Populate();//create a standard deck of 52 cards
     void shuffle();//shuffle the cards
     void deal(); // deal one card to a hand
};
class AbstractPlayer : public Hand{
    private:
    public:
     virtual bool isDrawing() const = 0;//indicates whether the player wants to draw another card
     bool isBusted(player);//returns whether the player BUSTED (>21)
};
class HumanPlayer : AbstractPlayer{
    public:
    bool isDrawing();
    void annouce();
};




class blackjack {

};


//#endif //COMP322_ASSN2_BLACKJACK_H
