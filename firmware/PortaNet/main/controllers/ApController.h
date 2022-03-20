#ifndef APCONTROLLER_H
#define APCONTROLLER_H

#include "../interfaces/ApInterface.h"
#include <stdbool.h>

#define MAX_SSID_LENGTH         32 //bytes
#define MIN_SSID_LENGTH         5 //bytes
#define MAX_PASSWORD_LENGTH     64 //bytes
#define MIN_PASSWORD_LENGTH     10 //bytes
#define MAX_NUMCONNECTIONS      10
#define MIN_NUMCONNECTIONS      2

#define DEFAULT_SSID                "DefualtSsid"
#define DEFUALT_PASSWORD            "1234567890"
#define DEFUALT_NUMCONNECTIONS      3

#define WIFI_CHANNEL    0

enum flags {
    AP_FLAG_NET_UP      = 0b1 << 0,
    AP_FLAG_NEW_SSID    = 0b1 << 1,
    AP_FLAG_PW_CHANGE   = 0b1 << 2,
    AP_FLAG_RST_NET     = 0b1 << 3,
    AP_FLAG_NEW_MAXCONN = 0b1 << 4
}AP_FLAGS;


typedef struct {
    char ssid[MAX_SSID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    uint8_t maxConn;
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
 * @return uint8_t current number of connected devices
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



#endif