/**
 * @file swVersion.h
 * @author Joe Maier, joemaier2@gmail.com
 * @brief software versioning driver header file
 * @date 2022-06-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SWVERSION_H_
#define SWVERSION_H_

#define VERSION_LEN     32
#define DATE_LEN        9
#define TIME_LEN        6


/**
 * @brief Get the Sw Version, major.minor.build
 * 
 * @param buffer to pass the software version to
 * @param len len of the pass software version
 */
void GetSwVersion(char *buffer, int *len);


/**
 * @brief Get the Major sw Version 
 * 
 * @param buffer to pass the major version number
 * @param len len of the major version number
 */
void GetMajorVersion(char *buffer, int *len);


/**
 * @brief Get the Minor sw Version 
 * 
 * @param buffer to pass the minor version number
 * @param len len of the minor version number
 */
void GetMinorVersion(char *buffer, int *len);


/**
 * @brief Get the Build Date
 * 
 * @param buffer to pass the build date
 * @param len of the build date
 */
void GetBuildDate(char *buffer, int *len);


/**
 * @brief Get the Build Time
 * 
 * @param buffer to pass the build time
 * @param len of the build time
 */
void GetBuildTime(char *buffer, int *len);


#endif
