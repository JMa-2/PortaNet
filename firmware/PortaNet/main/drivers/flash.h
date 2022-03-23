#ifndef FLASH_H
#define FLASH_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief read unsigned byte of data
 * 
 * @param section memory section to read
 * @param buffer memory loaction to store read value
 * @return true if read successful
 * @return false if read unsuccessful
 */
bool u8ReadFlash (const char *section, uint8_t *buffer);


/**
 * @brief write unsigned byte of data
 * 
 * @param section memory section to write
 * @param val value to write
 * @return true if write successful
 * @return false if write unsuccesful
 */
bool u8WriteFlash(const char *section, uint8_t val);


/**
 * @brief read string of data 
 * 
 * @param section memory section to read
 * @param buffer memory location to store read data
 * @param len memory location to store read length
 * @return true if read successful
 * @return false false in read unsuccessful
 */
bool strReadFlash(const char *section, char *buffer, size_t *len);


/**
 * @brief write string of data
 * 
 * @param section memory section to write to
 * @param str string memory location to write
 * @return true if write successful
 * @return false if write unsuccessful
 */
bool strWriteFlash(const char *section, char *str);




#endif