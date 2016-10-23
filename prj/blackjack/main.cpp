#include "shoe.hpp"
#include "card.hpp"
#include "side_game_score_keeper.hpp"
#include <chrono>
#include <iostream>

static const size_t iterationCount_ = 1e6;

void playOneHand(Shoe & shoe, std::size_t const playerCount, SideGameScoreKeeper & sgsk);

int main(int argc, char ** argv)
{
    SideGameScoreKeeper sgsk;
    Shoe shoe(8);
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    for (size_t iterations = 0; iterations < iterationCount_; iterations++)
    {
        shoe.shuffle();
        Card discardedCard = shoe.drawOne();

        /* Base it off the deal eyeballing the deck */
        size_t const deckThreshold = rand() % 30 + 40;
        while (shoe.getRemainingCardCount() > deckThreshold)
        {
            playOneHand(shoe, 3, sgsk);
        }
    }

    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Finished " << iterationCount_ << " shoes in " << elapsed_seconds.count() << " seconds." << std::endl;
    std::cout << sgsk.toString() << std::endl;

    float const totalSideGamePayouts = (float) sgsk.getWinCounter();
    float const weightedSideGamePayouts = (float) sgsk.getWeightedWinCounter();
    float const totalHands = (float) sgsk.getHandCount();

    std::cout << "Chance of any payout:" << totalSideGamePayouts / totalHands << std::endl;
    std::cout << "Return, assuming constant bets:" << weightedSideGamePayouts / totalHands << std::endl;

    std::string dummy;
    std::getline(std::cin, dummy);
    return 0;
}


void playOneHand(Shoe & shoe, std::size_t const playerCount, SideGameScoreKeeper & sgsk)
{
    std::vector<Card> dealerHand;
    std::vector<std::vector<Card> > playersHands;
    playersHands.resize(playerCount);

    /* Deal the cards, one card to each player, then dealer */
    for (std::size_t i = 0; i < playerCount; i++)
    {
        playersHands[i].push_back(shoe.drawOne());
    }
    dealerHand.push_back(shoe.drawOne());

    /* Deal the cards, another card to each player, then dealer */
    for (std::size_t i = 0; i < playerCount; i++)
    {
        playersHands[i].push_back(shoe.drawOne());
    }
    dealerHand.push_back(shoe.drawOne());

    /* Assume the player of interest is always at the 0th position */
    sgsk.evaluateHand(dealerHand, playersHands[0]);

    /* Actually play blackjack */


}

