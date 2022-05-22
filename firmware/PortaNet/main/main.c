#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "interfaces/ApInterface.h"
#include "interfaces/DisplayInterface.h"
#include "interfaces/TerminalInterface.h"

void app_main(void)
{
	xTaskCreate(&TaskAccessPoint, "TaskAccessPoint", 4096, NULL, 1, NULL);


}
