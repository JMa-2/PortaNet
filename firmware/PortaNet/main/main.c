#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "interfaces/ApInterface.h"
#include "interfaces/ConsoleInterface.h"

void app_main(void)
{
	xTaskCreate(&TaskAccessPoint, "TaskAccessPoint", 4096, NULL, 2, NULL);

	xTaskCreate(&TaskConsole, "TaskConsole", 4096, NULL, 1, NULL);
	
}
