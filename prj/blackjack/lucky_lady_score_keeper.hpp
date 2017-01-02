#pragma once
#include "card.hpp"

#include <vector>

class LuckyLadyScoreKeeper
{
    public:
        LuckyLadyScoreKeeper();
        ~LuckyLadyScoreKeeper();


        void evaluateHand(std::vector<Card> const & dealerHand, std::vector<Card> const & playerHand);
        std::string toString();
        size_t getWinCounter() const;
        size_t getWeightedWinCounter() const;
        size_t getHandCount() const;

        static bool hasBlackjack(std::vector<Card> const & hand);
    private:
        size_t totalHands_;
        size_t twenty_;
        size_t suitedTwenty_;
        size_t matchedTwenty_;
        size_t qhTwenty_;
        size_t qhTwenty_DealerBlackjack_;

        void formatLine(std::stringstream & ss, std::string const & tag, size_t const winCount, size_t const handCount);


};
