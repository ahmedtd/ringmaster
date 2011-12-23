
#ifndef ELEMENT
#define ELEMENT

#include <vector>
using std::vector;

#include "pin.hpp"

namespace ringmaster
{
    
/// An element has pins and maintains voltage and current relationships between
/// them, possibly time-variant.
class element
{
public:
    virtual unique_ptr<expression> voltage_between(
        const pin &pin1,
        const pin &pin2) const = 0;
    
    virtual unique_ptr<expression> current_between(
        const pin &pin1,
        const pin &pin2) const = 0;
    
    
};

}


#endif
