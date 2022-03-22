#include "ApInterface.h"


static ApData ApDataBuffer;


void TaskAccessPoint(void *pvoid)
{
    while(1)
    {
        AccessPointController(ApDataBuffer);
        vTaskDelay(portTICK_PERIOD_MS);
    }
}



bool ReqNewSsid(char *ssid, int ssidLen)
{
    //check string leng
    if ((ssidLen > MAX_SSID_LENGTH) || (ssidLen < MIN_SSID_LENGTH))
        return false;

    //check new SSID is unprocessed
    if (IsApFlagSet(AP_FLAG_NEW_SSID))
        return false;

    //accept and add new ssid to buffer
    strcpy(ApDataBuffer.ssid, ssid);
    SetApFlag(AP_FLAG_NEW_SSID);

    return true;
}



bool ReqNewPassword(char *password, int passwordLen)
{
    //check string length
    if ((passwordLen > MAX_PASSWORD_LENGTH) || (passwordLen < MIN_PASSWORD_LENGTH))
        return false;

    //check new password is unprocessed
    if (IsApFlagSet(AP_FLAG_PW_CHANGE))
        return false;

    //accept and add new password to buffer
    strcpy(ApDataBuffer.password, password);
    SetApFlag(AP_FLAG_PW_CHANGE);

    return true;
}



bool ReqApRestart(void)
{
    //check if reset is already wanted
    if (IsApFlagSet(AP_FLAG_RST_NET))
        return false;

    if (!IsApFlagSet(AP_FLAG_NET_UP))
        return false;

    SetApFlag(AP_FLAG_RST_NET);
    
    return true;
}



unsigned int GetNumConnections(void)
{
    return PassNumConnDevices();
}



void GetSsid(char *ssid)
{
    PassSsid(ssid);
}



void GetPassword(char *password)
{
    PassPassword(password);
}



bool ReqNewMaxConn(int maxConn)
{
    if ((maxConn > MAX_NUMCONNECTIONS) || (maxConn < MIN_NUMCONNECTIONS))
        return false;

    if (IsApFlagSet(AP_FLAG_NET_UP))
        return false;

    ApDataBuffer.maxConn = maxConn;
    SetApFlag(AP_FLAG_NEW_MAXCONN);

    return true;
}


