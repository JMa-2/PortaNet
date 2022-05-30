/**
 * @file ConsoleInterface.c
 * @author Joe Maier, joemaier2@gmail.com
 * @brief serial console interface source file for wifi access point control
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ConsoleInterface.h"
#include "../controllers/ConsoleController.h"


void TaskConsole(void *pvoid)
{
    while(1)
    {
        ConsoleController();
        vTaskDelay(portTICK_PERIOD_MS);
    }
}