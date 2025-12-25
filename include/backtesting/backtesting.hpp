
#pragma once 
#include "core/types.hpp"
#include "strategy.hpp"
#include <vector>

struct Result{
    std::vector<double> equity; 
    double final_equity{};
    double maxdd{};
    double netFees{};
    double netBuys{};
    double netSells{};
};

class Backtest{

    public:
    
    Result run(const std::vector<trd::Bar>& bars, Strategy& strat);

};