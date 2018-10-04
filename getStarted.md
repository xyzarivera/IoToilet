# Getting Started with the IoToilet
This document explains how to build your IoToilet circuit and integrate it to a Twitter account.
* Clone or Download the IoToilet Github repository
* Build your IoToilet circuit
* Test the light-dependent comparator circuit
* Create your own IoToilet Twitter account
* Build your IFTTT Applet
* Upload the IoToilet.ino file to the ESP8266

## Clone or Download the IoToilet Github repository
To get started, you must first clone or download then unzip the IoToilet repository.

## Build your IoToilet circuit 
Complete the listed hardware components then follow the schematic diagram in building the circuit.
### Schematic Diagrams:
You can check the Schematic Diagrams here. It also includes a Fritzing file
and a breadboard view.
### Hardware Components:
Datasheets are linked to the components
* [ESP-12f](https://www.elecrow.com/download/ESP-12F.pdf)
* [LM393](http://www.ti.com/lit/ds/symlink/lm393-n.pdf) Low-offset Dual Comparator 
* Light-dependent Resistor (LDR)
* Light-emitting Diode (LED)
* Resistors
    * 330Ω
    * 10kΩ
* 10kΩ potentiometer
* Push button
* [CP2102](https://www.sparkfun.com/datasheets/IC/cp2102.pdf) USB to Serial converter

## Test the light-dependent comparator circuit
You can learn more about the circuit on this [Youtube video](https://www.youtube.com/watch?v=McPBS7IAUZA&t=70s). I just made a modification where in the LED turns on when there is light detected.(I reveresed the LED). The LED is a physical indicator that the IoToilet is working as it detects the light in the comfort room.

### Adjust your threshold using the potentiometer
Don't forget to adjust your threshold for the light detection as your comfort room may have ambient light vs light from a light bulb. This will help the circuit differentiate light by intensity when you turn on the light switch.

## Create your own IoToilet Twitter account.
Time to give your IoToilet its own Twitter handle!

## Build your IFTTT Applet
You can also read the short turtorial created by IFTTT [here](https://help.ifttt.com/hc/en-us/articles/115010361388-How-do-I-create-an-Applet-).
1. Go to IFTTT.com and create your account
   ![IFTTT](/docs/images/1.PNG)
2. We will create a New Applet. An Applet connects two or more apps or devices together. It is similar to an API in software development. You can read more about Applets [here](https://help.ifttt.com/hc/en-us/articles/115010361348-What-is-an-Applet-)On the upper-right side of the website, click on the down arrow and choose `New Applet` and you will be directed to a new screen
   ![New Applet](/docs/images/2.PNG)
3. Choose the Service that will cause the trigger. Click the blue `+this`.
    * Choose/find the `Webhooks` Service.
    * Choose the `Receive a web request` trigger
    * Type `Maker_Event` as the Event Name
    * Click `Create Trigger`
    ![IFTTT](/docs/images/3.PNG)
4. Choose the Action Service. Click the blue `+that`.
    * Choose/find the `Twitter` Service
    * Choose the `Post a tweet` action
    * Type `*Test* The {{Value1}} Comfort Room is {{Value2}}. {{OccurredAt}}` in the Tweet text box
    * Click Create Action
   ![IFTTT](/docs/images/5.PNG)
5. Click Finish. You will be directed to your Applet's summary. You can still update your applet by clicking the gear icon on the upper-left side.
   ![IFTTT](/docs/images/6.PNG)
6. Go to the [Webhooks](https://ifttt.com/maker_webhooks) page to get your Maker Key. You will need this in the succeeding step. Click on the Setting button.
   ![IFTTT](/docs/images/7.PNG)
    * Copy the key from the last section of the URL. Do not give this key to others
      ![IFTTT](/docs/images/8.PNG)
## Upload the IoToilet.ino file to the ESP8266
To program the ESP8266, you will need to install the [Arduino Desktop IDE](https://www.arduino.cc/en/Main/Software) . To connect the ESP to your computer, you’ll need a [CP2102](https://www.sparkfun.com/datasheets/IC/cp2102.pdf) USB to Serial converter. It can provide power also to the board while testing.
You will also need to install the ESP8266 library in the Arduino Desktop IDE.

### Installing the ESP8266 Library:
Let's start with installing the ESP8266 board driver with boards manager in Arduino IDE. 

1. Start Arduino. Click on File menu then select Preferences.
2. Enter `http://arduino.esp8266.com/stable/package_esp8266com_index.json` into Additional Board Manager URLs field. You can add multiple URLs, separating them with commas. 
    
3. Open Boards Manager from Tools > Board menu and install the latest stable esp8266 platform 
4. Go to Tools again >  Board > Select Generic ESP8266 Module.
    - ESP8266 Arduino core documentation [link](https://arduino-esp8266.readthedocs.io/en/2.4.2/).
    - ESP8266 Arduino core github [link](https://github.com/esp8266/Arduino)

### Things to modify in the IoToilet.ino file
There are fields in the code that you need to modify for the IoToilet to connect to the internet a and other web services.

#### Network Credentials
Update your network credentials 
```
// Replace with your network credentials
const char* ssid     = "wifi SSID";
const char* password = "wifi password";
```
#### IFTTT Credentials
Update `Your_Key` (your Maker Key from the previous step) and `CRloc` (location of your comfort room) based on your IFTTT Applet. 
```
// IFTTT setup
const char *host = "maker.ifttt.com";
const char *Maker_Event = "Maker_Event";
const char *Your_Key = "Your_Key";
String CRloc = "Your Location";
```
### Uploading the IoToilet.ino to your ESP8266 
1. Check the Port number designated to your Clouduino.
    - For Windows: Find the COM Port number in the Device Manager
    - For MAC: Open terminal and type: "ls /dev/*"
    - For Linux: Open terminal and type: "ls /dev/tty*"
2. In the Arduino IDE, choose Tools Menu -> Board -> "Generic ESP8266 Module" under ESP8266 Modules
3. Suggested Tools settings:
    - Flash Mode -> "DIO"
    - Flash Size -> “512K (no SPIFFS)”
    - Debug port -> “Disabled” 
    - Debug Level -> “None”
    - IwIP Variant -> “v2 Lower Memory”
    - Reset Method -> “ck”
    - Crystal Frequency -> “26MHz”
    - Flash Frequency -> “40MHz”
    - CP U Frequency -> “80 MHz”
    - Builtin Led -> “2”
    - Upload Speed -> “921600” (Optional, for fastest upload speed)
    - Erase Flash -> “Only Sketch”
4. Choose the correct serial port for your board.
    - Choose Tools -> Port -> comX or /dev/tty.usbmodemXXXXX. (where X marks a sequentially or randomly assigned number.
5. Click the Upload icon.

##  Debugging and Troubleshooting
Failed upload is a common issue with programming ESP8266, (eg: "espcomm_sync failed" error), when encountered please try the following methods:
 - Check if power supply is sufficient. VCC pin should receive a stable 3.3V. Any lower than 2.9V supplied power causes upload to fail nor would the Clouduino function properly even on normal mode.
 - Use a very short USB cable as much as possible. Very long cables to tend fail UART communication due to delay induced by excess cable length.

Double check your code:
- Check if the strings you edited in modifying the code are enclosed in `" "`
