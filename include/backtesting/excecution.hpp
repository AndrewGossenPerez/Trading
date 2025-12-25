
#pragma once 
#include "core/types.hpp"

struct Excecution{

    trd::price fee{1.0};
    trd::price slipping_bps{0.0};

    double slip(double px,trd::Type buy) const {
        double s=px*(slipping_bps/10'000.0);
        return (buy==trd::Type::Buy) ? px+s:px-s; // Ensure slippage always harms the portfolio 
    }

};