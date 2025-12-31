
#pragma once 
#include "backtesting/excecution.hpp"
#include "data/market_state.hpp"
#include "events/events.hpp"
#include "events/dispatcher.hpp"

class ExcecutionHandler{

    public:

    ExcecutionHandler(Excecution& exce,trd::MarketState& marketState,events::Dispatcher& bus) 
    : m_exce(exce), m_marketState(marketState), m_bus(bus) {};

    void on(const events::Event& event){
        if (auto* ev=std::get_if<events::OrderEvent>(&event)){
            // Is an order event 

            trd::price px=m_exce.slip(m_marketState.next.open,ev->side); // APply slippage model
            trd::price fee=m_exce.fee;

            m_bus.push( // Add on the fill event now to update portfolio details 
                events::FillEvent{ev->epoch,ev->side,ev->qty,px,fee}
            );

        }
    }

    private:

    Excecution& m_exce;
    trd::MarketState& m_marketState;
    events::Dispatcher& m_bus;
    
};