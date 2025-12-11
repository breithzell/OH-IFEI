# Standalone F/A18C IFEI Display controller for DCS-WORLD

This project is all about a DCS-WORLD compatible, stand-alone F/A18C IFEI display emulation. 
The original from [Scuba](https://github.com/SCUBA82/OH-IFEI) is based on a ZX7d00XE01S 7" display, powered by an ESP32s3.

This fork made the original code compatible with the [Jincay ESP32-8048S070C](https://www.tinytronics.nl/en/development-boards/microcontroller-boards/with-wi-fi/jingcai-esp32-8048s070c-7-inch-tft-lcd-display-800*480-pixels-with-touchscreen-esp32-s3).

It relys on pure DCS-BIOS input without the need of an additnional HDMI connection to the display.

# Hardware
Most of the information are available from the documentation. However, [ESP3D.io](https://esp3d.io/ESP3D-TFT/Version_1.X/hardware/esp32-s3/sunton-70-8048/) has a very nice summary that is exactly what we need for this project. Follow is a summary of their website.

## Features summary
- ESP32-S3 dual-core Xtensa 32-bit LX7 microprocessor, up to 240 MHz with 384KB ROM, 512KB SRAM
- 2.4GHz WiFi and Bluetooth 5
- FLASH: 16MB
- PSRAM: 8MB
- Micro-SD card slot (SPI)
- 7-inch 800x480 TFT display - EK9716 (Parallel RGB-565 interface)
- Capacitive touch panel - GT911 (i2C - 0x5D or 0x14)
- Audio amplifier MAX98357 (i2s) Speaker
- 1 USB-C to Serial 0 (CH340C)
- I2C / SPI / GPIOs
- Boot and reset buttons
- Dimension: 181.0mm x 108.0mm
- Header P1 (4 pins) (UART): Gnd, Rx, Tx, +5V
- Header P2 (4 pins) (SPI): IO13, IO12, IO11, IO19
- Header P3 (4 pins) (USB/UART): IO20, IO19, IO18, IO17
- Header P4 (4 pins) : IO18, IO17, +3.3v, Gnd
- Header P5 (4 pins) : IO18, IO17, +3.3v, Gnd
- Header P6 (2 pins) Speaker: (+) (-)

## USB Connection
The screen is plug and play. You can just plug it via an USB-C and you will be able to program it.

## GPIO Pins 

| Usage | Jincay ESP32-8048S070C	 | waveshare-esp32s3-no-touch |
| ---   | ---                      | ----                       |
| BOOT_BTN / I2S_BCLK (v1.1) | GPIO 0 | 
| CTP_INT* / I2S_LRCLK      | GPIO 18 |       NA    |
| CTP_RST     | GPIO 38 |     GPIO    | NA
| CTP_SCL     | GPIO 20 |     GPIO 9   |
| CTP_SDA / I2S_BCLK (v1.0) | GPIO 19 |       GPIO 8   |
| I2S_DIN     | GPIO 17 |     GPIO    |
| LCD_B0      | GPIO 15 |     GPIO 14   |
| LCD_B1      | GPIO 7 |      GPIO 38   |
| LCD_B2      | GPIO 6 |      GPIO 18   |
| LCD_B3      | GPIO 5 |      GPIO 17   |
| LCD_B4      | GPIO 4 |      GPIO 10   |
| LCD_DE      | GPIO 41 |     GPIO 5    |
| LCD_G0      | GPIO 9 |      GPIO 39   |
| LCD_G1      | GPIO 46 |     GPIO 0   |
| LCD_G2      | GPIO 3 |      GPIO 45   |
| LCD_G3      | GPIO 8 |      GPIO 48   |
| LCD_G4      | GPIO 16 |     GPIO 47   |
| LCD_G5      | GPIO 1 |      GPIO 21 |
| LCD_HSYNC   | GPIO 39 |     NA      |
| LCD_PCLK    | GPIO 42 |     GPIO 7   |
| LCD_R0      | GPIO 14 |     GPIO 1   |
| LCD_R1      | GPIO 21 |     GPIO 2   |
| LCD_R2      | GPIO 47 |     GPIO 40   |
| LCD_R3      | GPIO 48 |     GPIO 41  |
| LCD_R4      | GPIO 45 |     GPIO 42   |
| LCD_VSYNC   | GPIO 40 |     GPIO 3   |
| NA          | GPIO 33 |     GPIO    |
| NA          | GPIO 34 |     GPIO    |
| NC / NA     | GPIO 35 |     GPIO    |
| NC / NA     | GPIO 36 |     GPIO    |
| NC / NA     | GPIO 37 |     GPIO    |
| SD_CS       | GPIO 10 |     GPIO    |
| SD_MISO     | GPIO 13 |     NA   |
| SD_MOSI     | GPIO 11 |     NA   |
| SD_SCK      | GPIO 12 |     NA   |
| TFT_BL      | GPIO 2 |      GPIO ?  |
| U0RXD       | GPIO 44 |     GPIO ?   |
| U0TXD       | GPIO 43 |     GPIO ?  |


### External Pullup Resistors 
No idea - this needs to be checked if you want to use the interfaces P1 -> P6 with the IFEI buttons. 

# Installation and Configuration 
This project is ment to be used along with platformIO but can be easily ported to Arduino IDE.

## PlatformIO settings
You need to modify `platformio.ini`. Mainly the following entries: 
```
upload_port = COM6
```

If you want to activate the debug option, uncomment: 
```
;debug_tool = esp-builtin
;build_type = debug 
;debug_init_break = tbreak setup
;upload_speed = 200000
```

## Quick Guide
- Clone this repository
- Modifiy the platformio.ini config with the corrrect COM port (if you use Arduino IDE, no idea what you need to do)
- Build & Upload Filesystem Image
- Upload code
- Eventually reboot the screen by unplug & plug

You should have now the demo version of the code running. Start DCS, DCS-Bios, and it should work in game. If not, reboot the screen.

# In depth configuration
This part explains what are each component of the code, and how you may have to change them to adapt to your screen. 

## Configuration
There are some configurable options within `config.h`. There are only two options here: what version of DCS-Bios to use, and the credentials to allow the ESP32 to connect to your wifi.

### DCS Fork
The projects allows to use different forks of DCS-BIOS. The default version is the
- [DCS-BIOS Skunkworks Fork](https://github.com/DCS-Skunkworks/dcs-bios-arduino-library) that uses the serial protocoll to communicate with DCS. This is the version used by the [OpenHornet](https://github.com/jrsteensen/OpenHornet) project.
- [DCS-BIOS Scuba Fork](https://github.com/SCUBA82/dcs-bios-arduino-library) that is Scuba's update on DCS-Bios that allow to communicate with WiFi. I do not use that, so I have no idea how it works.

### Using a different display?
If you are using a different display, you need to modify `display_drivers.h` with the pinouts of your screen. This repository is currently only for the Jincay ESP32-8048S070C.

If you are using a screen that has fewer available storage, you may not be able to store the fonts needed to run the code. Currently Ash is working on an adaptation of the code to make it work with less. Check with him for updates. 

If you are using a screen with a different resolution, many adaptation will be needed. This is not covered by this README. Good luck!

# Fonts
The fonts used in this project were directly inspired by the IFEI representation in DCS-WORLD. The [VLW Font](https://wiki.seeedstudio.com/Wio-Terminal-LCD-Anti-aliased-Fonts/)  format was chosen since it offers lightweight anti aliased font capabilities which looks way more clean than bitmap fonts. Everything below is from the original repository from Scuba. This fork does not touch to any of that.

## How fonts were created
- DCS-WORLD textures were used as templates. 
- [Vector graphics](https://github.com/SCUBA82/OH-IFEI/tree/main/workdir/Fonts/Vectors) were created by tracing the outlines of the font elements.

<img src="https://github.com/SCUBA82/OH-IFEI/blob/main/workdir/Documentation/pictures/vector-Trace.png" width="400">

- Vector graphics were imported in ["font forge"](https://fontforge.org/en-US/)

<img src="https://github.com/SCUBA82/OH-IFEI/blob/main/workdir/Documentation/pictures/Fontforge-IFEI-DATA.png" width="400">

- The [finished fonts](https://github.com/SCUBA82/OH-IFEI/tree/main/workdir/Fonts/Fonts/TrueType) were exported as ["True Type fonts"](https://github.com/SCUBA82/OH-IFEI/tree/main/workdir/Fonts/Fonts/TrueType) and installed in windows.
- The TTF Fonts were converted to [VLW Font](https://wiki.seeedstudio.com/Wio-Terminal-LCD-Anti-aliased-Fonts/) format using [processing](https://processing.org/) with the "smooth" option

  <img src="https://github.com/SCUBA82/OH-IFEI/blob/main/workdir/Documentation/pictures/Processing.png" width="400">

- The converted VLW fonts are stored on the esp32s3 in littlefs


# Image Sprites

To display the nozzel gauges, [individual images](https://github.com/SCUBA82/OH-IFEI/tree/main/workdir/Images) for each possible pointer position and color were created.
Again DCS-WORLD textures were used as templates to outline custom vector graphics.

To overcome some sprite overlapping issues, the color "0x000000 (pure black)" was defined to be transparent within LoyvanGFX.
Areas which are intendet to have a black background were defined with the color "0x010000" which still looks pure black. 


![Transparent black](https://github.com/SCUBA82/OH-IFEI/blob/main/workdir/Documentation/pictures/transparent.png)





