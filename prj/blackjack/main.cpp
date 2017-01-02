#include "shoe.hpp"
#include "card.hpp"
#include "lucky_lady_score_keeper.hpp"
#include "top_three_score_keeper.hpp"
#include <chrono>
#include <iostream>

static const size_t UPDATE_INTERVAL = 1000;
static const size_t TOTAL_SHOES = 100000;
static const size_t PLAYER_COUNT = 2;
static const size_t PLAYER_OF_INTEREST = 0;

void playOneHand(Shoe & shoe, std::size_t const playerCount, LuckyLadyScoreKeeper & llsk, TopThreeScoreKeeper & ttsk);
void playBlackjack(Shoe & shoe, Card const dealerUpCard, std::vector<Card> & playerHand);

int main(int argc, char ** argv)
{
    LuckyLadyScoreKeeper llsk;
    TopThreeScoreKeeper ttsk;
    Shoe shoe(6);
    std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

    for (size_t iterations = 0; iterations < TOTAL_SHOES; iterations++)
    {
        shoe.shuffle();
        Card const discardedCard = shoe.drawOne();

        /* Base it off the deal eyeballing the deck */
        size_t const deckThreshold = rand() % 30 + 40;
        while (shoe.getRemainingCardCount() > deckThreshold)
        {
            playOneHand(shoe, PLAYER_COUNT, llsk, ttsk);
        }
        if ((iterations % UPDATE_INTERVAL) == 0)
        {
	    std::cout << "Finished " << iterations << " of " << TOTAL_SHOES << "." << std::endl;
        }
    }

    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Finished " << TOTAL_SHOES << " shoes in " << elapsed_seconds.count() << " seconds." << std::endl << std::endl;
    std::cout << "Dealer + " << PLAYER_COUNT << " players." << std::endl;

    std::cout << "Lady Lucky Payouts" << std::endl;
    std::cout << llsk.toString() << std::endl;

//    {
//        float const normalSideGamePayouts = (float) ttsk.getNormalWinCounter();
//        float const topSideGamePayouts = (float) ttsk.getTopWinCounter();
//        float const normalWeightedSideGamePayouts = (float) ttsk.getNormalWeightedWinCounter();
//        float const topWeightedSideGamePayouts = (float) ttsk.getTopWeightedWinCounter();
//        float const totalHands = (float) ttsk.getHandCount();
//        std::cout << ttsk.toString() << std::endl;
//        std::cout << "Top 3 Payouts" << std::endl;
//        std::cout << "Chance of 'Bottom 3' payout:" << normalSideGamePayouts / totalHands << std::endl;
//        std::cout << "Return, assuming constant bets:" << normalWeightedSideGamePayouts / totalHands << std::endl;
//        std::cout << "Chance of 'Top 3' payout:" << topSideGamePayouts / totalHands << std::endl;
//        std::cout << "Return, assuming constant bets:" << topWeightedSideGamePayouts / totalHands << std::endl << std::endl;
//    }

    std::string dummy;
    std::getline(std::cin, dummy);
    return 0;
}


void playOneHand(Shoe & shoe, std::size_t const playerCount, LuckyLadyScoreKeeper & llsk, TopThreeScoreKeeper & ttsk)
{
    size_t playerHandsWon = 0;

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
    llsk.evaluateHand(dealerHand, playersHands[PLAYER_OF_INTEREST]);
    ttsk.evaluateHand(dealerHand, playersHands[PLAYER_OF_INTEREST]);

    /* Actually play blackjack */
    if (true == llsk.hasBlackjack(dealerHand))
    {
        /* We're done, don't deal any more */
    }
    else
    {
        for (std::size_t i = 0; i < playerCount; i++)
        {
            if (false == llsk.hasBlackjack(playersHands[i]))
            {
                playBlackjack(shoe, dealerHand[0], playersHands[i]);
            }
        }
    }
}

size_t getCardValue(Card const card)
{
    switch(card.rank_)
    {
        case Rank::Two: return 2;
        case Rank::Three: return 3;
        case Rank::Four: return 4;
        case Rank::Five: return 5;
        case Rank::Six: return 6;
        case Rank::Seven: return 7;
        case Rank::Eight: return 8;
        case Rank::Nine: return 9;
        case Rank::Ten:
        case Rank::Jack:
        case Rank::Queen:
        case Rank::King:
            return 10;

        case Rank::Ace: return 1; /* 1 is intentional */
    };
}

/* Not trying to play for real, but just burn a few cards acting like we're playing */
void playBlackjack(Shoe & shoe, Card const dealerUpCard, std::vector<Card> & playerHand)
{
    size_t playerHandSum = getCardValue(playerHand[0]) + getCardValue(playerHand[1]);
    while (playerHandSum <= 11)
    {
        Card const oneCard = shoe.drawOne();
        playerHandSum += getCardValue(oneCard);
        playerHand.push_back(oneCard);
    }


}

