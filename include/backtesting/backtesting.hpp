
#pragma once 
#include <cstdint>
#include <vector>
#include "core/types.hpp"
#include "core/portfolio.hpp"
#include "backtesting/excecution.hpp"
#include "backtesting/strategies.hpp"

namespace trd{ 

struct Trade{ // An excecuted trade during a FillEvent evnet 

    trd::timestamp epoch{0};
    trd::Side side=trd::Side::Hold;
    trd::quantity qtr{0};
    trd::price price{0.0};
    trd::price fee{0.0};

};

struct Result{ 

    // Equity curve marked each bar 
    std::vector<trd::price> equity;
    // Log trades 
    std::vector<Trade> trades;

    // Summary fields for the final output 
    trd::price finalEquity{0.0};
    trd::price maxDD{0.0};
    trd::price netFees{0.0};
    trd::quantity netBuys{0};
    trd::quantity netSells{0};

};

class Backtest{

    public:

    Backtest(Portfolio& portfolio,Excecution& exce) : m_portfolio(portfolio), m_exce(exce) {} 

    Result run(const std::vector<trd::Bar>& bars,Strategy& strategy);

    private: 

    Portfolio& m_portfolio;
    Excecution& m_exce;

};

}