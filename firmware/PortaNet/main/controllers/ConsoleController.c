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
#include <string.h>
#include <arpa/inet.h>
#include "../drivers/swVersion.h"


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
static int CmdSwVersion(int argc, char **argv);
static int CmdChannel(int argc, char **argv);
static void RegisterStatus(void);
static void RegisterReset(void);
static void RegisterRestart(void);
static void RegisterOn(void);
static void RegisterOff(void);
static void RegisterDevices(void);
static void RegisterSsid(void);
static void RegisterPassword(void);
static void RegisterMaxConn(void);
static void RegisterSwVersion(void);
static void RegisterChannel(void);


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
    RegisterRestart();
    RegisterSwVersion();
    RegisterChannel();
}



static int CmdStatus(int argc, char **argv)
{
    unsigned int NumConn;
    char ssid[SSID_LENGTH];
    char password[PASSWORD_LENGTH];
    uint8_t channel;

    NumConn = GetMaxConnections();
    GetSsid(ssid);
    GetPassword(password);
    channel = GetWifiChannel();


    printf("\n---SSID---\n");
    printf("%s\n\n", ssid);
    printf("---PASSWORD---\n");
    printf("%s\n\n", password);
    printf("---MAX CONNECTIONS---\n");
    printf("%u\n\n", NumConn);
    printf("---WIFI CHANNEL---\n");
    printf("%u\n\n", channel);

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
    if (ReqFactoryReset())
        printf("\nFactory reset request accepted...\n\n");
    else
        printf("\nFactory reset request denied...\n\n");

    return 0;
}



static void RegisterReset(void)
{
    const esp_console_cmd_t reset_cmd =
    {
        .command = "reset",
        .help = "Reset the AP to its default credentials.",
        .hint = NULL,
        .func = &CmdReset,
        .argtable = NULL
    };

    esp_console_cmd_register(&reset_cmd);
}



static int CmdRestart(int argc, char **argv)
{
    if (ReqApRestart())
        printf("\nRestart request accepted...\n\n");

    else
        printf("\nRestart request denied...\n\n");

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
    };

    esp_console_cmd_register(&restart_cmd);
}



static int CmdOn(int argc, char **argv)
{
    if(ReqApOn())
        printf("\nOn request accepted...\n\n");

    else
        printf("\nOn request denied...\n\n");

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
    };

    esp_console_cmd_register(&on_cmd);
}



static int CmdOff(int argc, char **argv)
{
    if(ReqApOff())
        printf("\nOff request accepted...\n\n");
    else
        printf("\nOff request denied...\n\n");

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
    };

    esp_console_cmd_register(&off_cmd);
}



static int CmdDevices(int argc, char **argv)
{
    unsigned int numConn;
    numConn = GetNumConnections();

    uint8_t macs[numConn * MAC_ADDR_LENGTH];
    uint32_t ips[numConn];

    GetStaList(macs, ips);

    printf("\n---IP ADDRESSES---\n");
    for(int i=0; i<numConn; i++)
    {
        printf("%s\n", inet_ntoa(ips[i]));
    }

    printf("\n---MAC ADDRESSES---\n");
    for(int i=0; i<(numConn*MAC_ADDR_LENGTH); i=i+MAC_ADDR_LENGTH)
    {
        for (int j=0; j<6; j++)
        {
            printf("%02x", macs[i+j]);
            if(j<5)
                printf(":");
        }
        printf("\n");
    }
    printf("\n");


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
    };

    esp_console_cmd_register(&devices_cmd);
}


static struct
{
    struct arg_str *ssid;
    struct arg_end *end;
} ssid_args;

static int CmdSsid(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **)&ssid_args);
    if (nerrors != 0)
    {
        arg_print_errors(stderr, ssid_args.end, argv[0]);
        return 1;
    }

    if (ReqNewSsid((char *)ssid_args.ssid->sval[0], strlen((char *)ssid_args.ssid->sval[0])))
        printf("\nSuccessfully requested new SSID of %s\n\n", ssid_args.ssid->sval[0]);

    else
        printf("\nFailed to request new SSID of %s\n\n", ssid_args.ssid->sval[0]);


    return 0;
}



