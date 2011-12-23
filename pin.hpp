
#ifndef PIN
#define PIN

#include "element.hpp"

namespace ringmaster
{

/// A pin that belongs to an element.  Used as the basic reference point in
/// overall voltage and current relationships.
class pin
{
public:
    pin(const elem &owner, const string &mName);

    const string mName;

protected:
    const element &mOwner;
};

/// Basic symbolic unit: represents the voltage difference between a high pin
/// and a low pin
class voltage
{
public:
    voltage(const pin &upper, const pin &lower);
private:
    const pin &mUpper;
    const pin &mLower;
};

/// Basic symbolic unit: represents the current between a source pin and a
/// destination pin
class current
{
public:
    current(const pin &src, const pin &dst);
private:
    const pin &src;
    const pin &dst;
};
 
}

#endif
