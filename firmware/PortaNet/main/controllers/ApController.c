#include "ApController.h"

#define SSID_MEM        "ssid"
#define PASSWORD_MEM    "password"
#define NUMCONN_MEM     "numConnSetting"

static bool GetFlashSsid(char *id, size_t *len);
static bool GetFlashPassword(char *pass, size_t *len);
static bool GetFlashNumConn(uint8_t *numConn);
static bool SetFlashSsid(char *id);
static bool SetFlashPassword(char *pass);
static bool SetFlashNumConn(uint8_t numConn);
static bool StartWifi(char *id, char *pass, uint8_t numConn);
static bool StopWifi(void);
static void NetUpHandler(void);
static void NewSsidHandler(char *newSsid);
static void PwChangeHandler(char *newPass);
static void RstNetHandler(void);
static void NewMaxConnHandler(uint8_t newVal);

static char ssid[MAX_SSID_LENGTH] = DEFAULT_SSID;
static char password[MAX_PASSWORD_LENGTH] = DEFAULT_PASSWORD;
static uint8_t numConnSetting = DEFAULT_NUMCONNECTIONS;

static volatile unsigned int AP_FLAGS = 0;

void AccessPointController(ApData data)
{
    NetUpHandler();
    NewSsidHandler(&data.ssid[0]);
    PwChangeHandler(&data.password[0]);
    RstNetHandler();
    NewMaxConnHandler(data.maxConn);
}



bool SetApFlag(unsigned int flags)
{
    if(IsFlagSet(AP_FLAGS, flags))
        return false;

    AP_FLAGS = SetFlag(AP_FLAGS, flags);

    if (IsFlagSet(AP_FLAGS, flags))
        return true;

    return false;
}



bool ResetApFlag(unsigned int flags)
{
    if(!IsFlagSet(AP_FLAGS, flags))
        return false;

    AP_FLAGS = ResetFlag(AP_FLAGS, flags);

    if (!IsFlagSet(AP_FLAGS, flags))
        return true;

    return false;
}



bool IsApFlagSet(unsigned int flags)
{
    return IsFlagSet(AP_FLAGS, flags);
}



uint8_t PassMaxConnSetting(void)
{
    return numConnSetting;
}



uint8_t PassNumConnDevices(void)
{
    const uint8_t failure = 11;

    esp_err_t err;
    wifi_sta_list_t stationInfo;

    err = esp_wifi_ap_get_sta_list(&stationInfo);

    if (err == ESP_OK)
        return (uint8_t)stationInfo.num;

    return failure;
}



void PassSsid(char *str)
{
    strcpy(str, ssid);
}



void PassPassword(char *str)
{
    strcpy(str, password);
}



static bool GetFlashSsid(char *id, size_t *len)
{
    return strReadFlash(SSID_MEM, id, len);
}



static bool GetFlashPassword(char *pass, size_t *len)
{
    return strReadFlash(PASSWORD_MEM, pass, len);
}



static bool GetFlashNumConn(uint8_t *numConn)
{
    return u8ReadFlash(NUMCONN_MEM, numConn);
}



static bool SetFlashSsid(char *id)
{
    return strWriteFlash(SSID_MEM, id);
}



static bool SetFlashPassword(char *pass)
{
    return strWriteFlash(PASSWORD_MEM, pass);
}



static bool SetFlashNumConn(uint8_t numConn)
{
    return u8WriteFlash(NUMCONN_MEM, numConn);
}



static bool StartWifi(char *id, char *pass, uint8_t numConn)
{
    wifi_init_config_t wifiInitConfig = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&wifiInitConfig);

    esp_wifi_set_mode(WIFI_MODE_AP); 

    wifi_config_t ap_config = {
        .ap = {
            .ssid = DEFAULT_SSID,
            .channel = WIFI_CHANNEL,
            .password = DEFAULT_PASSWORD,
            .max_connection = numConn,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .pmf_cfg = {
                .required = false,
            },
        },
    };

    //memcpy(ap_config.ap.ssid, id, MAX_SSID_LENGTH);

    esp_wifi_set_config(WIFI_IF_AP, &ap_config);
    esp_err_t err = esp_wifi_start();

    if (err == ESP_OK)
        return true;

    return false;
}



static bool StopWifi(void)
{
    esp_err_t err = esp_wifi_stop();

    if (err == ESP_OK)
        return true;

    return false;
}


static void NetUpHandler(void)
{
    if (IsApFlagSet(AP_FLAG_NET_UP))
        return;
    
    bool temp = true;
    size_t ssidLen, passLen;

    temp = GetFlashSsid(&ssid[0], &ssidLen) ? temp : false;
    temp = GetFlashPassword(&password[0], &passLen) ? temp : false;
    temp = GetFlashNumConn(&numConnSetting) ? temp : false;

    temp = StartWifi(ssid, password, numConnSetting);

    if (temp)
    {
        (void)SetApFlag(AP_FLAG_NET_UP);
    }
    else
    {
        (void)ResetApFlag(AP_FLAG_NET_UP);
        (void)SetApFlag(AP_FLAG_RST_NET);
    }
}



static void NewSsidHandler(char *newSsid)
{
    if (!IsApFlagSet(AP_FLAG_NEW_SSID))
        return;

    bool temp = true;

    temp = SetFlashSsid(newSsid) ? temp : false;

    if (temp)
    {
        (void)ResetApFlag(AP_FLAG_NEW_SSID);
        (void)SetApFlag(AP_FLAG_RST_NET);
    }
}



static void PwChangeHandler(char *newPass)
{
    if(!IsApFlagSet(AP_FLAG_PW_CHANGE))
        return;

    bool temp = true;

    temp = SetFlashPassword(newPass) ? temp : false;

    if (temp)
    {
        (void)ResetApFlag(AP_FLAG_PW_CHANGE);
        (void)SetApFlag(AP_FLAG_RST_NET);
    }
}



static void RstNetHandler(void)
{
    if (!IsApFlagSet(AP_FLAG_RST_NET))
        return;

    bool temp = true;

    temp = StopWifi() ? temp : false;

    if (temp)
    {
        (void)ResetApFlag(AP_FLAG_RST_NET);
        (void)ResetApFlag(AP_FLAG_NET_UP);
    }
}



static void NewMaxConnHandler(uint8_t newVal)
{
    if(!IsApFlagSet(AP_FLAG_NEW_MAXCONN))
        return;

    bool temp = true;

    temp = SetFlashNumConn(newVal) ? temp : false;

    if (temp)
    {
        (void)ResetApFlag(AP_FLAG_NEW_MAXCONN);
        (void)SetApFlag(AP_FLAG_RST_NET);
    }
}



