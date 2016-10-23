#include "shoe.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>


Shoe::Shoe(std::size_t const deckCount)
: deckCount_(deckCount)
, shoeIndex_(0)
{
    fillShoe(deckCount_, shoe_);
}

Shoe::~Shoe()
{

}


void Shoe::shuffle()
{
    /* Populate our deck vector with the number of cards as appropriate */
    shoeIndex_ = 0;
    randomizeShoe(25000, shoe_);

}

std::size_t Shoe::getRemainingCardCount() const
{
    return shoe_.size() - shoeIndex_;
}

Card const Shoe::drawOne()
{
    /* Get the top card */
    return  shoe_[shoeIndex_++];
}


void Shoe::fillShoe(std::size_t const deckCount, std::deque<Card> & shoe)
{
    shoe.clear();
    for (std::size_t i = 0; i < deckCount; i++)
    {
        fillShoeWithSuit(Suit::Hearts, shoe);
        fillShoeWithSuit(Suit::Diamonds, shoe);
        fillShoeWithSuit(Suit::Clubs, shoe);
        fillShoeWithSuit(Suit::Hearts, shoe);
    }

}

void Shoe::fillShoeWithSuit(Suit const targetSuit, std::deque<Card> & shoe)
{
    shoe.push_back(Card(targetSuit, Rank::Two));
    shoe.push_back(Card(targetSuit, Rank::Three));
    shoe.push_back(Card(targetSuit, Rank::Four));
    shoe.push_back(Card(targetSuit, Rank::Five));
    shoe.push_back(Card(targetSuit, Rank::Six));
    shoe.push_back(Card(targetSuit, Rank::Seven));
    shoe.push_back(Card(targetSuit, Rank::Eight));
    shoe.push_back(Card(targetSuit, Rank::Nine));
    shoe.push_back(Card(targetSuit, Rank::Ten));
    shoe.push_back(Card(targetSuit, Rank::Jack));
    shoe.push_back(Card(targetSuit, Rank::Queen));
    shoe.push_back(Card(targetSuit, Rank::King));
    shoe.push_back(Card(targetSuit, Rank::Ace));
}

void Shoe::randomizeShoe(std::size_t const swapCount, std::deque<Card> & shoe)
{
    /* Seed RNG */
    srand(time(nullptr));
    Card temporaryCard(Suit::Hearts, Rank::Queen);

    for (std::size_t i = 0; i < swapCount; i++)
    {
        std::size_t const card1 = rand() % shoe.size();
        std::size_t const card2 = rand() % shoe.size();

        temporaryCard = shoe[card1];
        shoe[card1] = shoe[card2];
        shoe[card2] = temporaryCard;
    }

}
