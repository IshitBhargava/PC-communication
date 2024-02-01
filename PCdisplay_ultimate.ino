//Note: some of the comments are in the laungauage "Russian"
// ------------------------ Settings ----------------------------
// настройки пределов скорости и температуры по умолчанию (на случай отсутствия связи)
byte speedMIN = 10, speedMAX = 90, tempMIN = 30, tempMAX = 70;
#define DRIVER_VERSION 1                 // 0 - маркировка драйвера кончается на 4АТ, 1 - на 4Т
#define COLOR_ALGORITM 0                 // 0 или 1 - разные алгоритмы изменения цвета (строка 222)
#define ERROR_DUTY 90                    // скорость вентиляторов при потере связи
#define ERROR_BACKLIGHT 0                // 0 - гасить подсветку при потере сигнала, 1 - не гасить
#define ERROR_UPTIME 1                   // 1 - сбрасывать uptime при потере связи, 0 - нет
#define ERROR_TEMP 1    	               // 1 - показывать температуру при потере связи. 0 - нет
#define lcdaddr 0x3f                       // the address of the first LCD display
#define printByte(args)  write(args);    // do not change the values for normal functioning
#define TEMPERATURE_PRECISION 1000000000 // the precision for reading temperatures
#define lcd1col 20                       // the number of columns in lcd 1
#define lcd1row 4                        // the number of rows in lcd 1
#define time 40                          // the pulse of timer (don't change)
#define speed 400                        // fan speed
#define blinkfor1 0                      // set blinking cursor on = 1, set off = 0
#define blinkfor2 0                      // set blinking cursor on = 1, set off = 0
#define switchthreshold 700              // the threshold for switch
#define scantime 2000                    // the scantime pause
#define enable 1                         // 1 = enable writing data in EEPRON, 0 or anything else = not writing data in EEPROM
#define rval 255                           //startup value of colour red during startup
#define gval 255                           //startup value of colour green during startup
#define bval 255                           //startup value of colour green during startup
#define DEFAULT_TEMP1 69       // Example default value for temp1
#define DEFAULT_DISTANCE 69    // Example default value for distance
#define EEPROM_TEMP1_START 0    // Start address for temp1
#define EEPROM_DISTANCE_START 512 // Start address for distance

//note: if the values on "line '23,24,25' are 255, then a white colour should be observed during startup, if not then the LED or LED strip is damaged.

// ------------------------ Settings ----------------------------

//---------------------------EEPROM-----------------------------

int address = 0 ;                        //from which byte to start writing data
int rstaddress = 0;                     //from which byte to start writing if the EEPROM is full

int distance_addr = 512 ;                  //from which byte to start writing data
int distance_rstaddr = 512 ;              //from which byte to start writing data if EEPROM is full

//---------------------------EEPROM-----------------------------

// ----------------------- PINS ---------------------------
#define FAN_PIN 9         // на мосфет вентиляторов
#define R_PIN 3           // на мосфет ленты, красный
#define G_PIN 5           // на мосфет ленты, зелёный
#define B_PIN 6           // на мосфет ленты, синий
#define BTN1 A3           // первая кнопка
#define BTN2 A2           // вторая кнопка
#define SENSOR_PIN A0     // датчик температуры
#define switchPin  A1     //Switch pin
#define greenTautoPin  13 // transistor to control Green1
#define redTautoPin  12   // transistor to control red1
#define blueTautoPin  8   // transistor to control blue1
#define greenTmanualPin  1// transistor to control Green2
#define redTmanualPin  0  // transistor to control red2
#define blueTmanualPin  2 // transistor to control blue2
#define trigPin  11       //trigger pin of HC-SR04
#define echoPin  10       //echo pin of HC-SR04
#define motor  7          //motor or output pin
#define motorn 4          //motor negative

// ----------------------- PINS ---------------------------

