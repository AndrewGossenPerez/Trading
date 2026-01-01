
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

    using clock = std::chrono::steady_clock;

    // Create strat and backtester 
    trd::price startingEquity{100'000};
    trd::csvReader reader;
    Portfolio portfolio;
    portfolio.setEquity(startingEquity);
    Excecution exce(1.0); // 10. fee 
    CoinFlipStrategy strat;
    trd::Backtest bt(portfolio,exce);

    // Create bars 
    auto t1CSV=clock::now();
    std::vector<trd::Bar> bars=reader.loadBars("samples/aapl.csv");
    auto t2CSV=clock::now();

    auto t1Bt=clock::now();
    trd::Result re=bt.run(bars,strat);
    auto t2Bt=clock::now();
    
    auto elapsedBt=t2Bt-t1Bt;
    auto elapsedCSV=t2CSV-t1CSV;

    double secondsBt = std::chrono::duration<double>(elapsedBt).count();
    double secondsCSV = std::chrono::duration<double>(elapsedCSV).count();

    std::cout << "\n --- TRADE RESULTS --- \n";
    std::printf("[Starting equity]: %.2f\n", startingEquity);
    std::printf("[Final equity]: %.2f\n", re.finalEquity);
    std::printf("[Fills]: %d\n", (int)re.trades.size());
    std::printf("[Equity Points]: %d\n", (int)re.equityPoints.size());
    std::printf("[Cumulated Fees]: %d\n", (int)re.netFees);
    std::printf("[Slippage Basis Points]: %d\n", (int)SLIP_BPS);
    
    std::cout << "\n -- BENCHMARKS BACKTESTER -- \n";
    std::cout << "[Bars/sec]: " << (bars.size()/secondsBt) << "\n";
    std::cout << "[Fills/sec]: " << (re.trades.size()/secondsBt) << "\n";
    std::printf("[Backtest Elapsed Time]: %.15f\n", secondsBt);

    std::cout << "\n -- BENCHMARKS CSV INGESTION -- \n";
    std::cout << "[Bars/sec]: " << (bars.size()/secondsCSV) << "\n";
    std::printf("[CSV Ingestion Elapsed Time]: %.15f\n", secondsCSV);

}