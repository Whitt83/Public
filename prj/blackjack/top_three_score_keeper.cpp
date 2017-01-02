#include "top_three_score_keeper.hpp"
#include <sstream>
#include <algorithm>

TopThreeScoreKeeper::TopThreeScoreKeeper()
: totalHands_(0)
, n3flush_(0)
, n3straight_(0)
, n3threeOfAKind_(0)
, t3suited3K_(0)
, t3straightFlush_(0)
, t3nonsuited3K_(0)
{

}


TopThreeScoreKeeper::~TopThreeScoreKeeper()
{


}
size_t TopThreeScoreKeeper::getHandCount() const
{
    return totalHands_;
}

size_t TopThreeScoreKeeper::getNormalWinCounter() const
{
    return n3flush_ + n3straight_ + n3threeOfAKind_;
}

size_t TopThreeScoreKeeper::getNormalWeightedWinCounter() const
{
    return (n3flush_ + n3straight_ + n3threeOfAKind_) * 9;
}

size_t TopThreeScoreKeeper::getTopWinCounter() const
{
    return t3suited3K_ + t3straightFlush_ + t3nonsuited3K_;
}

size_t TopThreeScoreKeeper::getTopWeightedWinCounter() const
{
    return t3suited3K_ * 270 + t3straightFlush_ * 180 + t3nonsuited3K_ * 90;
}

std::string TopThreeScoreKeeper::toString()
{
    std::stringstream ss;

    ss << "*** Top 3 Summary *** " << std::endl;
    ss << "Total Hands: " << totalHands_ << std::endl;
    ss << "Normal 3 Wins: " << getNormalWinCounter() << std::endl;
    ss << "Top 3 (3 of a kind): " << t3nonsuited3K_ << std::endl;
    ss << "Top 3 - Straight Flush: " << t3straightFlush_ << std::endl;
    ss << "Top 3 - Matched 3 of a kind: " << t3suited3K_ << std::endl;

    return ss.str();
}


void TopThreeScoreKeeper::evaluateHand(std::vector<Card> const & dealerHand, std::vector<Card> const & playerHand)
{
    if (playerHand.size() != 2)
    {
        return;
    }

    totalHands_++;

    /* Normal 3 first */
    if ((playerHand[0].rank_ == playerHand[1].rank_) && (playerHand[1].rank_ == dealerHand[0].rank_))
    {
        n3threeOfAKind_++;
    }
    else if ((playerHand[0].suit_ == playerHand[1].suit_) && (playerHand[1].suit_ == dealerHand[0].suit_))
    {
        n3flush_++;
    }
    else if (false)
    {
        /* Sort the cards */
        Rank const lowestRank = std::min(std::min(playerHand[0].rank_, playerHand[1].rank_), dealerHand[0].rank_);
        std::vector<Rank> const ranks = {playerHand[0].rank_, playerHand[1].rank_, dealerHand[0].rank_};
        bool const R0 = std::find(ranks.cbegin(), ranks.cend(), lowestRank) != ranks.end();
        bool const R1 = std::find(ranks.cbegin(), ranks.cend(), lowestRank + 1) != ranks.end();
        bool const R2 = std::find(ranks.cbegin(), ranks.cend(), lowestRank + 2) != ranks.end();
        if ((R0 == true ) && (R1 == true) && (R2 == true))
        {
            n3straight_++;
        }
    }


    /* Check Top 3 */
    if ( ((playerHand[0].rank_ == playerHand[1].rank_) && (playerHand[1].rank_ == dealerHand[0].rank_)) &&
        ((playerHand[0].suit_ == playerHand[1].suit_) && (playerHand[1].suit_ == dealerHand[0].suit_)))
    {
        t3suited3K_++;
    }
    else if ((playerHand[0].suit_ == playerHand[1].suit_) && (playerHand[1].suit_ == dealerHand[0].suit_))
    {
        /* Straight Flush */

        /* Sort the cards */
        Rank const lowestRank = std::min(std::min(playerHand[0].rank_, playerHand[1].rank_), dealerHand[0].rank_);
        std::vector<Rank> const ranks = {playerHand[0].rank_, playerHand[1].rank_, dealerHand[0].rank_};
        bool const R0 = std::find(ranks.cbegin(), ranks.cend(), lowestRank) != ranks.end();
        bool const R1 = std::find(ranks.cbegin(), ranks.cend(), lowestRank + 1) != ranks.end();
        bool const R2 = std::find(ranks.cbegin(), ranks.cend(), lowestRank + 2) != ranks.end();
        if ((R0 == true ) && (R1 == true) && (R2 == true))
        {
            t3straightFlush_++;
        }
    }
    else if ((playerHand[0].rank_ == playerHand[1].rank_) && (playerHand[1].rank_ == dealerHand[0].rank_))
    {
        t3nonsuited3K_++;
    }

}