// ----------------------Startup Message ------------------
  //---------------------------------Cursor------------------------------
  int a = 7 ;  // the column on which to print the message on the first line during setup()
  int e = 1 ;  //the row on which to print the message on the first line during setup()
  int c = 5 ;  //the column on which to print the message on the second line
  int d = 2 ;  //the row to the print the messge on second line during setup()

  int q = 5 ;  // the column on which to print the message on the third line during setup()
  int w = 3 ;  //the row on which to print the message on the third line during setup()
  int r = 5 ;  //the column on which to print the message on the *zero* line
  int t = 0 ;  //the row to the print the messge on *zero* line during setup()

  //---------------------------------Cursor------------------------------

  //--------------------------message--------------------------------------

  String line1 = "Stats" ;  //the message on line 1 during startup

  String line2 = " Monitor" ;  //the message on line 2 during startup

  String line3 = "Uttermost" ;  //the message on line 3 during startup

  String line0 = "Computer's"; //the message on line 0 during startup

  //--------------------------message--------------------------------------

// ----------------------Startup Message ------------------

//-----------------------Communication---------------------

  int baud = 9600;  //the baud rate on which the Arduino will comunicate

//-----------------------Communication---------------------

// ----------------- Ultrasonic control ------------------

  
  const int threshold = 10;  //the distance (if lesser than) turn on the motor

  unsigned long duration;  // variable (ignore)

  int distance;  //distance detected by the ultrasonic sensor in centimeters
  

// -------------------- Libraries ---------------------
#include <OneWire.h>            // библиотека протокола датчиков
#include <DallasTemperature.h>  // библиотека датчика
#include <string.h>             // библиотека расширенной работы со строками
#include <Wire.h>               // библиотека для соединения
#include <LiquidCrystal_I2C.h>  // библтотека дислея
#include <TimerOne.h>           // библиотека таймера
#include <EEPROM.h>             // For storing data in disk drive
// -------------------- Libraries ---------------------

// -------- LCD definition -------------
  LiquidCrystal_I2C lcd(lcdaddr, lcd1col, lcd1row);  // Create the first LCD
// -------- LCD definition -------------

//--------------- Other tasks -------------------------
OneWire oneWire(SENSOR_PIN);
DallasTemperature sensors(&oneWire);
DeviceAddress Thermometer1, Thermometer2;

