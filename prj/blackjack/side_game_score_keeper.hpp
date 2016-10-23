#pragma once
#include "card.hpp"

#include <vector>

class SideGameScoreKeeper
{
    public:
        SideGameScoreKeeper();
        ~SideGameScoreKeeper();


        void evaluateHand(std::vector<Card> const & dealerHand, std::vector<Card> const & playerHand);
        std::string toString();
        size_t getWinCounter() const;
        size_t getWeightedWinCounter() const;
        size_t getHandCount() const;
    private:
        size_t totalHands_;
        size_t twenty_;
        size_t suitedTwenty_;
        size_t matchedTwenty_;
        size_t qhTwenty_;
        size_t qhTwenty_DealerBlackjack_;

        bool hasBlackjack(std::vector<Card> const & hand);

};
