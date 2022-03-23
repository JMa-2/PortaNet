#include "TerminalInterface.h"

#include "../controllers/TerminalController.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"



void TaskTerminal(void *pvoid)
{
    while(1)
    {
        TerminalController();
        vTaskDelay(portTICK_PERIOD_MS*10);
    }
}