byte degree[8] = {0b11100,  0b10100,  0b11100,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000};
// правый край полосы загрузки
byte right_empty[8] = {0b11111,  0b00001,  0b00001,  0b00001,  0b00001,  0b00001,  0b00001,  0b11111};
// левый край полосы загрузки
byte left_empty[8] = {0b11111,  0b10000,  0b10000,  0b10000,  0b10000,  0b10000,  0b10000,  0b11111};
// центр полосы загрузки
byte center_empty[8] = {0b11111, 0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111};
// блоки для построения графиков
byte row8[8] = {0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row7[8] = {0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row6[8] = {0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row5[8] = {0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111,  0b11111};
byte row4[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111,  0b11111};
byte row3[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111,  0b11111};
byte row2[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111,  0b11111};
byte row1[8] = {0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b00000,  0b11111};

char inData[82];       // массив входных значений (СИМВОЛЫ)
int PCdata[20];        // массив численных значений показаний с компьютера
byte PLOTmem[6][16];   // массив для хранения данных для построения графика (16 значений для 6 параметров)
byte blocks, halfs;
byte index = 0;
int display_mode = 6;
String string_convert;
unsigned long timeout, blink_timer,uptime_timer, plot_timer;
boolean lightState, reDraw_flag = 1, updateDisplay_flag, updateTemp_flag, timeOut_flag = 1;
int duty, LEDcolor;
int k, b, R, G, B, Rf, Gf, Bf;
byte mainTemp;
byte lines[] = {4, 5, 7, 6};
byte plotLines[] = {0, 1, 4, 5, 6, 7};    // 0-CPU temp, 1-GPU temp, 2-CPU load, 3-GPU load, 4-RAM load, 5-GPU memory
String perc;
unsigned long sec;
unsigned long mins, hrs;
byte temp1, temp2;
boolean btn1_sig, btn2_sig, btn1_flag, btn2_flag, btn3_flag, btn3_sig, timeOutLCDClear = 0, restoreConnectToPC=0;

// Названия для легенды графиков
const char plot_0[] = "CPU";
const char plot_1[] = "GPU";
const char plot_2[] = "RAM";

const char plot_3[] = "temp";
const char plot_4[] = "load";
const char plot_5[] = "mem";
// названия ниже должны совпадать с массивами сверху и идти по порядку!
static const char *plotNames0[]  = {
  plot_0, plot_1, plot_0, plot_1, plot_2, plot_1
};
static const char *plotNames1[]  = {
  plot_3, plot_3, plot_4, plot_4, plot_4, plot_5
};
// 0-CPU temp, 1-GPU temp, 2-CPU load, 3-GPU load, 4-RAM load, 5-GPU memory

//--------------- Other tasks -------------------------

void show_logo() {

  lcd.setCursor(a, e); 
  lcd.print(line1);
  lcd.setCursor(c, d);
  lcd.print(line2);
  lcd.setCursor(q, w);
  lcd.print(line3);
  lcd.setCursor(r, t);
  lcd.print(line0);
}
void debug() {
  lcd.clear();
  lcd.setCursor(0, 0);
  for (int j = 0; j < 5; j++) {
    lcd.print(PCdata[j]); lcd.print("  ");
  }
  lcd.setCursor(0, 1);
  for (int j = 6; j < 10; j++) {
    lcd.print(PCdata[j]); lcd.print("  ");
  }
  lcd.setCursor(0, 2);
  for (int j = 10; j < 15; j++) {
    lcd.print(PCdata[j]); lcd.print("  ");
  }
  lcd.setCursor(0, 3);
  for (int j = 15; j < 18; j++) {
    lcd.print(PCdata[j]); lcd.print("  ");
  }
}


void setup() {
  // инициализация дисплея
  lcd.init();
  lcd.backlight();
  if(blinkfor1 == 1){
    lcd.blink_on();
  } else {
    lcd.blink_off();
  }
  

  lcd.clear();            // очистить дисплей
  show_logo();            // показать логотип
  Wire.begin();           
  Serial.begin(baud);  //start serial communication at baud rate
  while (!Serial);
  Serial.println("I2C Scanner");

  Timer1.initialize(time);   // поставить частоту ШИМ 25 кГц (40 микросекунд)
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  analogWrite(R_PIN, rval);
  analogWrite(G_PIN, gval);
  analogWrite(B_PIN, bval);
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  sensors.begin();
  sensors.getAddress(Thermometer1, 0);
  sensors.setResolution(Thermometer1, TEMPERATURE_PRECISION);
  
  Timer1.pwm(FAN_PIN, speed);  // включить вентиляторы на 40%
  delay(2000);               // на 2 секунды
  lcd.clear();               // очистить дисплей
  PCdata[8] = speedMAX;
  PCdata[9] = speedMIN;
  PCdata[10] = tempMAX;
  PCdata[11] = tempMIN;

    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(motor, OUTPUT); // Sets the Motor as an Output
    pinMode(motorn, OUTPUT);  //sets a motor negative 

    pinMode(switchPin, INPUT);  // Set the switch pin as INPUT
    pinMode(greenTautoPin, OUTPUT);  // Set the green1 transistor pin as OUTPUT
    pinMode(redTautoPin, OUTPUT);  // Set the red1 transistor pin as OUTPUT
    pinMode(blueTautoPin, OUTPUT);  // Set the blue1 transistor pin as OUTPUT

    pinMode(greenTmanualPin, OUTPUT);    // Set the green2 transistor pin as OUTPUT
    pinMode(redTmanualPin, OUTPUT);    // Set the red2 transistor pin as OUTPUT
    pinMode(blueTmanualPin, OUTPUT);    // Set the blue2 transistor pin as OUTPUT

    verify();                        //check if there are any I2C devices
    if (EEPROM.read(EEPROM_TEMP1_START) == 255 && EEPROM.read(EEPROM_DISTANCE_START) == 255) {
    // EEPROM is not initialized, write default values
    initializeEEPROM();
    Serial.println("EEPROM not intialized");
  } else {
    Serial.println("EEPROM is intialized ( already )");
  }
    Serial.println("Setup Complete!");

}
// 8-maxFAN, 9-minFAN, 10-maxTEMP, 11-minTEMP, 12-mnlFAN

// ------------------------------ ОСНОВНОЙ ЦИКЛ -------------------------------
void loop() {

   //----------------------Transisistor control-----------------------
    
      int switchState = analogRead(switchPin);
      Serial.print("Switch value is: ");
      Serial.println(switchState);
 
  if (switchState >switchthreshold) {
    // If the switch is not pressed (LOW)
    digitalWrite(greenTautoPin, HIGH);  //connect the circuit using green1 transistor
    digitalWrite(redTautoPin, HIGH);  //connect the circuit using red1 transistor
    digitalWrite(blueTautoPin, HIGH);  //connect the circuit using blue1 transistor

    digitalWrite(greenTmanualPin, LOW);  //break the circuit using green2 transistor
    digitalWrite(redTmanualPin, LOW);  //break the circuit using red2 transistor
    digitalWrite(blueTmanualPin, LOW);  //break the circuit using blue2 transistor
    
  } else {
    // If the switch is pressed (HIGH)
    digitalWrite(greenTautoPin, LOW);  //break the circuit using green1 transistor
    digitalWrite(redTautoPin, LOW);  //break the circuit using red1 transistor
    digitalWrite(blueTautoPin, LOW);  //break the circuit using blue1 transistor
    
    digitalWrite(greenTmanualPin, HIGH);  //connect the circuit using green2 transistor
    digitalWrite(redTmanualPin, HIGH);  //connect the circuit using red2 transistor
    digitalWrite(blueTmanualPin, HIGH);  //connect the circuit using blue2 transistor
  }
  
    //-------------------------------Ultrasonic control--------------------------------------

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
     if(distance < threshold){
     digitalWrite(motor, HIGH);
     digitalWrite(motorn,LOW);
     }else{
     digitalWrite(motor, LOW);
     digitalWrite(motorn,LOW);
     }

 

  //-----------------------------EEPROM--------------------------------------------------------
  
  if(enable == 1){
    EEPROM.put(address, temp1);  //store the data in EEPROM
    address = address + 1;
    if(address == 511){
      Serial.println("EEPROM full upto 512 bytes. Deleting old records! ERROR CODE 0");        
      address = rstaddress;
    }

    EEPROM.put(distance_addr, distance); //store the data in EEPROM
    distance_addr = distance_addr + 1;
    if(distance_addr == 1023){
    Serial.println("EEPROM FULL (1023 bytes), Deleting old records! ERROR CODE 1");
    distance_addr = distance_rstaddr;
    }

  } else {
    Serial.print("Not Writing Data in EEPROM");
  }
  
  //-----------------------------EEPROM--------------------------------------------------------

  //----------------------------Data printing and other controls-----------------------------

  
  parsing();                          // парсим строки с компьютера
  updatePlot();                       // обновляем массив данных графика
  getTemperature();                   // получить значения с датчиков температуры
  dutyCalculate();                    // посчитать скважность для вентиляторов
  Timer1.pwm(FAN_PIN, duty * 10);     // управлять вентиляторами
  LEDcontrol();                       // управлять цветом ленты
  buttonsTick();                      // опрос кнопок и смена режимов
  updateDisplay();                    // обновить показания на дисплее
  timeoutTick();                      // проверка таймаута
  if (!restoreConnectToPC)                                 // если связь была потеряна, но восстановилась
      if (ERROR_UPTIME) uptime_timer = millis();        // сбросить uptime, если разрешено 
}
// ------------------------------ ОСНОВНОЙ ЦИКЛ -------------------------------

void buttonsTick() {
  btn1_sig = !digitalRead(BTN1);
  btn2_sig = !digitalRead(BTN2);
  if (btn1_sig && !btn1_flag) {
    display_mode++;
    reDraw_flag = 1;
    if (display_mode > 7) display_mode = 0;
    btn1_flag = 1;
  }
  if (!btn1_sig && btn1_flag) {
    btn1_flag = 0;
  }
  if (btn2_sig && !btn2_flag) {
    display_mode--;
    reDraw_flag = 1;
    if (display_mode < 0) display_mode = 7;
    btn2_flag = 1;
  }
  if (!btn2_sig && btn2_flag) {
    btn2_flag = 0;
  }
}

void getTemperature() {
  if (updateTemp_flag) {
    sensors.requestTemperatures();
    temp1 = sensors.getTempC(Thermometer1);
    updateTemp_flag = 0;
  }
}
void LEDcontrol() {
  b = PCdata[16];
  if (PCdata[13] == 1)          // если стоит галочка Manual Color
    LEDcolor = PCdata[15];      // цвет равен установленному ползунком
  else {                        // если нет
    LEDcolor = map(mainTemp, PCdata[11], PCdata[10], 0, 1000);
    LEDcolor = constrain(LEDcolor, 0, 1000);
  }

  if (COLOR_ALGORITM) {
    // алгоритм цвета 1
    // синий убавляется, зелёный прибавляется
    // зелёный убавляется, красный прибавляется
    if (LEDcolor <= 500) {
      k = map(LEDcolor, 0, 500, 0, 255);
      R = 0;
      G = k;
      B = 255 - k;
    }
    if (LEDcolor > 500) {
      k = map(LEDcolor, 500, 1000, 0, 255);
      R = k;
      G = 255 - k;
      B = 0;
    }

  } else {
    // алгоритм цвета 2
    // синий максимум, плавно прибавляется зелёный
    // зелёный максимум, плавно убавляется синий
    // зелёный максимум, плавно прибавляется красный
    // красный максимум, плавно убавляется зелёный

    if (LEDcolor <= 250) {
      k = map(LEDcolor, 0, 250, 0, 255);
      R = 0;
      G = k;
      B = 255;
    }
    if (LEDcolor > 250 && LEDcolor <= 500) {
      k = map(LEDcolor, 250, 500, 0, 255);
      R = 0;
      G = 255;
      B = 255 - k;
    }
    if (LEDcolor > 500 && LEDcolor <= 750) {
      k = map(LEDcolor, 500, 750, 0, 255);
      R = k;
      G = 255;
      B = 0;
    }
    if (LEDcolor > 750 && LEDcolor <= 1000) {
      k = map(LEDcolor, 750, 1000, 0, 255);
      R = 255;
      G = 255 - k;
      B = 0;
    }
  }

  Rf = (b * R / 100);
  Gf = (b * G / 100);
  Bf = (b * B / 100);
  analogWrite(R_PIN, Rf);
  analogWrite(G_PIN, Gf);
  analogWrite(B_PIN, Bf);
}

void dutyCalculate() {
  if (PCdata[12] == 1)                  // если стоит галочка ManualFAN
    duty = PCdata[14];                  // скважность равна установленной ползунком
  else {                                // если нет
    switch (PCdata[18]) {
      case 0: mainTemp = PCdata[0];                   // взять опорную температуру как CPU
        break;
      case 1: mainTemp = PCdata[1];                   // взять опорную температуру как GPU
        break;
      case 2: mainTemp = max(PCdata[0], PCdata[1]);   // взять опорную температуру как максимум CPU и GPU
        break;
      case 3: mainTemp = temp1;
        break;
      case 4: mainTemp = temp2;
        break;
    }
    duty = map(mainTemp, PCdata[11], PCdata[10], PCdata[9], PCdata[8]);
    duty = constrain(duty, PCdata[9], PCdata[8]);
  }
  if (!timeOut_flag) duty = ERROR_DUTY;               // если пропало соединение, поставить вентиляторы на ERROR_DUTY
}
void parsing() {
  while (Serial.available() > 0) {
    char aChar = Serial.read();
    if (aChar != 'E') {
      inData[index] = aChar;
      index++;
      inData[index] = '\0';
    } else {
      char *p = inData;
      char *str;
      index = 0;
      String value = "";
      while ((str = strtok_r(p, ";", &p)) != NULL) {
        string_convert = str;
        PCdata[index] = string_convert.toInt();
        index++;
      }
      index = 0;
      updateDisplay_flag = 1;
      updateTemp_flag = 1;
    }
    timeout = millis();
    timeOut_flag = 1;
    restoreConnectToPC = 1;
    lcd.backlight();    
   }
  }
   
void updatePlot() {
  if ((millis() - plot_timer) > (PCdata[17] * 1000)) {
    for (int i = 0; i < 6; i++) {           // для каждой строки параметров
      for (int j = 0; j < 15; j++) {        // каждый столбец параметров (кроме последнего)
        PLOTmem[i][j] = PLOTmem[i][j + 1];  // сдвинуть весь массив на шаг ВЛЕВО
      }
    }
    for (int i = 0; i < 6; i++) {
      // запомнить общее число полосок графика в ПОСЛЕДНИЙ элемент массива
      PLOTmem[i][15] = ceil(PCdata[plotLines[i]] / 3);
    }
    plot_timer = millis();
  }
}
void updateDisplay() {
  if (updateDisplay_flag) {
    if (reDraw_flag) {
      lcd.clear();
      switch (display_mode) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5: draw_plot_symb();
          break;
        case 6: draw_labels_1();
          break;
        case 7: draw_labels_2();
          break;
      }
      reDraw_flag = 0;
    }
    switch (display_mode) {
      case 0:
      case 1:
      case 2:
      case 3:
      case 4:
      case 5: draw_plot();
        break;
      case 6: draw_stats_1();
        break;
      case 7: draw_stats_2();
        break;
      case 50: debug();
        break;
    }
    updateDisplay_flag = 0;
  }
  if(timeOutLCDClear)
  {reDraw_flag = 1;}
}
void draw_stats_1() {
  timeOutLCDClear = 0;
  lcd.setCursor(4, 0); lcd.print(PCdata[0]); lcd.write(223);
  lcd.setCursor(17, 0); lcd.print(PCdata[4]);
  if (PCdata[4] < 10) perc = "% ";
  else if (PCdata[4] < 100) perc = "%";
  else perc = "";  lcd.print(perc);
  lcd.setCursor(4, 1); lcd.print(PCdata[1]); lcd.write(223);
  lcd.setCursor(17, 1); lcd.print(PCdata[5]);
  if (PCdata[5] < 10) perc = "% ";
  else if (PCdata[5] < 100) perc = "%";
  else perc = "";  lcd.print(perc);
  lcd.setCursor(17, 2); lcd.print(PCdata[7]);
  if (PCdata[7] < 10) perc = "% ";
  else if (PCdata[7] < 100) perc = "%";
  else perc = "";  lcd.print(perc);
  lcd.setCursor(17, 3); lcd.print(PCdata[6]);
  if (PCdata[6] < 10) perc = "% ";
  else if (PCdata[6] < 100) perc = "%";
  else perc = "";  lcd.print(perc);

  for (int i = 0; i < 4; i++) {
    byte line = ceil(PCdata[lines[i]] / 10);
    lcd.setCursor(7, i);
    if (line == 0) lcd.printByte(1)
      else lcd.printByte(4);
    for (int n = 1; n < 9; n++) {
      if (n < line) lcd.printByte(4);
      if (n >= line) lcd.printByte(2);
    }
    if (line == 10) lcd.printByte(4)
      else lcd.printByte(3);
  }
}
void draw_stats_2() {
  lcd.setCursor(16, 0); lcd.print(duty);
  if ((duty) < 10) perc = "% ";
  else if ((duty) < 100) perc = "%";
  else perc = "";  lcd.print(perc);

  lcd.setCursor(14, 1); lcd.print(temp1); lcd.write(223);
  lcd.setCursor(4, 2); lcd.print(PCdata[2]); lcd.write(223);
  lcd.setCursor(16, 2); lcd.print(PCdata[3]); lcd.write(223);

  lcd.setCursor(9, 3);
  sec = (long)(millis() - uptime_timer) / 1000;
  hrs = (float)floor((sec / 3600));
  mins = (float)floor(sec - (hrs * 3600)) / 60;
  sec = sec - (hrs * 3600 + mins * 60);
  if (hrs < 10) lcd.print(0);
  lcd.print(hrs);
  lcd.print(":");
  if (mins < 10) lcd.print(0);
  lcd.print(mins);
  lcd.print(":");
  if (sec < 10) lcd.print(0);
  lcd.print(sec);

  byte line = ceil(duty / 10);
  lcd.setCursor(6, 0);
  if (line == 0) lcd.printByte(1)
    else lcd.printByte(4);
  for (int n = 1; n < 9; n++) {
    if (n < line) lcd.printByte(4);
    if (n >= line) lcd.printByte(2);
  }
  if (line == 10) lcd.printByte(4)
    else lcd.printByte(3);
}
void draw_labels_1() {
  lcd.createChar(0, degree);
  lcd.createChar(1, left_empty);
  lcd.createChar(2, center_empty);
  lcd.createChar(3, right_empty);
  lcd.createChar(4, row8);
  lcd.setCursor(0, 0);
  lcd.print("CPU:");
  lcd.setCursor(0, 1);
  lcd.print("GPU:");
  lcd.setCursor(0, 2);
  lcd.print("GPUmem:");
  lcd.setCursor(0, 3);
  lcd.print("RAMuse:");
}
void draw_labels_2() {
  lcd.createChar(0, degree);
  lcd.createChar(1, left_empty);
  lcd.createChar(2, center_empty);
  lcd.createChar(3, right_empty);
  lcd.createChar(4, row8);

  lcd.setCursor(0, 0);
  lcd.print("FANsp:");
  lcd.setCursor(3, 1);
  lcd.print("Local Temp:");
  lcd.setCursor(0, 2);
  lcd.print("MOM:");
  lcd.setCursor(9, 2);
  lcd.print("HDDmax:");
  lcd.setCursor(0, 3);
  lcd.print("UPTIME:");
}
void draw_legend() {
  byte data = PCdata[plotLines[display_mode]];
  lcd.setCursor(16, 2); lcd.print(data);
  if (display_mode > 1) {
    if (data < 10) perc = "% ";
    else if (data < 100) perc = "%";
    else {
      perc = "";
    }
    lcd.print(perc);
  } else {
    if (data < 10) {
      lcd.write(223);
      lcd.print("  ");
    } else if (data < 100) {
      lcd.write(223); lcd.print(" ");
    } else {
      lcd.write(223);
    }
  }
}

void draw_plot() {
  draw_legend();

  for (byte i = 0; i < 16; i++) {                       // каждый столбец параметров
    blocks = floor(PLOTmem[display_mode][i] / 8);       // найти количество целых блоков
    halfs = PLOTmem[display_mode][i] - blocks * 8;      // найти число оставшихся полосок
    for (byte n = 0; n < 4; n++) {
      if (n < blocks) {
        lcd.setCursor(i, (3 - n));
        lcd.printByte(0);
      }
      if (n >= blocks) {
        if (n != 3) {
          lcd.setCursor(i, (3 - n));
          if (halfs > 0) lcd.printByte(halfs);
          for (byte k = n + 1; k < 4; k++) {
            lcd.setCursor(i, (3 - k));
            lcd.print(" ");
          }
          break;
        }
      }
    }
  }
}

void draw_plot_symb() {
  lcd.createChar(0, row8);
  lcd.createChar(1, row1);
  lcd.createChar(2, row2);
  lcd.createChar(3, row3);
  lcd.createChar(4, row4);
  lcd.createChar(5, row5);
  lcd.createChar(6, row6);
  lcd.createChar(7, row7);
  lcd.setCursor(16, 0);
  lcd.print(plotNames0[display_mode]);
  lcd.setCursor(16, 1);
  lcd.print(plotNames1[display_mode]);
}
void timeoutTick() {
  if ((millis() - timeout > 5000))
  { lcd.clear(); }  
  while (Serial.available() < 1){
  if ((millis() - timeout > 5000) && timeOut_flag) {        
    getTemperature();    
    index = 0;
    updateTemp_flag = 1;
    getTemperature();
    if(restoreConnectToPC)
    {
     reDraw_flag=1;
     restoreConnectToPC=0;
     if (reDraw_flag) {
     lcd.clear();
     reDraw_flag = 0;}
    } 
     if(ERROR_TEMP)
    {
      lcd.setCursor(3, 0);
      lcd.print("Local temp:");
      lcd.setCursor(14, 0); lcd.print(temp1); lcd.write(223);

    lcd.setCursor(5, 1);
    lcd.print("CONNECTION");
    lcd.setCursor(7, 2);
    lcd.print("FAILED");
    reDraw_flag = 0;
    updateDisplay_flag = 1;
    timeOutLCDClear = 1;
    if(timeOutLCDClear)
    {reDraw_flag = 1;}
    if (!ERROR_BACKLIGHT) lcd.noBacklight();
  }}}
}

void verify(){
    byte error, address;
  int devices = 0;

  Serial.println("Scanning...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println();
      devices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (devices == 0) {
    Serial.println("No I2C devices found\n");
  } else {
    Serial.println("Scan complete\n");
  }

  delay(scantime);  // Wait for 5 seconds before scanning again
}

void initializeEEPROM() {
  // Write default value for temp1 to EEPROM
  for (int i = EEPROM_TEMP1_START; i < EEPROM_TEMP1_START + 512; i++) {
    EEPROM.write(i, DEFAULT_TEMP1);
  }

  // Write default value for distance to EEPROM
  for (int i = EEPROM_DISTANCE_START; i < EEPROM_DISTANCE_START + 512; i += 2) {
    EEPROM.write(i, DEFAULT_DISTANCE & 0xFF);           // Low byte
    EEPROM.write(i + 1, (DEFAULT_DISTANCE >> 8) & 0xFF); // High byte
  }

  Serial.println("EEPROM initialized with default values.");
}