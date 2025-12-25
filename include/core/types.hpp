
#pragma once 
#include <cstdint>

namespace trd{

    using timestamp=std::int64_t; // Epoch in nanoseconds
    using price=double;
    using quantity=int;

    enum Type{Buy,Sell,None}; 
    
};