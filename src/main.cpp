
#include "data/csv_reader.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <chrono>
#include "backtesting/strategies.hpp"
#include "backtesting/backtesting.hpp"
#include "data/csv_reader.hpp"
#include "data/config.hpp"
#include <cstdio>

int main(){

    std::printf("--- BACK TEST STARTING --- \n");

    // Create strat and backtester 
    trd::price startingEquity{100'000};
    trd::csvReader reader;
    Portfolio portfolio;
    portfolio.setEquity(startingEquity);
    Excecution exce(1.0); // 10. fee 
    CoinFlipStrategy strat;
    trd::Backtest bt(portfolio,exce);

    // Create bars 
    std::vector<trd::Bar> bars=reader.loadBars("samples/aapl.csv");
    trd::Result re=bt.run(bars,strat);

    std::cout << "\n --- RESULTS --- \n";
    std::printf("[Starting equity]: %.2f\n", startingEquity);
    std::printf("[Final equity]: %.2f\n", re.finalEquity);
    std::printf("[Net Trades]: %d\n", (int)re.trades.size());
    std::printf("[Equity Points]: %d\n", (int)re.equityPoints.size());
    std::printf("[Cumulated Fees]: %d\n", (int)re.netFees);
    std::printf("[Slippage Basis Points]: %d\n", (int)SLIP_BPS);

}