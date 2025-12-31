
#pragma once 
#include "events/dispatcher.hpp"
#include "events/events.hpp"
#include "core/portfolio.hpp"

namespace trd{

class RiskHandler{

    public:

    RiskHandler(Portfolio& portfolio,events::Dispatcher& bus) : m_portfolio(portfolio), m_bus(bus) {};

    void on(const events::Event& event){

        if (auto* ev=std::get_if<events::SignalEvent>(&event)){
            // Is a signal event 
            if (ev->side==trd::Side::Buy && m_portfolio.pos==0){
                // Buy Signal
                m_bus.push( // Push an order to purchase one asset 
                    events::OrderEvent{ev->epoch,ev->side,1}
                );
            } else if (ev->side==trd::Side::Sell && m_portfolio.pos > 0 ){
                // Sell signal 
                m_bus.push(  // Push an order to sell all assets 
                    events::OrderEvent{ev->epoch,ev->side,m_portfolio.pos}
                );
            }
        } // Else hold and do nothing 

    }

    private:

    Portfolio& m_portfolio;
    events::Dispatcher& m_bus;

};

}