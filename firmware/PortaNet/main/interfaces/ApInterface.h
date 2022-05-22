#ifndef APINTERFACE_H
#define APINTERFACE_H

#include <stdbool.h>

#define SSID_LENGTH         32 //bytes
#define PASSWORD_LENGTH     64 //bytes

/**
 * @brief freertos task for the wifi soft access point
 * 
 * @param pvoid 
 */
void TaskAccessPoint(void *pvoid);


/**
 * @brief request a new SSID or network ID of the wifi soft access point
 * 
 * @param ssid new name to use
 * @param ssidLen char length of the new name to use 
 * @return true if name can be used
 * @return false if name can't be used
 */
bool ReqNewSsid(char *ssid, int ssidLen);


/**
 * @brief request a new network password to be used for the wireless access point
 * 
 * @param password new password to use
 * @param passwordLen string length of the new password to use
 * @return true if the password can be used
 * @return false if the password can't be used
 */
bool ReqNewPassword(char *bufferPass, int passwordLen);


/**
 * @brief request the access point to restart
 * 
 * @return true if the restart can be processed
 * @return false if the restart can be processed
 */
bool ReqApRestart(void);


/**
 * @brief Get the number of currently connected devices
 * 
 * @return unsigned int number of connected devices
 */
unsigned int GetNumConnections(void);


/**
 * @brief Get the current SSID name
 * 
 * @param ssid char array to pass the current name too
 */
void GetSsid(char *ssid);


/**
 * @brief Get the current network password
 * 
 * @param password char arry to pass the current password to
 */
void GetPassword(char *password);


/**
 * @brief request a new number of max network connections
 * 
 * @param maxConn new max connections settings to set
 * @return true if new number of max connections can be used
 * @return false if new number of max connections can't be used
 */
bool ReqNewMaxConn(int maxConn);





#endif
