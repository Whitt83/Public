#pragma once

#include <string>

enum class Suit
{
    Spades,
    Clubs,
    Hearts,
    Diamonds
};

enum class Rank : uint8_t
{
    Two = 2,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    INVALID1,
    INVALID2
};

Rank operator + (Rank lhs, int const & rhs);

class Card
{
    public:
        Card(Suit const suit, Rank const rank);
        ~Card();

        std::string toString();

        Suit suit_;
        Rank rank_;

};