static void RegisterSsid(void)
{
    ssid_args.ssid = arg_str0(NULL, NULL, "<ssid>", "SSID of AP");
    ssid_args.end = arg_end(2);

    const esp_console_cmd_t ssid_cmd =
    {
        .command = "ssid",
        .help = "Request new SSID of AP and restart the AP.",
        .hint = NULL,
        .func = &CmdSsid,
        .argtable = &ssid_args
    };

    esp_console_cmd_register(&ssid_cmd);
}



static struct
{
    struct arg_str *pw;
    struct arg_end *end;
} pw_args;

static int CmdPassword(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **)&pw_args);
    if (nerrors != 0)
    {
        arg_print_errors(stderr, pw_args.end, argv[0]);
        return 1;
    }

    if (ReqNewPassword((char *)pw_args.pw->sval[0], strlen((char *)pw_args.pw->sval[0])))
        printf("\nSuccessfully requested new password of %s\n\n", pw_args.pw->sval[0]);

    else
        printf("\nFailed to request new password of %s\n\n", pw_args.pw->sval[0]);


    return 0;
}



static void RegisterPassword(void)
{
    pw_args.pw = arg_str0(NULL, NULL, "<pw>", "Password of AP");
    pw_args.end = arg_end(2);

    const esp_console_cmd_t pw_cmd =
    {
        .command = "password",
        .help = "Request new password of AP and restart the AP.",
        .hint = NULL,
        .func = &CmdPassword,
        .argtable = &pw_args
    };

    esp_console_cmd_register(&pw_cmd);
}



static struct
{
    struct arg_int *conn;
    struct arg_end *end;
} maxconn_args;

static int CmdMaxConn(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **)&maxconn_args);
    if (nerrors != 0)
    {
        arg_print_errors(stderr, maxconn_args.end, argv[0]);
        return 1;
    }

    if (ReqNewMaxConn(maxconn_args.conn->ival[0]))
        printf("\nSuccessfully requested new max connection quantity of %i\n\n", maxconn_args.conn->ival[0]);

    else
        printf("\nFailed to request new max connection quantity of %i\n\n", maxconn_args.conn->ival[0]);


    return 0;
}



static void RegisterMaxConn(void)
{
    maxconn_args.conn = arg_int0(NULL, NULL, "<numconn>", "Number of max connections.");
    maxconn_args.end = arg_end(2);

    const esp_console_cmd_t maxconn_cmd =
    {
        .command = "maxconn",
        .help = "Request new number of max connections for AP and restart the AP.",
        .hint = NULL,
        .func = &CmdMaxConn,
        .argtable = &maxconn_args
    };

    esp_console_cmd_register(&maxconn_cmd);
}



static int CmdSwVersion(int argc, char **argv)
{
    printf("\n---SW VERSION---\n");

    char temp[VERSION_LEN];
    int len;

    GetMajorVersion(temp, &len);
    printf("v%s.", temp);

    GetMinorVersion(temp, &len);
    printf("%s.", temp);

    GetBuildDate(temp, &len);
    printf("%s", temp);

    GetBuildTime(temp, &len);
    printf("%s\n\n", temp);


    return 0;
}



static void RegisterSwVersion(void)
{
    const esp_console_cmd_t swver_cmd =
    {
        .command = "version",
        .help = "Show version of the software.",
        .hint = NULL,
        .func = &CmdSwVersion,
        .argtable = NULL
    };

    esp_console_cmd_register(&swver_cmd);
}



static struct
{
    struct arg_int *channel;
    struct arg_end *end;
} channel_args;

static int CmdChannel(int argc, char **argv)
{
    int nerrors = arg_parse(argc, argv, (void **)&channel_args);
    if (nerrors != 0)
    {
        arg_print_errors(stderr, channel_args.end, argv[0]);
        return 1;
    }

    if (ReqNewWifiChannel(channel_args.channel->ival[0]))
        printf("\nSuccessfully requested new wifi channel of %i\n\n", channel_args.channel->ival[0]);

    else
        printf("\nFailed to request new wifi channel of %i\n\n", channel_args.channel->ival[0]);


    return 0;
}



static void RegisterChannel(void)
{
    channel_args.channel = arg_int0(NULL, NULL, "<#>", "Wifi Channel number.");
    channel_args.end = arg_end(2);

    const esp_console_cmd_t channel_cmd =
    {
        .command = "channel",
        .help = "Request new wifi channel for AP and restart the AP.",
        .hint = NULL,
        .func = &CmdChannel,
        .argtable = &channel_args
    };

    esp_console_cmd_register(&channel_cmd);
}