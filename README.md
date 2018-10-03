# IoToilet

The Internet of our Toilet
IoToilet is a side project using the ESP-12 as a microcontroller, currently on its first iteration.
The idea was conceived from irritating inconvenience of standing up just to check the availability of the office comfort room. There were instances that the door was unlocked by a key from the outside even if the comfort room was occupied. The lack of an occupancy indicator is the cause of this dilemma. Thus, the IoToilet is born!


## How it Works
IoToilet is an Internet of Things project that uses a light-dependent resistor to check the occupancy of the comfort room. 
  - A lighted comfort room would mean it is occupied.

It uses the IFTTT Applet service to be able to tweet in its own Twitter account, [@IoToilet](https://twitter.com/IoToilet).
- Tweeting is triggered when there is a change in the light brightness (from bright to dark or from dark to light).

## Build Your Own IoToilet
Schematic diagrams and breadboard prototype can be found in this folder

### Hardware Components
* [ESP-12f](https://www.elecrow.com/download/ESP-12F.pdf)
* [LM393](http://www.ti.com/lit/ds/symlink/lm393-n.pdf) Low-offset Dual Comparator 
* Light-dependent Resistor (LDR)
* Light-emitting Diode (LED)
* Resistors
    * 330Ω
    * 10kΩ
* 10kΩ potentiometer
* push button
* [CP2102](https://www.sparkfun.com/datasheets/IC/cp2102.pdf) USB to Serial converter

### Software applications and Online Services
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [ESP8266 Library](https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/installing-the-esp8266-arduino-addon) 
* [IFTTT Applet Service](https://ifttt.com/discover)

## Getting Started
Full documentation on Getting Started here.
1. Clone or Download the IoToilet Github repository
2. Build your IoToilet circuit based on the schematic diagram.
3. Install the Arduino IDE and the ESP8266 Libraries.
4. Test the light-dependent comparator circuit and adjust your threshold using the potentiometer.
5. Create your own IoToilet Twitter account. 
6. Build your IFTTT Applet and connect it to your Twitter account.

## License
GNU Affero General Public License v3.0

## To-dos
 - Design a proper power supply circuit
 - Enable Sleep mode
 - Include a PIR motion sensor to increase detection success
 - Integrate to a Slack Chatbot
 - Create an API