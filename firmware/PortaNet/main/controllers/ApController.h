#ifndef APCONTROLLER_H
#define APCONTROLLER_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_SSID_LENGTH         32 //bytes
#define MIN_SSID_LENGTH         5  //bytes
#define MAX_PASSWORD_LENGTH     64 //bytes
#define MIN_PASSWORD_LENGTH     10 //bytes
#define MAX_NUMCONNECTIONS      10
#define MIN_NUMCONNECTIONS      2
#define MIN_WIFI_CHANNEL        3
#define MAX_WIFI_CHANNEL        7
#define WIFI_CHANNEL_ERROR      2   //TODO: figure out why this is needed

#define DEFAULT_SSID                "DefaultSsid"
#define DEFAULT_PASSWORD            "1234567890"
#define DEFAULT_NUMCONNECTIONS      3
#define DEFAULT_WIFI_CHANNEL        1

enum ApFlags {
    AP_FLAG_NET_UP      = 0b1 << 0,
    AP_FLAG_NEW_SSID    = 0b1 << 1,
    AP_FLAG_PW_CHANGE   = 0b1 << 2,
    AP_FLAG_RST_NET     = 0b1 << 3,
    AP_FLAG_NEW_MAXCONN = 0b1 << 4,
    AP_FLAG_REQ_OFF     = 0b1 << 5,
    AP_FLAG_REQ_ON      = 0b1 << 6,
    AP_FLAG_REQ_RESET   = 0b1 << 7,
    AP_FLAG_NEW_CHANNEL = 0b1 << 8
};


typedef struct ApData{
    char ssid[MAX_SSID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    uint8_t maxConn;
    uint8_t channel;
}ApData;


/**
 * @brief set an access point flag high
 * 
 * @param flags flag or flags to set high from AP_FLAGS
 * @return true if all flags to be set went from low to high
 * @return false if any of the tags didn't go high or if flags were already high
 */
bool SetApFlag(unsigned int flags);


/**
 * @brief set a access point flag(s) low 
 * 
 * @param flags flag or flags to set low from AP_FLAGS
 * @return true if all flags to be reset when from high to low
 * @return false of any of the tags didn't go low or if flags were already low
 */
bool ResetApFlag(unsigned int flags);


/**
 * @brief see if flag(s) are set
 * 
 * @param flags to check if high
 * @return true if flags are high
 * @return false if any on the flags aren't high
 */
bool IsApFlagSet(unsigned int flags);


/**
 * @brief main access point controller function the interface should call
 * 
 * @param data access point data buffer to pass from interface to controller
 */
void AccessPointController(ApData data);


/**
 * @brief pass the number of max connections to the interface
 * 
 * @return uint8_t current number of allowed connection setting
 */
uint8_t PassMaxConnSetting(void);


/**
 * @brief pass the current number of connected devices to the interface
 * 
 * @return uint8_t current number of connected devices or a value of 11 if the a failure occured
 */
uint8_t PassNumConnDevices(void);


/**
 * @brief pass the current ssid name to the interface
 * 
 * @param str address where ssid name will be copied
 */
void PassSsid(char *str);


/**
 * @brief pass the current password to the inteface
 * 
 * @param str address where password will be copied
 */
void PassPassword(char *str);


/**
 * @brief pass the current list of macs
 * 
 * @param macbuffer buffer to pass the macs
 * @param ipbuffer buffer to pass the ips
 */
void PassStaInfo(uint8_t* macbuffer, uint32_t* ipbuffer);


/**
 * @brief pass the current wifi channel to the interface
 * 
 * @return uint8_t current wifi channel
 */
uint8_t PassWifiChannel(void);



#endif