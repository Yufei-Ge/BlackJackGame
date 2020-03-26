
#include "blackjack.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <cstdlib>



using namespace std;


int Card::getValue() {
    int n = rank;
    return n;
}
void Card::displayCard() {
    char temp = 't';
    switch(type){
        case CLUBS: temp = 'C';
        case DIAMONDS: temp = 'D' ;
        case HEARTS: temp = 'H';
        case SPADES: temp = 'S';
    }
    if (rank == JACK ){
        std::cout<<"J"<< temp << endl;
    } else if (rank == KING){
        std::cout<<"K"<< temp << endl;
    } else if (rank == QUEEN){
        std::cout<<"Q"<< temp << endl;
    } else {
        std::cout<< Card::getValue()<< temp<<" ";
    }
}

void Hand::add(Card card) {
    cards.push_back(card);
}

void Hand::clear(){ //this method delete all cards in hand
    cards.clear();
}

int Hand::getTotal() const{
    int count = 0;
    int num_of_aces = 0;
    for (int i = 0; i < cards.size(); i++)
    {
        Card c = cards[i];
        if (c.getValue() == 11){
            num_of_aces += 1;
            count += 1;
        }
        else
            count = count + c.getValue();
    }
    for (int i = 0; i < num_of_aces; i++) {
        if (count + 10 <= 21)
            count += 10;
        return count;
    }
    return count;
}
void Hand::displayHand() {//helper function to display cards in hand
    for (int i=0; i<cards.size(); i++){
        cards[i].displayCard();
    }
}

Deck::Deck() {//helper del-defined constructor
    cards.reserve(52);
    Populate();
}

void Deck::Populate() {
    for (int i=0; i < 13; i++){
        cards[i].rank = Card::Rank(i+1);//To cast int value back to corresponding Rank value
        cards[i].type = Card::DIAMONDS;//the DIAMONDS deck
    }
    for (int i=13; i < 26; i++){
        cards[i].rank = Card::Rank(i-12);
        cards[i].type = Card::CLUBS;
    }
    for (int i=26; i < 39; i++){
        cards[i].rank = Card::Rank(i-25);
        cards[i].type = Card::HEARTS;
    }
    for (int i=39; i < 52; i++){
        cards[i].rank = Card::Rank(i-38);
        cards[i].type = Card::SPADES;
    }
}

void Deck::shuffle(){
    std::random_shuffle (cards.begin(), cards.end());
}

void Deck::deal(Hand player) {
    if (!cards.empty())//when deck here is not empty
    {
        player.add(cards.back());//deal a card to player hand
        cards.pop_back();//get rid of it in deck
    }
}

bool AbstractPlayer::isBusted(){
    if (getTotal() > 21){//when exceed 21 is busted
        return true;
    } else
        return false;
}

bool HumanPlayer::isDrawing() const{//override isdrawing in abstractplayer to see if human wants to draw
    std::cout<<"Would you like to draw? (y/n)"<<endl;
    char answer;
    std::cin >> answer;
    if (answer == 'y')
        return true;
    else
        return false;
}

void HumanPlayer::announce(char c){//to announce if this player win/lose/push
    if (c=='w'){
        std::cout<<"Player wins!"<<endl;
    }else if (c=='p'){
        std::cout<<"Push:No one wins"<<endl;
    }else if (c=='b'){
        std::cout<<"Player busted!"<<endl;
    }
}

bool ComputerPlayer::isDrawing() const{
    if (ComputerPlayer::Hand::getTotal()>16)
        return false;//stop when total in casino hand >16
    else
        return true;
}

void BlackJackGame::play() {
    HumanPlayer player;
    m_deck.Populate();//generate standard deck on m_deck
    m_deck.shuffle();//shuffle the standard deck

    //at the very beginning, casino dealt 1 card; player dealt 2 cards
    cout<< "Casino: ";
    m_deck.deal(m_casino);//deal 1 card to casino hand
    m_casino.displayHand();
    cout << "["<< m_casino.getTotal() <<"]"<<endl;//display cards in casino hand

    cout<< "Player: ";
    m_deck.deal(player);
    m_deck.deal(player);//first deal player with 2 cards
    player.displayHand();
    cout << "["<< player.getTotal() <<"]"<<endl;//display cards in player hand

    while(player.isDrawing()) {//when player is still drawing
        cout << "Player: ";
        m_deck.deal(player);
        player.displayHand();
        cout << "[" << player.getTotal() << "]" << endl;
        if(player.isBusted()) {
            player.announce('b');//player definitely busted and break out of this loop
            break;
        }
    }
    //when player do not want to draw, it is time for casino
    while(m_casino.isDrawing()){
        cout<< "Casino: ";
        m_deck.deal(m_casino);//deal 1 card to casino hand
        m_casino.displayHand();
        cout << "["<< m_casino.getTotal() <<"]"<<endl;//display cards in casino hand
    }
    if (m_casino.getTotal()==player.getTotal()){
        player.announce('p');//this is a push situation
    }else if(m_casino.getTotal()==21){//when two total != and casino reach 21 precisely
        std::cout<<"Casino wins!"<<endl;
    }else if (m_casino.getTotal()> 21 && player.getTotal()==21){//when casino busts and player=21 precisely
        player.announce('w');
        std::cout<<"Casino busts!"<<endl;
    }else if(m_casino.getTotal()<21){
        if(m_casino.getTotal()< player.getTotal()){//when 2 total are both <21, larger wins
            player.announce('w');
        }else if (m_casino.getTotal()>player.getTotal()){
            std::cout<<"Casino wins!"<<endl;
        }else if (player.getTotal()==21){
            player.announce('w');//when casino <21 and player precisely 21
        }
    }

    //clear all cards on hands
    m_casino.clear();
    player.clear();
}






