# CO-Sensor with ESP32 and MQ-7

## Developing
There are a lot of options for writing code for the esp32 and for flashing it e.g. Arduino IDE, VScode with Arduino extention, PlattformIO. All possibilities to develop with the esp32 are listed and described [here](https://github.com/espressif/arduino-esp32/).

When uploading to esp32, don't forget to press IO0 on it when it tries to connect to the esp32.

When you want to keep track of which firmware is flashed on your ESP32, you can add update_git_hash.sh as git hook to your local git repository. Just add a file named `post-commit` to `.git/hooks/` and add the line `./update_git_hash.sh` or run this script manually before flashing, when you are not using the makefile.

### Arduino IDE
Prepare your IDE like described and then open
`CO-Sensor_MQ-7.ino`

`chose ESP32 DevModule` as Board
set partition scheme to `Minimal SPIFFS (Large `

### VScode with Arduino extention
Your arduino.json could look like this
```
{
    "port": "/dev/ttyUSB0",
    "board": "esp32:esp32:esp32",
    "configuration": "PSRAM=disabled,PartitionScheme=min_spiffs,CPUFreq=240,FlashMode=qio,FlashFreq=80,FlashSize=4M,UploadSpeed=921600,DebugLevel=debug",
    "sketch": "CO-Sensor_MQ-7.ino",
    "output": "./build"
}
```

### PlatformIO - VScode
All necessery informations are already provided in platformio.ini. When your esp32 is connected via USB you can simply press upload.

### PlatformIO - CLI
When you have installed PlatformIO on your computer, you can just use the provided Makefile in this repository and run
`make upload` to download all dependencies, build the code, and upload it to your ESP-32 in one step.

#### Over the air firmware update (OTA)
More information: https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/ota.html


#### Debugging
The makros of [esp_log.h](https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/log.html) are used to send serial debug messages. When you open a serial monitor and connect the esp32 via USB you should see them. The build flag `DCORE_DEBUG_LEVEL` must be set for this. When you are compiling with plattformio, this is already done in plattformio.ini. In the arduino ide you have to set Tools->Core Debug Level. For the arduino extention in vscode the example above already gives the right flag.
When you got a JTAG adapter e.g. [jlink](https://www.ebay.de/itm/ARM7-ARM9-ARM11-J-link-V8-Emulator-Cortex-M3-IAR-STM32-JTAG-Schnittstelle-CYED/233389427917?hash=item3657180ccd:g:Ex4AAOSwYIxX-8DR) you can also do inline debugging with the [unified debugger of plattformio](https://docs.platformio.org/en/latest/plus/debugging.html).

## Licensing

This project is licensed under the terms of the GPL-3.0.
