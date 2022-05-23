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
static int CmdReset(int argc, char **argv);
static int CmdRestart(int argc, char **argv);
static int CmdOn(int argc, char **argv);
static int CmdOff(int argc, char **argv);
static int CmdDevices(int argc, char **argv);
static int CmdSsid(int argc, char **argv);
static int CmdPassword(int argc, char **argv);
static int CmdMaxConn(int argc, char **argv);
static void RegisterStatus(void);
static void RegisterReset(void);
static void RegisterRestart(void);
static void RegisterOn(void);
static void RegisterOff(void);
static void RegisterDevices(void);
static void RegisterSsid(void);
static void RegisterPassword(void);
static void RegisterMaxConn(void);


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
    RegisterReset();
    RegisterOn();
    RegisterOff();
    RegisterDevices();
    RegisterSsid();
    RegisterPassword();
    RegisterMaxConn();
}



static int CmdStatus(int argc, char **argv)
{
    unsigned int NumConn;
    char ssid[SSID_LENGTH];
    char password[PASSWORD_LENGTH];

    NumConn = GetNumConnections();
    GetSsid(ssid);
    GetPassword(password);

    
    printf("\n---SSID---\n");
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



static int CmdReset(int argc, char **argv)
{
    //TODO add AP interface/controller functionality to handle this
    return 0;
}



static void RegisterReset(void)
{
    const esp_console_cmd_t reset_cmd =
    {
        .command = "reset",
        .help = "Reset the AP to its defual credentials.",
        .hint = NULL,
        .func = &CmdReset,
        .argtable = NULL
    }

    esp_console_cmd_register(&reset_cmd);
}



static int CmdRestart(int argc, char **argv)
{
    if (ReqApRestart())
        printf("\nRestart request accepted...\n");

    else
        printf("\n Restart request denied...\n");
    
    return 0;
}



static void RegisterRestart(void)
{
    const esp_console_cmd_t restart_cmd =
    {
        .command = "restart",
        .help = "Request the AP to restart.",
        .hint = NULL,
        .func = &CmdRestart,
        .argtable = NULL
    }

    esp_console_cmd_register(&restart_cmd);
}



static int CmdOn(int argc, char **argv)
{
    //TODO add AP interface/controller functionality to handle this
    return 0;
}



static void RegisterOn(void)
{
    const esp_console_cmd_t on_cmd =
    {
        .command = "on",
        .help = "Turn on the AP. Will only work if AP is off.",
        .hint = NULL,
        .func = &CmdOn,
        .argtable = NULL
    }

    esp_console_cmd_register(&on_cmd);
}



static int CmdOff(int argc, char **argv)
{
    //TODO add AP interface/controller functionality to handle this
    return 0;
}



static void RegisterOff(void)
{
    const esp_console_cmd_t off_cmd =
    {
        .command = "off",
        .help = "Turn off the AP. Will only work if AP is on.",
        .hint = NULL,
        .func = &CmdOff,
        .argtable = NULL
    }

    esp_console_cmd_register(&off_cmd);
}



static int CmdDevices(int argc, char **argv)
{
    //TODO add AP interface/controller functionality to handle this
    return 0;
}



static void RegisterDevices(void)
{
    const esp_console_cmd_t devices_cmd =
    {
        .command = "devices",
        .help = "Show info on currently connected devices.",
        .hint = NULL,
        .func = &CmdDevices,
        .argtable = NULL
    }

    esp_console_cmd_register(&devices_cmd);
}



static int CmdSsid(int argc, char **argv)
{
    return 0;
}



static void RegisterSsid(void)
{

}



static int CmdPassword(int argc, char **argv)
{
    return 0;
}



static void RegisterPassword(void)
{

}



static int CmdMaxConn(int argc, char **argv)
{
    return 0;
}



static void RegisterMaxConn(void)
{

}


