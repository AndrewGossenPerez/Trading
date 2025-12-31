
#pragma once 
#include "core/types.hpp"
#include "data/bar.hpp"
#include <random>

struct Signal{
    trd::Side side=trd::Side::Hold;
};

// Main strategy parent struct 
struct Strategy{
    
    public: 

    virtual ~Strategy()=default;
    virtual Signal onBar(const trd::Bar& bar)=0;

};


class CoinFlipStrategy : public Strategy {

    public:
    CoinFlipStrategy() : rng_(std::random_device{}()), dist_(0, 1) {}

    Signal onBar(const trd::Bar&) override {
        int flip = dist_(rng_);
        if (flip == 0) return { trd::Side::Buy };
        else return { trd::Side::Sell };
    }

    private:
    std::mt19937 rng_;
    std::uniform_int_distribution<int> dist_;

};

