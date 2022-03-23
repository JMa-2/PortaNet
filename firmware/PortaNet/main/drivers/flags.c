#include "flags.h"

#include <stdbool.h>

unsigned int SetFlag(unsigned int flag, unsigned int val)
{
    flag |= val;
    return flag;
}



unsigned int ResetFlag(unsigned int flag, unsigned int val)
{
    flag &= ~val;
    return flag;
}



bool IsFlagSet(unsigned int flag, unsigned int val)
{
    if ((flag & val) == val)
        return true;
    
    return false;
}












