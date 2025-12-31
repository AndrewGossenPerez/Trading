
#pragma once 
#include "core/types.hpp"
#include "data/bar.hpp"

namespace trd{

struct MarketState{
    trd::Bar current{};
    trd::Bar next{};
};

}