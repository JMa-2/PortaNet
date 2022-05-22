/**
 * @file ConsoleController.h
 * @author Joe Maier, joemaier2@gmail.com
 * @brief serial console controller header file
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef CONSOLECONTROLLER_H_
#define CONSOLECONTROLLER_H_

enum ConsoleFlags{
    CONSOLE_FLAG_INIT   = 0b1 << 0 
};

/**
 * @brief console controller file
 * 
 */
void ConsoleController(void);



#endif