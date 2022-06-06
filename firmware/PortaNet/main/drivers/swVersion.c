/**
 * @file swVersion.c
 * @author Joe Maier, joemaier2@gmail.com
 * @brief software versioning driver source file
 * @date 2022-06-05
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "swVersion.h"
#include <stdio.h>
#include <string.h>


#define MAJOR_VERSION_NUM       "1"
#define MINOR_VERSION_NUM       "1"

#define VERSION_PREFIX          MAJOR_VERSION_NUM "." MINOR_VERSION_NUM "."

#define MAJOR_VERSION_LEN        3
#define MINOR_VERSION_LEN        3

static void GetTime(char *buffer);
static void GetDate(char *buffer);


void GetSwVersion(char *buffer, int *len)
{
   char majorMinor[] = VERSION_PREFIX;

   char timeVal[TIME_LEN];
   GetTime(timeVal);

   char dateVal[DATE_LEN];
   GetDate(dateVal);

   strncat(buffer, majorMinor, sizeof(majorMinor)-1);
   strncat(buffer, dateVal, sizeof(dateVal)-1);
   strncat(buffer, timeVal, sizeof(timeVal)-1);

   *len = strlen(buffer);
}



void GetMajorVersion(char *buffer, int *len)
{
   char temp[MAJOR_VERSION_LEN] = MAJOR_VERSION_NUM;

   strcpy(buffer, temp);
   *len = strlen(buffer);
}



void GetMinorVersion(char *buffer, int *len)
{
   char temp[MINOR_VERSION_LEN] = MINOR_VERSION_NUM;

   strcpy(buffer, temp);
   *len = strlen(buffer);
}



void GetBuildDate(char *buffer, int *len)
{
   GetDate(buffer);

   *len = strlen(buffer);
}



void GetBuildTime(char *buffer, int *len)
{
   GetTime(buffer);

   *len = strlen(buffer);
}



static void GetTime(char *buffer)
{
   char timeVal[] = __TIME__;
   size_t timeLen = strlen(timeVal);
   int bufferIndex = 0;

   for (size_t i=0; i<timeLen; i++)
   {
      if (timeVal[i] != ':')
      {
         buffer[bufferIndex] = timeVal[i];
         bufferIndex++;
      }
   }
   buffer[bufferIndex] = '\0';

}



static void GetDate(char *buffer)
{
   char dateVal[] = __DATE__;
   size_t dateLen = strlen(dateVal);
   char month[4] = {dateVal[0], dateVal[1], dateVal[2], '\0'};

   if(strcmp(month, "Jan") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '1';
   }
   else if(strcmp(month, "Feb") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '2';
   }
   else if(strcmp(month, "Mar") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '3';
   }
   else if(strcmp(month, "Apr") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '4';
   }
   else if(strcmp(month, "May") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '5';
   }
   else if(strcmp(month, "Jun") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '6';
   }
   else if(strcmp(month, "Jul") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '7';
   }
   else if(strcmp(month, "Aug") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '8';
   }

   else if(strcmp(month, "Sep") == 0)
   {
      buffer[0] = '0';
      buffer[1] = '9';
   }
   else if(strcmp(month, "Oct") == 0)
   {
      buffer[0] = '1';
      buffer[1] = '0';
   }
   else if(strcmp(month, "Nov") == 0)
   {
      buffer[0] = '1';
      buffer[1] = '1';
   }
   else if(strcmp(month, "Dec") == 0)
   {
      buffer[0] = '1';
      buffer[1] = '2';
   }
   else
   {
      buffer[0] = '0';
      buffer[1] = '0';
   }


   int bufferIndex = 2;

   for (size_t i=3; i<dateLen; i++)
   {
      if (dateVal[i] != ' ')
      {
         buffer[bufferIndex] = dateVal[i];
         bufferIndex++;
      }
   }
   buffer[bufferIndex] = '\0';
}
