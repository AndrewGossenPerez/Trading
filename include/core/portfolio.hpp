
#pragma once 
#include "core/types.hpp"

struct Portfolio{

    trd::price balance{10000.0};
    trd::quantity pos{0};

    void buy(trd::quantity qty,trd::price price,trd::price fee){
        balance -= (price*qty) + fee;
        pos+=qty;
    }

    void sell(trd::quantity qty,trd::price price,trd::price fee){
        balance += (price*qty) - fee;
        pos-=qty;
    }

    trd::price equity(trd::price markPx) const {
        return balance + static_cast<trd::price>(pos) * markPx;
    }

    void setEquity(trd::price equity){
        balance=equity;
    }

};