#pragma once
#include "card.hpp"

#include <vector>

class TopThreeScoreKeeper
{
    public:
        TopThreeScoreKeeper();
        ~TopThreeScoreKeeper();


        void evaluateHand(std::vector<Card> const & dealerHand, std::vector<Card> const & playerHand);
        std::string toString();
        size_t getNormalWinCounter() const;
        size_t getNormalWeightedWinCounter() const;
        size_t getTopWinCounter() const;
        size_t getTopWeightedWinCounter() const;
        size_t getHandCount() const;
    private:
        size_t totalHands_;

        /* Normal 3 */
        size_t n3flush_;
        size_t n3straight_;
        size_t n3threeOfAKind_;

        /* Top */
        size_t t3suited3K_;  /* 270:1 */
        size_t t3straightFlush_; /* 180 : 1 */
        size_t t3nonsuited3K_; /* 90 : 1 */



};
