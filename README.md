# PC-communication
Display the temperatures and other things on a LCD 20x04 using Arduino UNO

Hardware Required: 

1x Arduino UNO
2x Temperature Sensors ( 3-pin)
1x LCD I2C; Size: 20x04
1x Ultrasonic Sensor HC-SR04
1x DC 5V motor or LED
1x Red LED
1x SlideS  Swtich
1x Potentiometer 10K (optional)
6x Transistors or Mosfets
2x Resistors fo 220 Ohms
3x Pushbuttons
1x USB breakout board (optional)

Other Things: 

Jumper Wires

OpenHardwareMonitor 2019 version

**Code is already Attached**

Connections: 

**Temperature Sensor:**
VCC: 5V or 3.3V
GND: GND
DO: A0

**LCD:**
SDA: A4 or SDA pin
SCl: A5 or SCL pin
VCC: 5v
GND: GND
JUMPER ONE ON THE OTHER SIDE: Potentiometer terminal 1
JUMPER TWO ON THE OHER SIDE: Potentiometer Wiper
Note: For better perfomance, connect terminal 2 of potentiometer to Arduino GND

**Ultrasonic Sensor:**
Trig: 
Echo:
VCC: 5v 
GND: GND
