
#pragma once 
#include "core/types.hpp"

struct Portfolio{

    trd::price balance{100'000}; // Starting balance, self explanatory 
    int pos{0}; // HOw many units of the asset we currently own

    void buy(int quantity,double px, double fee){ 
        balance-=quantity*px + fee;
        pos+=quantity;
    }

    void sell(int quantity,double px, double fee){
        balance+=quantity*px - fee;
        pos-=quantity;
    }

    double equity(double mark_px) const { 
        return balance+pos*mark_px;
    }

};