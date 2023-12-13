# PC-communication
Display the temperatures and other things on a LCD 20x04 using Arduino UNO

Hardware Required: 

1x Arduino UNO
2x Temperature Sensors ( 3-pin)
1x LCD I2C; Size: 20x04
1x Ultrasonic Sensor HC-SR04
1x DC 5V motor or LED
1x Red LED
1x Slide Swtich
4x Potentiometer 10K (optional)
6x Transistors or Mosfets
2x Resistors of 220 Ohms
3x Pushbuttons
1x USB breakout board (optional)
1x RGB light emitting diode

Other Things: 

Jumper Wires

OpenHardwareMonitor 2019 version

**Code is already Attached**

**3 out of the 4 potentiometers, need to have their terminal 1 connected to external 6v Power supply (+ve) and terminal 2 to (-ve)** 

**Use resistors to connect leds**

Connections: 

**Temperature Sensor:**
VCC: 5V or 3.3V
GND: GND
DO: A0

**LCD:**
SDA: SDA pin
SCl: SCL pin
VCC: 5v
GND: GND
JUMPER ONE ON THE OTHER SIDE: Potentiometer terminal 1
JUMPER TWO ON THE OHER SIDE: Potentiometer Wiper
Note: For better perfomance, connect terminal 2 of potentiometer to Arduino GND

**Ultrasonic Sensor:**
Trig: 11
Echo: 10
VCC: 5v 
GND: GND

**LEDs:**
Red LED: 9
Motor or LED: 7

**Slide Switch:**
Terminal 1: 5V or 3.3V
Wiper: A1
Terminal 2: Not required

**Transistors: Also use different potentiometers for connections of transistor 4,5,6**

     *Transistor 1:*
     Collector: 3
     Base: 13
     Emitter: Short with emitter of transitor 4 and connect to RGB led Green Terminal

     *Transistor 2:*
     Collector: 5
     Base: 12
     Emitter: Short with emitter of transistor 5 and connect to RGB led Red terminal
     
     *transistor 3:*
     Collector: 6
     Base: 8
     Emitter: Short with emitter of transistor 6 and connect to RGB led blue terminal

     *transistor 4:*
     Collector: Potentiometer Wiper 
     Base: 1

     *transistor 5:*
     Collector: Potentiometer Wiper
     Base: 0

     *transistor 6:*
     Collector: Potentiometer Wiper
     Base: 2

**Pushbutton:**
1st: Between negative power supply from Arduino UNO to A2
2nd: Between negative power supply from Arduino UNO to A3

**USB breakout board:**
VCC : External Power Supply
GND : Negative
Data + : A4
Data - : A5

Note: This USb breakout board is connected for expansion of the I2C bus. This will allow you to connect extra I2C displays which use I2C

_________________________________________________________________________________________________________

**Things to do after completing Hardware part**

Step 1: Change the address in the code (line 55) as per the address of your I2C backpack

Step 2: Verify Pin Connections

Step 3: Upload the code to the Arduino Uno Attached by the name "PC_communication.ino"

Step 4: After uploading, You should get a screen without backlight, Saying the message "TMP 1: (value between -25 and 129); TMP 2: (value between -25 and 129) and CONNECTION FAILED on the next line"

Step 5: If it doesn't, Open the troubleshooting file

Step 6: Download Open Hardware Monitor (2019) on your computer

Step 7: Open this app, click on "options", Then on "Serial", then on "CONFIGURE" or "CONFIG". Select the COM on which your Arduino UNO is connected. Then CLick on "RUN"

Then the stats should be displayed on the LCD screen. if it doesn't, then check out the truoubleshooting file.
