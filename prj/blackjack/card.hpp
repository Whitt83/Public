#pragma once

#include <string>

enum class Suit
{
    Spades,
    Clubs,
    Hearts,
    Diamonds
};

enum class Rank
{
    Two,
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
    Ace
};



class Card
{
    public:
        Card(Suit const suit, Rank const rank);
        ~Card();

        std::string toString();

        Suit suit_;
        Rank rank_;

};
