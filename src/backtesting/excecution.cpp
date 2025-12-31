
#include "backtesting/excecution.hpp"
#include "core/types.hpp"

trd::price Excecution::slip(trd::price refPrice,trd::Side side) const {
    return refPrice; // Implement slippage later 
};