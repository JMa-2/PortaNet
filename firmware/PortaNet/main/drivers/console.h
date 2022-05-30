/**
 * @file console.h
 * @author Joe Maier, joemaier2@gmail.com
 * @brief serial console driver header file
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "esp_console.h"

/**
 * @brief initialize serial console
 * 
 * @return true, if init successful
 * @return false, if init unsuccessful
 */
void InitConsole(void);


/**
 * @brief process serial console operations
 * 
 */
void ProcessConsole(void);


/**
 * @brief add serial console command
 * 
 */
void AddConsoleCommand(esp_console_cmd_t desc);

#endif