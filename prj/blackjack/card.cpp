#include "card.hpp"
#include <sstream>

Card::Card(Suit const suit, Rank const rank)
: suit_(suit)
, rank_(rank)
{

}


Card::~Card()
{

}


std::string Card::toString()
{
    std::stringstream ss;
    switch(rank_)
    {
        default:
            throw std::runtime_error("Invalid Rank.");

        case Rank::Two: ss << "Two of "; break;
        case Rank::Three: ss << "Three of "; break;
        case Rank::Four: ss << "Four of "; break;
        case Rank::Five: ss << "Five of "; break;
        case Rank::Six: ss << "Six of "; break;
        case Rank::Seven: ss << "Seven of "; break;
        case Rank::Eight: ss << "Eight of "; break;
        case Rank::Nine: ss << "Nine of "; break;
        case Rank::Ten: ss << "Ten of "; break;
        case Rank::Jack: ss << "Jack of "; break;
        case Rank::Queen: ss << "Queen of "; break;
        case Rank::King: ss << "King of "; break;
        case Rank::Ace: ss << "Ace of "; break;
    };

    switch(suit_)
    {
        case Suit::Spades: ss << "Spades"; break;
        case Suit::Clubs: ss << "Clubs"; break;
        case Suit::Hearts: ss << "Hearts"; break;
        case Suit::Diamonds: ss << "Diamonds"; break;

    }

    return ss.str();
}
