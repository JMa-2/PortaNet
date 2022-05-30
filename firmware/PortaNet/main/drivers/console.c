/**
 * @file console.c
 * @author Joe Maier, joemaier2@gmail.com
 * @brief serial console driver source file
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "console.h"
#include <stdio.h>
#include "esp_system.h"

#define PROMPT_STR "PortaNet"
#define CONFIG_CONSOLE_MAX_COMMAND_LINE_LENGTH 1024;

void InitConsole(void)
{
    esp_console_repl_t *repl = NULL;
    esp_console_repl_config_t replConfig = ESP_CONSOLE_REPL_CONFIG_DEFAULT();

    replConfig.prompt = PROMPT_STR ">";
    replConfig.max_cmdline_length = CONFIG_CONSOLE_MAX_COMMAND_LINE_LENGTH;
    
    esp_console_dev_usb_serial_jtag_config_t hwConfig = ESP_CONSOLE_DEV_USB_SERIAL_JTAG_CONFIG_DEFAULT();
    esp_console_new_repl_usb_serial_jtag(&hwConfig, &replConfig, &repl);

    esp_console_start_repl(repl);
}
