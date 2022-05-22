/**
 * @file ConsoleController.c
 * @author Joe Maier, joemaier2@gmail.com
 * @brief serial console controller source file
 * @version 0.1
 * @date 2022-05-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "ConsoleController.h"
#include "../drivers/flags.h"
#include "../drivers/console.h"
#include "argtable3/argtable3.h"
#include "esp_console.h"
#include "../interfaces/ApInterface.h"
 

static void RegisterAllCommands(void);
static int CmdStatus(int argc, char **argv);
static void RegisterStatus(void);

static unsigned int CONSOLE_FLAGS = 0;

void ConsoleController(void)
{
    if (!IsFlagSet(CONSOLE_FLAGS, CONSOLE_FLAG_INIT))
    {
        InitConsole();
        RegisterAllCommands();
    }
}



static void RegisterAllCommands(void)
{
    esp_console_register_help_command();
    RegisterStatus();
}



static int CmdStatus(int argc, char **argv)
{
    unsigned int NumConn;
    char ssid[SSID_LENGTH];
    char password[PASSWORD_LENGTH];

    NumConn = GetNumConnections();
    GetSsid(ssid);
    GetPassword(password);

    printf("---SSID---\n");
    printf("%s\n\n", ssid);
    printf("---PASSWORD---\n");
    printf("%s\n\n", password);
    printf("---MAX CONNECTIONS---\n");
    printf("%u\n\n", NumConn);

    return 0;
}



static void RegisterStatus(void)
{
    const esp_console_cmd_t status_cmd = 
    {
        .command = "status",
        .help = "Status of the AP including SSID, password, max number of connections, and wifi channel",
        .hint = NULL,
        .func = &CmdStatus,
        .argtable = NULL
    };

    esp_console_cmd_register(&status_cmd);
}


