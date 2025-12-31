
#pragma once 
#include "data/market_state.hpp"
#include "backtesting/strategies.hpp"
#include "events/dispatcher.hpp"

class StrategyHandler{

    public:

    StrategyHandler(Strategy& strat,events::Dispatcher& bus) : m_strat(strat),m_bus(bus) {};

    void on(const events::Event& event){

        if (auto* ev=std::get_if<events::MarketEvent>(&event)){
            // Is a market event 
            Signal signal=m_strat.onBar(ev->bar); // Apply strategy on the bar to generate a singal
            if (signal.side!=trd::Side::Hold){
                // Timestamp the signal so we don't trade on the same bar 
                m_bus.push( // Push the signal event to be handled by the risk handler 
                    events::SignalEvent{ev->next.epoch,signal.side}
                );
            }
        }

    }

    private:

    Strategy& m_strat;
    events::Dispatcher& m_bus;

};