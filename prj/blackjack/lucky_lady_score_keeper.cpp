#include "lucky_lady_score_keeper.hpp"
#include <sstream>
#include <iomanip>

LuckyLadyScoreKeeper::LuckyLadyScoreKeeper()
: totalHands_(0)
, twenty_(0)
, suitedTwenty_(0)
, matchedTwenty_(0)
, qhTwenty_(0)
, qhTwenty_DealerBlackjack_(0)
{

}


LuckyLadyScoreKeeper::~LuckyLadyScoreKeeper()
{


}
size_t LuckyLadyScoreKeeper::getHandCount() const
{
    return totalHands_;
}

size_t LuckyLadyScoreKeeper::getWinCounter() const
{
    return twenty_ + suitedTwenty_ + matchedTwenty_ + qhTwenty_ + qhTwenty_DealerBlackjack_;
}

size_t LuckyLadyScoreKeeper::getWeightedWinCounter() const
{
    return 4 * twenty_ + 9 * suitedTwenty_ + 19 * matchedTwenty_ + 250 * qhTwenty_ + 1000 * qhTwenty_DealerBlackjack_;
}

void LuckyLadyScoreKeeper::formatLine(std::stringstream & ss, std::string const & tag, size_t const winCount, size_t const handCount)
{
    float const o1 = (float) winCount / (float) handCount;
    ss << std::left << std::setw(25) << tag  << std::right << std::setw(15) << std::setfill(' ') << winCount << "\t" <<  std::setprecision(6) << o1 << std::endl;
}
std::string LuckyLadyScoreKeeper::toString()
{
    std::stringstream ss;
    ss << "*** Summary *** " << std::endl;
    ss << std::left << std::setw(25) << "Total Hands:"  << std::right << std::setw(15) << std::setfill(' ') << totalHands_ << std::endl;
    formatLine(ss, "Twenty:", twenty_, totalHands_);
    formatLine(ss, "Suited Twenties:", suitedTwenty_, totalHands_);
    formatLine(ss, "Matched Twenties:", matchedTwenty_, totalHands_);
    formatLine(ss, "QoH Twenties:", qhTwenty_, totalHands_);
    formatLine(ss, "QoH Twenties with BJ:", qhTwenty_DealerBlackjack_, totalHands_);
    ss << std::endl;
    ss << std::left << std::setw(25) << "Chance of any payout:" << std::right << std::setw(15) << std::setfill(' ') << " " << "\t" << std::setprecision(6) << (((float) getWinCounter()) / (float) totalHands_) << std::endl;
    ss << std::left << std::setw(25) << "Return:" << std::right << std::setw(15) << std::setfill(' ') << " " << "\t" << std::setprecision(6) << (((float) getWeightedWinCounter()) / totalHands_) << std::endl;
    return ss.str();
}


bool LuckyLadyScoreKeeper::hasBlackjack(std::vector<Card> const & hand)
{
    size_t cardSummation = 0;

    switch(hand[0].rank_)
    {
        case Rank::Two: cardSummation += 2; break;
        case Rank::Three: cardSummation += 3; break;
        case Rank::Four: cardSummation += 4; break;
        case Rank::Five: cardSummation += 5; break;
        case Rank::Six: cardSummation += 6; break;
        case Rank::Seven: cardSummation += 7; break;
        case Rank::Eight: cardSummation += 8; break;
        case Rank::Nine: cardSummation += 9; break;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            cardSummation += 10; break;

        case Rank::Ace: cardSummation += 11; break;
    };


    switch(hand[1].rank_)
    {
        case Rank::Two: cardSummation += 2; break;
        case Rank::Three: cardSummation += 3; break;
        case Rank::Four: cardSummation += 4; break;
        case Rank::Five: cardSummation += 5; break;
        case Rank::Six: cardSummation += 6; break;
        case Rank::Seven: cardSummation += 7; break;
        case Rank::Eight: cardSummation += 8; break;
        case Rank::Nine: cardSummation += 9; break;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            cardSummation += 10; break;

        case Rank::Ace: cardSummation += 11; break;
    };

    return (cardSummation == 21);
}

void LuckyLadyScoreKeeper::evaluateHand(std::vector<Card> const & dealerHand, std::vector<Card> const & playerHand)
{
    if (playerHand.size() != 2)
    {
        return;
    }
    totalHands_++;

    /* Does the player's hand equal 20? */
    size_t cardSummation = 0;


    switch(playerHand[0].rank_)
    {
        default: return;
        case Rank::Two: cardSummation += 2; break;
        case Rank::Three: cardSummation += 3; break;
        case Rank::Four: cardSummation += 4; break;
        case Rank::Five: cardSummation += 5; break;
        case Rank::Six: cardSummation += 6; break;
        case Rank::Seven: cardSummation += 7; break;
        case Rank::Eight: cardSummation += 8; break;
        case Rank::Nine: cardSummation += 9; break;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            cardSummation += 10; break;

        case Rank::Ace: cardSummation += 0; break;
    };

    switch(playerHand[1].rank_)
    {
        default: return;
        case Rank::Two: cardSummation += 2; break;
        case Rank::Three: cardSummation += 3; break;
        case Rank::Four: cardSummation += 4; break;
        case Rank::Five: cardSummation += 5; break;
        case Rank::Six: cardSummation += 6; break;
        case Rank::Seven: cardSummation += 7; break;
        case Rank::Eight: cardSummation += 8; break;
        case Rank::Nine: cardSummation += 9; break;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            cardSummation += 10; break;

        case Rank::Ace: cardSummation += 0; break;
    };

    /* Is either card an Ace? */
    if ( ( (playerHand[0].rank_ == Rank::Ace)  || (playerHand[1].rank_ == Rank::Ace) ) &&
        ( (playerHand[0].rank_ == Rank::Nine)  || (playerHand[1].rank_ == Rank::Nine) ) )
    {
        cardSummation = 20;
    }

    if (cardSummation == 20)
    {
        if (playerHand[0].suit_ == playerHand[1].suit_)
        {
            if (playerHand[0].rank_ == playerHand[1].rank_)
            {
                if ( (playerHand[0].rank_ == Rank::Queen) && (playerHand[0].suit_ == Suit::Hearts) )
                {
                    if (true == hasBlackjack(dealerHand))
                    {
                        qhTwenty_DealerBlackjack_++;
                    }
                    else
                    {
                        qhTwenty_++;
                    }
                }
                else
                {
                    matchedTwenty_++;
                }
            }
            else
            {
                suitedTwenty_++;
            }
        }
        else
        {
            twenty_++;
        }
    }
}
