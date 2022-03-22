#ifndef FLAGS_H
#define FLAGS_H

#include <stdbool.h>


/**
 * @brief Set the Flag value
 * 
 * @param flag flag enum to modify
 * @param val value to add into flag 
 * @return unsigned int new flag value
 */
unsigned int SetFlag(unsigned int flag, unsigned int val);


/**
 * @brief reset the flag value
 * 
 * @param flag flag enum to modify
 * @param val value to remove from flag
 * @return unsigned int new flag value
 */
unsigned int ResetFlag(unsigned int flag, unsigned int val);


/**
 * @brief check if flag is set
 * 
 * @param flag flag enum to check
 * @param val value to check if set
 * @return true if flag is set
 * @return false if flag is reset
 */
bool IsFlagSet(unsigned int flag, unsigned int val);







#endif


