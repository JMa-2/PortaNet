#include "ApController.h"

#define SSID_MEM        "ssid"
#define PASSWORD_MEM    "password"
#define NUMCONN_MEM     "numConnSetting"

static bool getFlashSsid(char *id, size_t *len);
static bool getFlashPassword(char *pass, size_t *len);
static bool getFlashNumConn(uint8_t *numConn);
static bool setFlashSsid(char *id);
static bool setFlashPassword(char *pass);
static bool setFlashNumConn(uint8_t numConn);
static bool startWifi(char *id, char *pass, uint8_t numConn);
static bool stopWifi(void);



void AccessPointController(ApData data)
{
    static char ssid[MAX_SSID_LENGTH] = DEFAULT_SSID;
    static char password[MAX_PASSWORD_LENGTH] = DEFAULT_PASSWORD;
    static uint8_t numConnSetting = DEFAULT_NUMCONNECTIONS;



}



bool SetApFlag(unsigned int flags)
{
    if(IsFlagSet(AP_FLAGS, flags))
        return false;

    SetFlag(AP_FLAGS, flags);

    if (IsFlagSet(AP_FLAGS, flags))
        return true;

    return false;
}



bool ResetApFlag(unsigned int flags)
{
    if(!IsFlagSet(AP_FLAGS, flags))
        return false;

    ResetFlag(AP_FLAGS, flags);

    if (!IsFlagSet(AP_FLAGS, flags))
        return true;

    return false;
}



bool IsApFlagSet(unsigned int flags)
{
    return IsFlagSet(AP_FLAGS, flags);
}



uint8_t PassMaxConnSetting(uint8_t num)
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



static bool getFlashSsid(char *id, size_t *len)
{
    return strReadFlash(SSID_MEM, id, len);
}



static bool getFlashPassword(char *pass, size_t *len)
{
    return strReadFlash(PASSWORD_MEM, pass, len);
}



static bool getFlashNumConn(uint8_t *numConn)
{
    return u8ReadFlash(NUMCONN_MEM, numConn);
}



static bool setFlashSsid(char *id)
{
    return strWriteFlash(SSID_MEM, id);
}



static bool setFlashPassword(char *pass)
{
    return strWriteFlash(PASSWORD_MEM, pass);
}



static bool setFlashNumConn(uint8_t numConn)
{
    return u8WriteFlash(NUMCONN_MEM, numConn);
}



static bool startWifi(char *id, char *pass, uint8_t numConn)
{
    wifi_init_config_t wifiInitConfig = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&wifiInitConfig);

    esp_wifi_set_mode(WIFI_MODE_AP);

    wifi_config_t ap_config = {
        .ap = {
            .ssid = {id[0]},
            .channel = WIFI_CHANNEL,
            .password = {pass[0]},
            .max_connection = numConn,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .pmf_cfg = {
                .required = false,
            },
        },
    };

    esp_wifi_set_config(WIFI_IF_AP, &ap_config);
    esp_err_t err = esp_wifi_start();

    if (err == ESP_OK)
        return true;

    return false;
}



static bool stopWifi(void)
{
    esp_err_t err = esp_wifi_stop();

    if (err == ESP_OK)
        return true;

    return false;
}






