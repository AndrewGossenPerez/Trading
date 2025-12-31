
#pragma once 
#include "core/types.hpp"


class Excecution{

    public:

    trd::price fee{0.0};

    Excecution()=default;
    
    explicit Excecution(trd::price tradeFee) : fee(tradeFee) {}

    // Slippage model to ensure each trade harms the portfolio 
    // Given the reference prifce ref_px and the side, return price after slippage 
    trd::price slip(trd::price refPrice,trd::Side side) const;


    
};