#ifndef CONFIG_H
#define CONFIG_H

//#######################  User Settings ####################################
/*Which DCS-BIOS fork are you using? 
------------------------------------------------------------
DCSBIOS_DEFAULT = https://github.com/DCS-Skunkworks/dcs-bios-arduino-library
Using USB for data communication
------------------------------------------------------------
DCSBIOS_WIFI_FORK = https://github.com/SCUBA82/dcs-bios-arduino-library
Using Wifi for data communication
*/

//#define DCSBIOS_DEFAULT   
#define DCSBIOS_DEFAULT 
#ifdef DCSBIOS_DEFAULT 
  // Otherwise DCS-Skunkworks doesn't compile 
  #define DCSBIOS_ESP32 
#endif  

// Automatically load the proper screen drivers. Keep uncommented your screen
// To add more screen, you need to have one SCREEN_display_drivers.h
// Check README for details
#define WAVESHARE_ESP32S3_NO_TOUCH
// #define JINCAY_ESP32_8048S070C

// Wifi credentials if Wifi is enabled
#ifdef DCSBIOS_WIFI_FORK
  char ssid[] = "XXXXX";
  char passwd[] = "XXXXX";
#endif 


/* Enable DCS BIOS input command forward
   Disable this option if no physical inputs are connected to the ZX7D00CE01S board.
*/
//#define ENABLE_DCS_BIOS_INPUTS

#endif