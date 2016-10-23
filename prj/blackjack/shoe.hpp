#pragma once
#include "card.hpp"
#include <deque>

class Shoe
{
    public:
        Shoe(std::size_t const deckCount);
        ~Shoe();
        void shuffle();
        Card const drawOne();
        std::size_t getRemainingCardCount() const;
    private:
        std::size_t const deckCount_;
        size_t shoeIndex_;
        std::deque<Card> shoe_;

    void fillShoe(std::size_t const deckCount, std::deque<Card> & shoe);
    void fillShoeWithSuit(Suit const targetSuit, std::deque<Card> & shoe);
    void randomizeShoe(std::size_t const swapCount, std::deque<Card> & shoe);
};
