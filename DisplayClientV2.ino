
// H revision sketch
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------
// ----------------------------------------------------- PLEASE USE SETUP ASSISTANT AVAILABLE IN SUB FOLDER !!!! -------------------------------------------

//#define INCLUDE_TM1638 //{"Name":"INCLUDE_TM1638","Type":"autodefine","Condition":"[TM1638_ENABLEDMODULES]>0"}

//#define INCLUDE_WS2801 //{"Name":"INCLUDE_WS2801","Type":"autodefine","Condition":"[WS2801_RGBLEDCOUNT]>0"}

//#define INCLUDE_WS2812B //{"Name":"INCLUDE_WS2812B","Type":"autodefine","Condition":"[WS2812B_RGBLEDCOUNT]>0"}

//#define INCLUDE_WS2812B_MATRIX //{"Name":"INCLUDE_WS2812B_MATRIX","Type":"autodefine","Condition":"[WS2812B_MATRIX_ENABLED]>0"}

//#define INCLUDE_LEDBACKPACK //{"Name":"INCLUDE_LEDBACKPACK","Type":"autodefine","Condition":"[ENABLE_ADA_HT16K33_7SEGMENTS]>0 || [ENABLE_ADA_HT16K33_Matrix]>0"}

//#define INCLUDE_TM1637 //{"Name":"INCLUDE_TM1637","Type":"autodefine","Condition":"[TM1637_ENABLEDMODULES]>0"}

//#define INCLUDE_I2CLCD //{"Name":"INCLUDE_I2CLCD","Type":"autodefine","Condition":"[I2CLCD_enabled]>0"}

//#define INCLUDE_NOKIALCD //{"Name":"INCLUDE_NOKIALCD","Type":"autodefine","Condition":"[ENABLED_NOKIALCD]>0"}

//#define INCLUDE_OLED //{"Name":"INCLUDE_OLED","Type":"autodefine","Condition":"[ENABLED_OLEDLCD]>0"}

//#define INCLUDE_MAX7221MATRIX //{"Name":"INCLUDE_MAX7221MATRIX","Type":"autodefine","Condition":"[MAX7221_MATRIX_ENABLED]>0"}

//#define INCLUDE_74HC595_GEAR_DISPLAY //{"Name":"INCLUDE_74HC595_GEAR_DISPLAY","Type":"autodefine","Condition":"[ENABLE_74HC595_GEAR_DISPLAY]>0"}

//#define INCLUDE_MAX7221_MODULES //{"Name":"INCLUDE_MAX7221_MODULES","Type":"autodefine","Condition":"[MAX7221_ENABLEDMODULES]>0"}

//#define INCLUDE_6c595_GEAR_DISPLAY  //{"Name":"INCLUDE_6c595_GEAR_DISPLAY ","Type":"autodefine","Condition":"[ENABLE_6C595_GEAR_DISPLAY]>0"}

#define INCLUDE_TACHOMETER  //{"Name":"INCLUDE_TACHOMETER ","Type":"autodefine","Condition":"[ENABLE_TACHOMETER]>0"}

//#define INCLUDE_BOOSTGAUGE  //{"Name":"INCLUDE_BOOSTGAUGE ","Type":"autodefine","Condition":"[ENABLE_BOOSTGAUGE]>0"}

//#define INCLUDE_SHAKEITADASHIELD  //{"Name":"INCLUDE_SHAKEITADASHIELD ","Type":"autodefine","Condition":"[ADAMOTORS_SHIELDSCOUNT]>0"}

//#define INCLUDE_SHAKEITDKSHIELD  //{"Name":"INCLUDE_SHAKEITDKSHIELD ","Type":"autodefine","Condition":"[DKMOTOR_SHIELDSCOUNT]>0"}

//#define INCLUDE_SHAKEITL298N  //{"Name":"INCLUDE_SHAKEITL298N ","Type":"autodefine","Condition":"[L98NMOTORS_ENABLED]>0"}

//#define INCLUDE_GAMEPAD  //{"Name":"INCLUDE_GAMEPAD ","Type":"autodefine","Condition":"[ENABLE_MICRO_GAMEPAD]>0"}


#ifdef INCLUDE_TACHOMETER
#include <Tone.h>
#endif
#include <avr/pgmspace.h>
#include <EEPROM.h>

#include <SPI.h>
#include "Arduino.h"
#include <avr/pgmspace.h>

#include <Wire.h>
#include "LedControl.h"
#include "Adafruit_GFX.h"
#include "FlowSerialRead.h"

//#ifdef INCLUDE_TM1638
#include <TM1638.h>
//#endif

#if defined(INCLUDE_WS2812B) || defined(INCLUDE_WS2812B_MATRIX)
#include <Adafruit_NeoPixel.h>
#endif

#ifdef INCLUDE_WS2801
#include <Adafruit_WS2801.h>
#endif

//#ifdef INCLUDE_TM1637
#include "TM1637.h"
//#endif

#ifdef INCLUDE_I2CLCD
#include <LiquidCrystal_I2C.h>
#endif

#ifdef INCLUDE_LEDBACKPACK
#include "Adafruit_LEDBackpack.h"
#endif

#ifdef INCLUDE_NOKIALCD
#include <Adafruit_PCD8544.h>
#endif
#if defined(INCLUDE_NOKIALCD) || defined(INCLUDE_OLED)
#include "ACHubCustomFonts/Open24DisplaySt12pt7b.h"
#define CUSTOM_LCD_FONT_1 Open24DisplaySt12pt7b
#include "ACHubCustomFonts/Open24DisplaySt18pt7b.h"
#define CUSTOM_LCD_FONT_2 Open24DisplaySt18pt7b
#endif

#ifdef INCLUDE_OLED
#include <Adafruit_SSD1306.h>
#endif // INCLUDE_OLED

#ifdef INCLUDE_SHAKEITADASHIELD
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#endif

#ifdef INCLUDE_SHAKEITDKSHIELD
#include <AFMotor.h>
#endif

#ifdef INCLUDE_GAMEPAD
#include <Joystick.h>

//initialize an Joystick with 34 buttons;
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,
	JOYSTICK_TYPE_JOYSTICK, 128, 0,
	false, false, false, false, false, false,
	false, false, false, false, false);

#endif

#define MESSAGE_HEADER 0x03

// ----------------------------------------------------- HW SETTINGS, PLEASE REVIEW ALL -------------------------------------------
String DEVICE_NAME = String("E36 Cluster"); //{"Group":"General","Name":"DEVICE_NAME","Title":"Device name","DefaultValue":"SimHub Dash","Type":"string","Template":"String DEVICE_NAME = String(\"{0}\");"}

int ENABLE_MICRO_GAMEPAD = 0; //{"Group":"GAMEPAD","Name":"ENABLE_MICRO_GAMEPAD","Title":"Enable arduino micro gamepad output for all the activated buttons\r\nSet to 0 to disable","DefaultValue":"0","Type":"integer","Template":"int ENABLE_MICRO_GAMEPAD = {0};"}

// -------------------------------------------------------------------------------------------------------
// TM1638 Modules ----------------------------------------------------------------------------------------
// http://www.dx.com/p/jy-mcu-8x-green-light-digital-tube-8x-key-8x-double-color-led-module-104329
// https://www.fasttech.com/products/0/10006503/1497600-jy-mcu-8x-digital-tube-red-led-module
// -------------------------------------------------------------------------------------------------------

// Number of Connected TM1638/1639 modules
// 0 disabled, > 0 enabled
int TM1638_ENABLEDMODULES = 0; //{"Group":"TM1638","Name":"TM1638_ENABLEDMODULES","Title":"TM1638 modules connected\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int TM1638_ENABLEDMODULES = {0};"}

#ifdef INCLUDE_TM1638
// 0 disabled, 1 enabled
int TM1638_SWAPLEDCOLORS = 0; //{"Group":"TM1638","Name":"TM1638_SWAPLEDCOLORS","Title":"Reverse Red and green colors \r\n0 = No, 1 = Yes","DefaultValue":"0","Type":"boolean","Template":"int TM1638_SWAPLEDCOLORS = {0};","Condition":"TM1638_ENABLEDMODULES > 0"}
// TM1638 Modules common pins
#define TM1638_DIO 8 //{"Group":"TM1638","Name":"TM1638_DIO","Title":"Common data (DIO) digital pin number","DefaultValue":"8","Type":"integer","Template":"#define TM1638_DIO {0}","Condition":"TM1638_ENABLEDMODULES > 0"}
#define TM1638_CLK 7 //{"Group":"TM1638","Name":"TM1638_CLK","Title":"Common clock (CLK) digital pin number","DefaultValue":"7","Type":"integer","Template":"#define TM1638_CLK {0}","Condition":"TM1638_ENABLEDMODULES > 0"}
// TM1638 1st module strobe pin
#define TM1638_STB1 9 //{"Group":"TM1638","Name":"TM1638_STB1","Title":"1st module strobe (STB0) digital pin number","DefaultValue":"9","Type":"integer","Template":"#define TM1638_STB1 {0}","Condition":"TM1638_ENABLEDMODULES > 0"}
// TM1638 2nd screen strobe pin
#define TM1638_STB2 10 //{"Group":"TM1638","Name":"TM1638_STB2","Title":"2d module strobe (STB1) digital pin number","DefaultValue":"10","Type":"integer","Template":"#define TM1638_STB2 {0}","Condition":"TM1638_ENABLEDMODULES > 1"}
// TM1638 3nd screen strobe pin
#define TM1638_STB3 11 //{"Group":"TM1638","Name":"TM1638_STB3","Title":"3rd module strobe (STB2) digital pin number","DefaultValue":"11","Type":"integer","Template":"#define TM1638_STB3 {0}","Condition":"TM1638_ENABLEDMODULES > 2"}
// TM1638 4rd screen strobe pin
#define TM1638_STB4 12 //{"Group":"TM1638","Name":"TM1638_STB4","Title":"4th module strobe (STB3) digital pin number","DefaultValue":"12","Type":"integer","Template":"#define TM1638_STB4 {0}","Condition":"TM1638_ENABLEDMODULES > 3"}
// TM1638 5th screen strobe pin
#define TM1638_STB5 0 //{"Group":"TM1638","Name":"TM1638_STB5","Title":"5th module strobe (STB4) digital pin number","DefaultValue":"0","Type":"integer","Template":"#define TM1638_STB5 {0}","Condition":"TM1638_ENABLEDMODULES > 4"}
// TM1638 6th screen strobe pin
#define TM1638_STB6 0 //{"Group":"TM1638","Name":"TM1638_STB6","Title":"6th module strobe (STB5) digital pin number","DefaultValue":"0","Type":"integer","Template":"#define TM1638_STB6 {0}","Condition":"TM1638_ENABLEDMODULES > 5"}
#endif

// -------------------------------------------------------------------------------------------------------
// TM1637 Modules ----------------------------------------------------------------------------------------
// http://www.dx.com/p/0-36-led-4-digit-display-module-for-arduino-black-blue-works-with-official-arduino-boards-254978
// -------------------------------------------------------------------------------------------------------

// Number of Connected TM1637 modules
// 0 disabled, > 0 enabled
int TM1637_ENABLEDMODULES = 0; //{"Group":"TM1637","Name":"TM1637_ENABLEDMODULES","Title":"TM1637 modules connected\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int TM1637_ENABLEDMODULES = {0};"}
#ifdef INCLUDE_TM1637
#define TM1637_DIO1 4 //{"Group":"TM1637","Name":"TM1637_DIO1","Title":"1st TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO1 {0}","Condition":"TM1637_ENABLEDMODULES >=1"}
#define TM1637_CLK1 3 //{"Group":"TM1637","Name":"TM1637_CLK1","Title":"1st TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK1 {0}","Condition":"TM1637_ENABLEDMODULES >=1"}

#define TM1637_DIO2 4 //{"Group":"TM1637","Name":"TM1637_DIO2","Title":"2nd TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO2 {0}","Condition":"TM1637_ENABLEDMODULES >=2"}
#define TM1637_CLK2 3 //{"Group":"TM1637","Name":"TM1637_CLK2","Title":"2nd TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK2 {0}","Condition":"TM1637_ENABLEDMODULES >=2"}

#define TM1637_DIO3 4 //{"Group":"TM1637","Name":"TM1637_DIO3","Title":"3rd TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO3 {0}","Condition":"TM1637_ENABLEDMODULES >=3"}
#define TM1637_CLK3 3 //{"Group":"TM1637","Name":"TM1637_CLK3","Title":"3rd TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK3 {0}","Condition":"TM1637_ENABLEDMODULES >=3"}

#define TM1637_DIO4 4 //{"Group":"TM1637","Name":"TM1637_DIO4","Title":"4th TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO4 {0}","Condition":"TM1637_ENABLEDMODULES >=4"}
#define TM1637_CLK4 3 //{"Group":"TM1637","Name":"TM1637_CLK4","Title":"4th TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK4 {0}","Condition":"TM1637_ENABLEDMODULES >=4"}

#define TM1637_DIO5 4 //{"Group":"TM1637","Name":"TM1637_DIO5","Title":"5th TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO5 {0}","Condition":"TM1637_ENABLEDMODULES >=5"}
#define TM1637_CLK5 3 //{"Group":"TM1637","Name":"TM1637_CLK5","Title":"5th TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK5 {0}","Condition":"TM1637_ENABLEDMODULES >=5"}

#define TM1637_DIO6 4 //{"Group":"TM1637","Name":"TM1637_DIO6","Title":"6th TM1637 DIO digital pin number","DefaultValue":"4","Type":"integer","Template":"#define TM1637_DIO6 {0}","Condition":"TM1637_ENABLEDMODULES >=6"}
#define TM1637_CLK6 3 //{"Group":"TM1637","Name":"TM1637_CLK6","Title":"6th TM1637 CLK digital pin number","DefaultValue":"3","Type":"integer","Template":"#define TM1637_CLK6 {0}","Condition":"TM1637_ENABLEDMODULES >=6"}
#endif

// -------------------------------------------------------------------------------------------------------
// MAX7219 / MAX7221 7 Segment modules -----------------------------------------------------------------------------
// http://www.dx.com/p/max7219-led-dot-matrix-digital-led-display-tube-module-cascade-391256
// -------------------------------------------------------------------------------------------------------

// 0 disabled, > 0 enabled
int MAX7221_ENABLEDMODULES = 0; //{"Group":"MAX7221","Name":"MAX7221_ENABLEDMODULES","Title":"MAX7219 / MAX7221 7 Segment modules connected \r\nSet to 0 if none\r\nMultiple modules can be cascaded connected module output to next module input","DefaultValue":"0","Type":"integer","Template":"int MAX7221_ENABLEDMODULES = {0};"}

#ifdef INCLUDE_MAX7221_MODULES
// DATA IN - pin of the first MAX7221
#define MAX7221_DATA 3 //{"Group":"MAX7221","Name":"MAX7221_DATA","Title":"DATA (DIN) digital pin number","DefaultValue":"3","Type":"integer","Template":"#define MAX7221_DATA {0}","Condition":"MAX7221_ENABLEDMODULES > 0"}
// CLK - pin of the first MAX7221
#define MAX7221_CLK 5 //{"Group":"MAX7221","Name":"MAX7221_CLK","Title":"CLOCK (CLK) digital pin number","DefaultValue":"5","Type":"integer","Template":"#define MAX7221_CLK {0}","Condition":"MAX7221_ENABLEDMODULES > 0"}
// LOAD(/ CS) - pin of the first MAX7221
#define MAX7221_LOAD 4 //{"Group":"MAX7221","Name":"MAX7221_LOAD","Title":"LOAD (LD) digital pin number","DefaultValue":"4","Type":"integer","Template":"#define MAX7221_LOAD {0}","Condition":"MAX7221_ENABLEDMODULES > 0"}
LedControl MAX7221 = LedControl(MAX7221_DATA, MAX7221_CLK, MAX7221_LOAD, MAX7221_ENABLEDMODULES);

#endif // INCLUDE_MAX7221_MODULES
// -------------------------------------------------------------------------------------------------------
// MAX7219 / MAX7221 Led Matrix module -----------------------------------------------------------------------------
// http://www.dx.com/p/max7219-dot-matrix-module-w-5-dupont-lines-184854
// -------------------------------------------------------------------------------------------------------

int MAX7221_MATRIX_ENABLED = 0; //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_ENABLED","Title":"MAX7221 led matrix enabled \r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"integer","Template":"int MAX7221_MATRIX_ENABLED = {0};"}
#ifdef INCLUDE_MAX7221MATRIX
// 0 disabled, 1 enabled
int MAX7221_MATRIX_LUMINOSITY = 15;
// DATA IN - pin of the first MAX7221
#define MAX7221_MATRIX_DATA 3 //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_DATA","Title":"DATA (DIN) digital pin number","DefaultValue":"3","Type":"integer","Template":"#define MAX7221_MATRIX_DATA {0}","Condition":"MAX7221_MATRIX_ENABLED>0"}
// CLK - pin of the first MAX7212
#define MAX7221_MATRIX_CLK 5 //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_CLK","Title":"CLOCK (CLK) digital pin number","DefaultValue":"5","Type":"integer","Template":"#define MAX7221_MATRIX_CLK {0}","Condition":"MAX7221_MATRIX_ENABLED>0"}
// LOAD(/ CS) - pin of the first MAX7221
#define MAX7221_MATRIX_LOAD 4 //{"Group":"MAX7221_MATRIX","Name":"MAX7221_MATRIX_LOAD","Title":"LOAD (LD) digital pin number","DefaultValue":"4","Type":"integer","Template":"#define MAX7221_MATRIX_LOAD {0}","Condition":"MAX7221_MATRIX_ENABLED>0"}
LedControl MAX7221_MATRIX = LedControl(MAX7221_MATRIX_DATA, MAX7221_MATRIX_CLK, MAX7221_MATRIX_LOAD, MAX7221_MATRIX_ENABLED);
#endif // INCLUDE_MAX7221MATRIX

// -------------------------------------------------------------------------------------------------------
// WS2812b RGBLEDS ---------------------------------------------------------------------------------------
// http://www.dx.com/p/8-bit-ws2812-5050-rgb-led-development-board-w-built-in-full-color-drive-387667
// -------------------------------------------------------------------------------------------------------

// WS2812b chained RGBLEDS count
// 0 disabled, > 0 enabled
int WS2812B_RGBLEDCOUNT = 0; //{"Group":"WS2812B_RGBLED","Name":"WS2812B_RGBLEDCOUNT","Title":"WS2812B RGB leds count\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int WS2812B_RGBLEDCOUNT = {0};"}

#ifdef INCLUDE_WS2812B
// 0 leds will be used from left to right, 1 leds will be used from right to left
int WS2812B_RIGHTTOLEFT = 0; //{"Group":"WS2812B_RGBLED","Name":"WS2812B_RIGHTTOLEFT","Title":"Reverse led order \r\n0 = No, 1 = Yes","DefaultValue":"0","Type":"boolean","Template":"int WS2812B_RIGHTTOLEFT = {0};","Condition":"WS2812B_RGBLEDCOUNT>0"}
// WS2812b chained RGBLEDS pins
#define WS2812B_DATAPIN 6 //{"Group":"WS2812B_RGBLED","Name":"WS2812B_DATAPIN","Title":"Data (DIN) digital pin number","DefaultValue":"6","Type":"boolean","Template":"#define WS2812B_DATAPIN {0}","Condition":"WS2812B_RGBLEDCOUNT>0"}
Adafruit_NeoPixel WS2812B_strip = Adafruit_NeoPixel(WS2812B_RGBLEDCOUNT, WS2812B_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

// -------------------------------------------------------------------------------------------------------
// WS2812b MATRIX ---------------------------------------------------------------------------------------
// http://www.dx.com/p/8-bit-ws2812-5050-rgb-led-development-board-w-built-in-full-color-drive-387667
// -------------------------------------------------------------------------------------------------------

// WS2812b chained RGBLEDS count
// 0 disabled, > 0 enabled
int WS2812B_MATRIX_ENABLED = 0; //{"Group":"WS2812B_MATRIX","Name":"WS2812B_MATRIX_ENABLED","Title":"Support Coming Soon !! -- WS2812B 8x8 Matrix enabled\r\nSet to 1 to enable","DefaultValue":"0","Type":"integer","Template":"int WS2812B_MATRIX_ENABLED = {0};"}

#ifdef INCLUDE_WS2812B_MATRIX

#define WS2812B_MATRIX_DATAPIN 6 //{"Group":"WS2812B_MATRIX","Name":"WS2812B_MATRIX_DATAPIN","Title":"Data (DIN) digital pin number","DefaultValue":"6","Type":"boolean","Template":"#define WS2812B_MATRIX_DATAPIN {0}","Condition":"WS2812B_MATRIX_ENABLED>0"}
Adafruit_NeoPixel WS2812B_matrix = Adafruit_NeoPixel(64, WS2812B_MATRIX_DATAPIN, NEO_GRB + NEO_KHZ800);
#endif

// -------------------------------------------------------------------------------------------------------
// WS2801 RGBLEDS ----------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------

// 0 disabled, > 0 enabled
int WS2801_RGBLEDCOUNT = 0; //{"Group":"WS2801_RGBLED","Name":"WS2801_RGBLEDCOUNT","Title":"WS2801 RGB leds count\r\nSet to 0 if none","DefaultValue":"0","Type":"integer","Template":"int WS2801_RGBLEDCOUNT = {0};"}

#ifdef INCLUDE_WS2801
// 0 leds will be used from left to right, 1 leds will be used from right to left
int WS2801_RIGHTTOLEFT = 0; //{"Group":"WS2801_RGBLED","Name":"WS2801_RIGHTTOLEFT","Title":"WS2801 right to left\r\nSet to 0 for left to right, 1 for right to left","DefaultValue":"0","Type":"integer","Template":"int WS2801_RIGHTTOLEFT = {0};","Condition":"WS2801_RGBLEDCOUNT>0"}
#define WS2801_DATAPIN 5 //{"Group":"WS2801_RGBLED","Name":"WS2801_DATAPIN","Title":"Data (DIN) digital pin number","DefaultValue":"5","Type":"integer","Template":"#define WS2801_DATAPIN {0}","Condition":"WS2801_RGBLEDCOUNT>0"}
#define WS2801_CLOCKPIN 6 //{"Group":"WS2801_RGBLED","Name":"WS2801_CLOCKPIN","Title":"Clock (DIN) digital pin number","DefaultValue":"6","Type":"integer","Template":"#define WS2801_CLOCKPIN {0}","Condition":"WS2801_RGBLEDCOUNT>0"}
Adafruit_WS2801 WS2801_strip = Adafruit_WS2801(WS2801_RGBLEDCOUNT, WS2801_DATAPIN, WS2801_CLOCKPIN);

#endif

// -------------------------------------------------------------------------------------------------------
// I2C LiquidCristal - WIP no finished
// http://www.dx.com/p/arduino-iic-i2c-serial-3-2-lcd-2004-module-display-138611#.Vb0QtW7tlBd
// Board				I2C / TWI pins
// Uno, Ethernet, Nano	A4(SDA), A5(SCL)
// Mega2560				20 (SDA), 21 (SCL)
// Leonardo				2 (SDA), 3 (SCL)
// Due					20 (SDA), 21 (SCL), SDA1, SCL1
// -------------------------------------------------------------------------------------------------------

int I2CLCD_enabled = 0; //{"Group":"I2C LCD","Name":"I2CLCD_enabled","Title":"I2C LCD (2004) enabled\r\n0 = disabled, 1 = enabled\r\nUno, Ethernet, Nano : A4(SDA), A5(SCL)\r\nMega2560 : 20 (SDA), 21 (SCL)\r\nLeonardo : 2 (SDA), 3 (SCL)\r\nDue : 20 (SDA), 21 (SCL), SDA1, SCL1","DefaultValue":"0","Type":"integer","Template":"int I2CLCD_enabled = {0};"}
#ifdef INCLUDE_I2CLCD
int I2CLCD_width = 20;
int I2CLCD_height = 4;
byte I2CLCD_address = 0x3f; //{"Group":"I2C LCD","Name":"I2CLCD_address","Title":"I2C address","DefaultValue":"0x3f","Type":"hex","Template":"byte I2CLCD_address = {0};","Condition":"I2CLCD_enabled>0"}
LiquidCrystal_I2C I2CLCD(I2CLCD_address, I2CLCD_width, I2CLCD_height);
#endif

// --------------------------------------------------------------------------------------------------------
// 74HC595 Shift register, one 7seg module for gear indicator ---------------------------------------------
// DIY : http://lucidtronix.com/tutorials/2
// --------------------------------------------------------------------------------------------------------

// 0 disabled, 1 enabled
int ENABLE_74HC595_GEAR_DISPLAY = 0; //{"Group":"74HC595 GEAR DISPLAY","Name":"ENABLE_74HC595_GEAR_DISPLAY","Title":"74HC595 gear display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_74HC595_GEAR_DISPLAY = {0};"}

#ifdef INCLUDE_74HC595_GEAR_DISPLAY
// Reverse led state
int RS_74HC595_INVERT = 0;
#define RS_74HC595_DATAPIN 2 //{"Group":"74HC595 GEAR DISPLAY","Name":"RS_74HC595_DATAPIN","Title":"DATA digital pin number","DefaultValue":"2","Type":"hex","Template":"#define RS_74HC595_DATAPIN {0}","Condition":"ENABLE_74HC595_GEAR_DISPLAY >0"}
#define RS_74HC595_LATCHPIN 3 //{"Group":"74HC595 GEAR DISPLAY","Name":"RS_74HC595_LATCHPIN","Title":"LATCH digital pin number","DefaultValue":"3","Type":"hex","Template":"#define RS_74HC595_LATCHPIN {0}","Condition":"ENABLE_74HC595_GEAR_DISPLAY > 0"}
#define RS_74HC595_CLOCKPIN 4 //{"Group":"74HC595 GEAR DISPLAY","Name":"RS_74HC595_CLOCKPIN","Title":"CLOCK digital pin number","DefaultValue":"4","Type":"hex","Template":"#define RS_74HC595_CLOCKPIN {0}","Condition":"ENABLE_74HC595_GEAR_DISPLAY > 0"}
// RS_74HC595 DIGITS
// 0,1,2 ....
byte RS_74HC595_dec_digits[] = { 0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110, 0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110 };
// Empty
byte RS_74HC595_ClearDigit = 0b00000000;
// R
byte RS_74HC595_ReverseDigit = 0b10001100;
// N
byte RS_74HC595_NeutralDigit = 0b11101100;
#endif // INCLUDE_74HC595_GEAR_DISPLAY

// --------------------------------------------------------------------------------------------------------
// 6c595 Shift register, one 7seg module for gear indicator ---------------------------------------------
// DIY : https://www.xsimulator.net/community/threads/12cm-12v-7segments-gear-indicator-with-gamedash.5747/
// --------------------------------------------------------------------------------------------------------
#ifdef INCLUDE_6c595_GEAR_DISPLAY
int ENABLE_6c595_GEAR_DISPLAY = 0; //{"Group":"6c595 GEAR DISPLAY","Name":"ENABLE_6C595_GEAR_DISPLAY","Title":"6C595 gear display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_6c595_GEAR_DISPLAY = {0};"}
#define RS_6c595_DATAPIN 11 //{"Group":"6c595 GEAR DISPLAY","Name":"RS_6c595_DATAPIN","Title":"DATA digital pin number, can't be changed !","DefaultValue":"11","Type":"hex","Template":"#define RS_6c595_DATAPIN {0}","Condition":"ENABLE_6C595_GEAR_DISPLAY>0"}
#define RS_6c595_LATCHPIN 13 //{"Group":"6c595 GEAR DISPLAY","Name":"RS_6c595_LATCHPIN","Title":"LATCH digital pin number, can't be changed !","DefaultValue":"13","Type":"hex","Template":"#define RS_6c595_LATCHPIN {0}","Condition":"ENABLE_6C595_GEAR_DISPLAY>0"}
#define RS_6c595_SLAVEPIN 10 //{"Group":"6c595 GEAR DISPLAY","Name":"RS_6c595_SLAVEPIN","Title":"SLAVE digital pin number","DefaultValue":"10","Type":"hex","Template":"#define RS_6c595_SLAVEPIN {0}","Condition":"ENABLE_6C595_GEAR_DISPLAY>0"}

byte g_6c595fontArray[] = {
	// dp-a-b-c-d-e-f-g
	0b10100001, // 0
	0b00101000, // 1
	0b11001101, // 2
	0b01101101, // 3
	0b00101011, // 4
	0b01100111, // 5
	0b11100111, // 6
	0b00101100, // 7
	0b00000000, // OFF empty
	0b10000001, // REVERSE SPEED
};
byte g_6c595LEDarray; //computed order that will be sent to the LED display
#endif

// --------------------------------------------------------------------------------------------------------
// Adafruit 4x7segment with HT16K33 I2C Backpack
// These displays use I2C to communicate, 2 pins are required to interface.
// There are multiple selectable I2C addresses.
// For backpacks with 2 Address Select addresses : 0x70, 0x71, 0x72 or 0x73.
// For backpacks with 3 Address Select addresses : 0x70 thru 0x77
// --------------------------------------------------------------------------------------------------------
// 0 disabled, 1 enabled
int ENABLE_ADA_HT16K33_7SEGMENTS = 0; //{"Group":"HT16K33_7SEGMENTS","Name":"ENABLE_ADA_HT16K33_7SEGMENTS","Title":"Adafruit HT16K33 7 segments display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_ADA_HT16K33_7SEGMENTS = {0};"}
#ifdef INCLUDE_LEDBACKPACK
// I2C Adress
byte ADA_HT16K33_7SEGMENTS_I2CADDRESS = 0x70;
Adafruit_7segment ADA_HT16K33_7SEGMENTS = Adafruit_7segment();
#endif

// --------------------------------------------------------------------------------------------------------
// Adafruit 8x8 bi color with HT16K33 I2C Backpack
// These displays use I2C to communicate, 2 pins are required to interface.
// There are multiple selectable I2C addresses.
// For backpacks with 2 Address Select addresses : 0x70, 0x71, 0x72 or 0x73.
// For backpacks with 3 Address Select addresses : 0x70 thru 0x77
// --------------------------------------------------------------------------------------------------------
// 0 disabled, 1 enabled
int ENABLE_ADA_HT16K33_Matrix = 0; //{"Group":"HT16K33_Matrix","Name":"ENABLE_ADA_HT16K33_Matrix","Title":"Adafruit HT16K33 matrix display enabled\r\n0 = disabled, 1 = enabled","DefaultValue":"0","Type":"hex","Template":"int ENABLE_ADA_HT16K33_Matrix = {0};"}
// I2C Adress
#ifdef INCLUDE_LEDBACKPACK
byte ADA_HT16K33_MATRIX_I2CADDRESS = 0x71;
Adafruit_BicolorMatrix ADA_HT16K33_MATRIX = Adafruit_BicolorMatrix();
byte ADA_HT16K33_Matrix_luminosity = 0;
#endif

// ------------------------ TACHOMETER ----------------------------------------------------------------------
// https://github.com/zegreatclan/AssettoCorsaTools/wiki/Arduino-After-Market-Tach-support
// ----------------------------------------------------------------------------------------------------------

#ifdef INCLUDE_TACHOMETER
int ENABLE_TACHOMETER = 1; //{"Group":"TACHOMETER","Name":"ENABLE_TACHOMETER","Title":"After market tachometer enabled\r\n0 = disabled, 1 = enabled\r\nsee wiki for wiring instructions","DefaultValue":"0","Type":"hex","Template":"int ENABLE_TACHOMETER = {0};"}
int pinTacho = 2; //{"Group":"TACHOMETER","Name":"TACHOMETER_PIN","Title":"Tachometer pin","DefaultValue":"9","Type":"hex","Template":"int pinTacho = {0};","Condition":"ENABLE_TACHOMETER > 0 "}
Tone rpmTone;
#endif

#ifdef INCLUDE_BOOSTGAUGE
int ENABLE_BOOSTGAUGE = 0; //{"Group":"BOOST GAUGE","Name":"ENABLE_BOOSTGAUGE","Title":"After market boost gauge enabled\r\n0 = disabled, 1 = enabled\r\nsee wiki for wiring instructions","DefaultValue":"0","Type":"hex","Template":"int ENABLE_BOOSTGAUGE = {0};"}
int pinBoost = 5; //{"Group":"BOOST GAUGE","Name":"BOOST_PIN","Title":"Boost pwm pin","DefaultValue":"5","Type":"hex","Template":"int pinBoost = {0};","Condition":"ENABLE_BOOSTGAUGE >0"}
#endif

// ----------------------- ADDITIONAL BUTTONS ---------------------------------------------------------------
// https://www.arduino.cc/en/Tutorial/InputPullupSerial
// ----------------------------------------------------------------------------------------------------------
int ENABLED_BUTTONS_COUNT = 0; //{"Group":"ADDITIONAL BUTTONS","Name":"ENABLED_BUTTONS_COUNT","Title":"Additional buttons (directly connected to the arduino) buttons count\r\n0 = disabled, >0  = enabled","DefaultValue":"0","Type":"integer","Template":"int ENABLED_BUTTONS_COUNT = {0};"}
int BUTTON_PIN_1 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_1","Title":"1'st Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_1 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=1"}
int BUTTON_PIN_2 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_2","Title":"2'nd Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_2 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=2"}
int BUTTON_PIN_3 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_3","Title":"3'rd Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_3 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=3"}
int BUTTON_PIN_4 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_4","Title":"4'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_4 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=4"}
int BUTTON_PIN_5 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_5","Title":"5'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_5 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=5"}
int BUTTON_PIN_6 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_6","Title":"6'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_6 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=6"}
int BUTTON_PIN_7 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_7","Title":"7'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_7 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=7"}
int BUTTON_PIN_8 = 3; //{"Group":"ADDITIONAL BUTTONS","Name":"BUTTON_PIN_8","Title":"8'th Additional button digital pin","DefaultValue":"3","Type":"integer","Template":"int BUTTON_PIN_8 = {0};","Condition":"ENABLED_BUTTONS_COUNT>=8"}
int BUTTON_PINS[] = { BUTTON_PIN_1, BUTTON_PIN_2, BUTTON_PIN_3, BUTTON_PIN_4, BUTTON_PIN_5, BUTTON_PIN_6, BUTTON_PIN_7, BUTTON_PIN_8 };

// -------------------- NOKIA GLCD -------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------------------------------------
int ENABLED_NOKIALCD = 0; //{"Group":"NOKIA_GLCD","Name":"ENABLED_NOKIALCD","Title":"Number of Nokia GLCD connected (up to 2)\r\n0 = disabled, >0  = enabled","DefaultValue":"0","Type":"integer","Template":"int ENABLED_NOKIALCD = {0};"}
//#define ENABLE_SECONDARY_NOKIALCD //{"Name":"ENABLE_SECONDARY_NOKIALCD","Type":"autodefine","Condition":"[ENABLED_NOKIALCD]>1"}

#ifdef INCLUDE_NOKIALCD
// Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS or SCE, RST);
Adafruit_PCD8544 glcd1 = Adafruit_PCD8544(A0, A1, A2, A4, A3);
#ifdef ENABLE_SECONDARY_NOKIALCD
Adafruit_PCD8544 glcd2 = Adafruit_PCD8544(3, 4, 5, 7, 6);
Adafruit_PCD8544 * nokiaLCDs[] = { &glcd1, &glcd2 };
#else
Adafruit_PCD8544 * nokiaLCDs[] = { &glcd1 };
#endif
#endif

int ENABLED_OLEDLCD = 0; //{"Group":"OLED_LCD","Name":"ENABLED_OLEDLCD","Title":"Number of OLED LCD connected (up to 2)\r\n0 = disabled, >0  = enabled","DefaultValue":"0","Type":"integer","Template":"int ENABLED_OLEDLCD = {0};"}
//#define ENABLE_SECONDARY_OLEDLCD //{"Name":"ENABLE_SECONDARY_OLEDLCD","Type":"autodefine","Condition":"[ENABLED_OLEDLCD]>1"}
#ifdef INCLUDE_OLED
#define OLED_RESET 4
Adafruit_SSD1306 glcd1(OLED_RESET);
#ifdef ENABLE_SECONDARY_OLEDLCD
Adafruit_SSD1306 glcd2(OLED_RESET);
Adafruit_SSD1306 * nokiaLCDs[] = { &glcd1, &glcd2 };
#else
Adafruit_SSD1306 * nokiaLCDs[] = { &glcd1 };
#endif
#endif

int ADAMOTORS_SHIELDSCOUNT = 0; //{"Group":"SHAKEIT ADAFRUIT MOTORSHIELD V2","Name":"ADAMOTORS_SHIELDSCOUNT","Title":"Number of adadruit shields connected (up to 3)\r\n0 = disabled, >0  = enabled, ","DefaultValue":"0","Type":"integer","Template":"int ADAMOTORS_SHIELDSCOUNT = {0};"}

#ifdef INCLUDE_SHAKEITADASHIELD

Adafruit_MotorShield Shield1(0x60); // Default address, no jumpers
Adafruit_MotorShield Shield2(0x61); // Rightmost jumper closed
Adafruit_MotorShield Shield3(0x62); // Rightmost jumper closed

Adafruit_DCMotor *motor01 = Shield1.getMotor(1);
Adafruit_DCMotor *motor02 = Shield1.getMotor(2);
Adafruit_DCMotor *motor03 = Shield1.getMotor(3);
Adafruit_DCMotor *motor04 = Shield1.getMotor(4);

Adafruit_DCMotor *motor05 = Shield2.getMotor(1);
Adafruit_DCMotor *motor06 = Shield2.getMotor(2);
Adafruit_DCMotor *motor07 = Shield2.getMotor(3);
Adafruit_DCMotor *motor08 = Shield2.getMotor(4);

Adafruit_DCMotor *motor09 = Shield3.getMotor(1);
Adafruit_DCMotor *motor10 = Shield3.getMotor(2);
Adafruit_DCMotor *motor11 = Shield3.getMotor(3);
Adafruit_DCMotor *motor12 = Shield3.getMotor(4);

Adafruit_DCMotor * AdaMotors[] = { motor01, motor02, motor03, motor04, motor05, motor06, motor07, motor08, motor09, motor10, motor11, motor12 };

#endif // INCLUDE_SHAKEITADASHIELD

int DKMOTOR_SHIELDSCOUNT = 0; //{"Group":"SHAKEIT DK Motor shield","Name":"DKMOTOR_SHIELDSCOUNT","Title":"Number of DK shields connected (up to 1)\r\n0 = disabled, 1  = enabled, ","DefaultValue":"0","Type":"integer","Template":"int DKMOTOR_SHIELDSCOUNT = {0};"}

#ifdef INCLUDE_SHAKEITDKSHIELD

AF_DCMotor dkmotor1(1, MOTOR12_64KHZ);
AF_DCMotor dkmotor2(2, MOTOR12_64KHZ);
AF_DCMotor dkmotor3(3, MOTOR34_64KHZ);
AF_DCMotor dkmotor4(4, MOTOR34_64KHZ);

AF_DCMotor * DKMotors[] = { &dkmotor1, &dkmotor2, &dkmotor3, &dkmotor4 };

#endif // INCLUDE_SHAKEITDKSHIELD
// ----------------------------------------------------- END OF HW SETTINGS --------------------------------------------------------------

int L98NMOTORS_ENABLED = 0; //{"Group":"SHAKEIT L298N Motors board","Name":"L98NMOTORS_ENABLED","Title":"L298N motor board enabled \r\n0 = disabled, 1  = enabled, ","DefaultValue":"0","Type":"integer","Template":"int L98NMOTORS_ENABLED = {0};"}

#ifdef INCLUDE_SHAKEITL298N

int L98N_enA = 10; //{"Group":"SHAKEIT L298N Motors board","Name":"L98N_enA","Title":"ENA digital pin","DefaultValue":"10","Type":"integer","Template":"int L98N_enA = {0};","Condition":"L98NMOTORS_ENABLED>=1"}
int L98N_in1 = 9; //{"Group":"SHAKEIT L298N Motors board","Name":"L98N_enB","Title":"IN1 digital pin","DefaultValue":"9","Type":"integer","Template":"int L98N_in1 = {0};","Condition":"L98NMOTORS_ENABLED>=1"}
int L98N_in2 = 8; //{"Group":"SHAKEIT L298N Motors board","Name":"L98N_enB","Title":"IN2 digital pin","DefaultValue":"8","Type":"integer","Template":"int L98N_in2 = {0};","Condition":"L98NMOTORS_ENABLED>=1"}
// motor two
int L98N_enB = 5; //{"Group":"SHAKEIT L298N Motors board","Name":"L98N_enB","Title":"ENB digital pin","DefaultValue":"5","Type":"integer","Template":"int L98N_enB = {0};","Condition":"L98NMOTORS_ENABLED>=1"}
int L98N_in3 = 7; //{"Group":"SHAKEIT L298N Motors board","Name":"L98N_in3","Title":"IN3 digital pin","DefaultValue":"7","Type":"integer","Template":"int L98N_in3 = {0};","Condition":"L98NMOTORS_ENABLED>=1"}
int L98N_in4 = 6; //{"Group":"SHAKEIT L298N Motors board","Name":"L98N_in4","Title":"IN4 digital pin","DefaultValue":"6","Type":"integer","Template":"int L98N_in4 = {0};","Condition":"L98NMOTORS_ENABLED>=1"}

long lastDataReceived = 0;
void L298NMotorsSafetyCheck() {
	if (millis() - lastDataReceived > 2000) {
		digitalWrite(L98N_enA, LOW);
		digitalWrite(L98N_enB, LOW);
		lastDataReceived = millis();
	}
}

void ReadL298NMotors() {
	int value = FlowSerialTimedRead();
	if (value == 0) {
		digitalWrite(L98N_enA, LOW);
	}
	else {
		analogWrite(L98N_enA, value);
	}
	value = FlowSerialTimedRead();
	if (value == 0) {
		digitalWrite(L98N_enB, LOW);
	}
	else {
		analogWrite(L98N_enB, value);
	}
	lastDataReceived = millis();

	// Throw away 2 bytes
	FlowSerialTimedRead();
	FlowSerialTimedRead();
}
#endif

#ifdef INCLUDE_SHAKEITADASHIELD

long lastDataReceived = 0;
void AdaMotorsSafetyCheck() {
	if (millis() - lastDataReceived > 2000) {
		for (int motorIdx = 0; motorIdx < ADAMOTORS_SHIELDSCOUNT * 4; motorIdx++) {
			AdaMotors[motorIdx]->run(RELEASE);
		}
		lastDataReceived = millis();
	}
}

void ReadAdaMotors() {
	for (int motorIdx = 0; motorIdx < ADAMOTORS_SHIELDSCOUNT * 4; motorIdx++) {
		int value = FlowSerialTimedRead();
		if (value == 0) {
			AdaMotors[motorIdx]->run(RELEASE);
		}
		else {
			AdaMotors[motorIdx]->run(FORWARD);
			AdaMotors[motorIdx]->setSpeed(value);
		}
		lastDataReceived = millis();
	}
}
#endif

#ifdef INCLUDE_SHAKEITDKSHIELD

void setPwmFrequency(int pin, int divisor) {
	byte mode;
	if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
		switch (divisor) {
		case 1: mode = 0x01; break;
		case 8: mode = 0x02; break;
		case 64: mode = 0x03; break;
		case 256: mode = 0x04; break;
		case 1024: mode = 0x05; break;
		default: return;
		}
		if (pin == 5 || pin == 6) {
			TCCR0B = TCCR0B & 0b11111000 | mode;
		}
		else {
			TCCR1B = TCCR1B & 0b11111000 | mode;
		}
	}
	else if (pin == 3 || pin == 11) {
		switch (divisor) {
		case 1: mode = 0x01; break;
		case 8: mode = 0x02; break;
		case 32: mode = 0x03; break;
		case 64: mode = 0x04; break;
		case 128: mode = 0x05; break;
		case 256: mode = 0x06; break;
		case 1024: mode = 0x7; break;
		default: return;
		}
		TCCR2B = TCCR2B & 0b11111000 | mode;
	}
}

long lastDKDataReceived = 0;
void DKMotorsSafetyCheck() {
	if (millis() - lastDKDataReceived > 2000) {
		for (int motorIdx = 0; motorIdx < min(1, DKMOTOR_SHIELDSCOUNT) * 4; motorIdx++) {
			DKMotors[motorIdx]->run(RELEASE);
		}
		lastDKDataReceived = millis();
	}
}

void ReadDKMotors() {
	for (int motorIdx = 0; motorIdx < min(1, DKMOTOR_SHIELDSCOUNT) * 4; motorIdx++) {
		int value = FlowSerialTimedRead();
		if (value == 0) {
			DKMotors[motorIdx]->run(RELEASE);
		}
		else {
			DKMotors[motorIdx]->run(FORWARD);
			DKMotors[motorIdx]->setSpeed(value);
		}
		lastDKDataReceived = millis();
	}
}
#endif

#if defined(INCLUDE_TM1638) || defined(INCLUDE_MAX7221_MODULES)
struct ScreenItem {
public:
#ifdef INCLUDE_TM1638
	TM1638 * Screen;
#endif
	byte Buttons;
	byte Oldbuttons;
	byte Intensity;

	ScreenItem() { }
#ifdef INCLUDE_TM1638
	ScreenItem(TM1638 * module) : Screen(module) {
		this->Buttons = 0;
		this->Oldbuttons = 0;
		this->Intensity = 7;
	}
#endif
};
#endif

#ifdef INCLUDE_TM1638
TM1638 TM1638_module1(TM1638_DIO, TM1638_CLK, TM1638_STB1, false);
ScreenItem TM1638_screen1(&TM1638_module1);

TM1638 TM1638_module2(TM1638_DIO, TM1638_CLK, TM1638_STB2, false);
ScreenItem TM1638_screen2(&TM1638_module2);

TM1638 TM1638_module3(TM1638_DIO, TM1638_CLK, TM1638_STB3, false);
ScreenItem TM1638_screen3(&TM1638_module3);

TM1638 TM1638_module4(TM1638_DIO, TM1638_CLK, TM1638_STB4, false);
ScreenItem TM1638_screen4(&TM1638_module4);

TM1638 TM1638_module5(TM1638_DIO, TM1638_CLK, TM1638_STB5, false);
ScreenItem TM1638_screen5(&TM1638_module5);

TM1638 TM1638_module6(TM1638_DIO, TM1638_CLK, TM1638_STB6, false);
ScreenItem TM1638_screen6(&TM1638_module6);

// Screen referencing
ScreenItem * TM1638_screens[] = { &TM1638_screen1, &TM1638_screen2, &TM1638_screen3, &TM1638_screen4, &TM1638_screen5, &TM1638_screen6 };
#endif

#ifdef INCLUDE_MAX7221_MODULES

ScreenItem MAX7221_screen1;
ScreenItem MAX7221_screen2;
ScreenItem MAX7221_screen3;
ScreenItem MAX7221_screen4;
ScreenItem MAX7221_screen5;
ScreenItem MAX7221_screen6;

ScreenItem * MAX7221_screens[] = { &MAX7221_screen1, &MAX7221_screen2, &MAX7221_screen3, &MAX7221_screen4, &MAX7221_screen5, &MAX7221_screen6 };

byte MAX7221_ByteReorder(byte x)
{
	x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa);
	x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc);
	x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0);
	return (x >> 1) | ((x & 1) << 7);
}

#endif // INCLUDE_MAX7221_MODULES

#ifdef INCLUDE_TM1637
TM1637 TM1637_module1(TM1637_CLK1, TM1637_DIO1);
TM1637 TM1637_module2(TM1637_CLK2, TM1637_DIO2);
TM1637 TM1637_module3(TM1637_CLK3, TM1637_DIO3);
TM1637 TM1637_module4(TM1637_CLK4, TM1637_DIO4);
TM1637 TM1637_module5(TM1637_CLK5, TM1637_DIO5);
TM1637 TM1637_module6(TM1637_CLK6, TM1637_DIO6);

TM1637 * TM1637_screens[] = { &TM1637_module1, &TM1637_module2, &TM1637_module3, &TM1637_module4, &TM1637_module5, &TM1637_module6 };
#endif

int i;
byte displayValues[] = { 1, 2, 4, 8, 16, 32, 64, 128 };

#ifdef INCLUDE_74HC595_GEAR_DISPLAY
void RS_74HC595_SendData(byte data) {
	// take the latchPin low so
	// the LEDs don't change while you're sending in bits:
	digitalWrite(RS_74HC595_LATCHPIN, LOW);
	// shift out the bits:
	shiftOut(RS_74HC595_DATAPIN, RS_74HC595_CLOCKPIN, MSBFIRST, data);
	//take the latch pin high so the LEDs will light up:
	digitalWrite(RS_74HC595_LATCHPIN, HIGH);
}

void RS_74HC595_SetChar(char c) {
	byte data = 0;
	if (c == ' ') {
		data = RS_74HC595_ClearDigit;
	}
	else if (c == 'R') {
		data = RS_74HC595_ReverseDigit;
	}
	else if (c == 'N') {
		data = RS_74HC595_NeutralDigit;
	}
	else {
		int value = c - '0';
		if (value >= 0 && value < 10) {
			data = RS_74HC595_dec_digits[value];
		}
	}

	if (RS_74HC595_INVERT == 1) {
		data = data ^ 0xFF;
	}
	RS_74HC595_SendData(data);
}

void RS_74HC595_Init() {
	//set pins to output so you can control the shift register
	pinMode(RS_74HC595_DATAPIN, OUTPUT);
	pinMode(RS_74HC595_LATCHPIN, OUTPUT);
	pinMode(RS_74HC595_CLOCKPIN, OUTPUT);
	RS_74HC595_SetChar(' ');
}
#endif // INCLUDE_74HC595_GEAR_DISPLAY

#ifdef INCLUDE_6c595_GEAR_DISPLAY
void RS_6c595_SetChar(char c) {
	byte data = 0;
	if (c == ' ') {
		data = g_6c595fontArray[8];
	}
	else if (c == 'R') {
		data = g_6c595fontArray[9];
	}
	else if (c == 'N') {
		data = g_6c595fontArray[0];
	}
	else {
		int value = c - '0';
		if (value >= 0 && value < 10) {
			data = g_6c595fontArray[value];
		}
	}
	digitalWrite(RS_6c595_SLAVEPIN, LOW); // << RCLK line goes low
	SPI.transfer(data);  //  << SRCLK goes  high-low 8 times to output 8 bits of data
	digitalWrite(RS_6c595_SLAVEPIN, HIGH); // data outputs change on this rising edge << RCLK line goes high to move data into output register
}
#endif //INCLUDE_6c595_GEAR_DISPLAY

void setup()
{
	FlowSerialBegin(19200);

#ifdef INCLUDE_GAMEPAD
	Joystick.begin(false);
#endif // Inc

#ifdef INCLUDE_TM1638
	// TM1638 INIT
	for (i = 0; i < TM1638_ENABLEDMODULES; i++)
	{
		TM1638_screens[i]->Screen->setupDisplay(true, 7);
		TM1638_screens[i]->Screen->clearDisplay();
	}
#endif

	// NOKIALCD INIT
#ifdef INCLUDE_NOKIALCD
	if (ENABLED_NOKIALCD) {
		glcd1.begin();
		glcd1.clearDisplay();
		glcd1.setRotation(2);
		//nokiaLCD.setFont(&DJB_Get_Digital15pt7b);
		glcd1.setContrast(45);
		glcd1.setCursor(0, 20);
		//nokiaLCD.setFont(&FONT_1);
		glcd1.setTextSize(1);

		glcd1.print("123");

		glcd1.display();
		glcd1.setCursor(0, 20);

#ifdef ENABLE_SECONDARY_NOKIALCD
		glcd2.begin();
		glcd2.setRotation(2);
		glcd2.setContrast(54);
		glcd2.clearDisplay();
		glcd2.print("2 345");
		glcd2.display();
#endif
	}
#endif

	// TM1637 INIT
#ifdef INCLUDE_TM1637
	for (int i = 0; i < TM1637_ENABLEDMODULES; i++) {
		TM1637_screens[i]->init();
		TM1637_screens[i]->set(BRIGHT_TYPICAL);
		TM1637_screens[i]->clearDisplay();
	}
#endif
#ifdef INCLUDE_WS2812B
	// WS2812B INIT
	if (WS2812B_RGBLEDCOUNT > 0) {
		WS2812B_strip.begin();
		WS2812B_strip.show();
	}
#endif

#ifdef INCLUDE_WS2812B_MATRIX
	if (WS2812B_MATRIX_ENABLED > 0) {
		WS2812B_matrix.begin();
		WS2812B_matrix.show();
	}
#endif

	// WS2801 INIT
#ifdef INCLUDE_WS2801
	if (WS2801_RGBLEDCOUNT > 0) {
		WS2801_strip.begin();
		WS2801_strip.show();
	}
#endif

#ifdef INCLUDE_MAX7221_MODULES
	for (i = 0; i < MAX7221_ENABLEDMODULES; i++) {
		MAX7221.shutdown(i, false);
		MAX7221.setIntensity(i, 15);
		MAX7221.clearDisplay(i);
	}
#endif // INCLUDE_MAX7221_MODULES

	// MAX7221 7SEG INIT
#ifdef INCLUDE_MAX7221MATRIX
	// MAX7221 MATRIX INIT
	for (i = 0; i < MAX7221_MATRIX_ENABLED; i++) {
		MAX7221_MATRIX.shutdown(i, false);
		MAX7221_MATRIX.setIntensity(i, 15);
		MAX7221_MATRIX.clearDisplay(i);
	}
#endif

	// 74HC595 INIT
#ifdef INCLUDE_74HC595_GEAR_DISPLAY
	if (ENABLE_74HC595_GEAR_DISPLAY == 1)
	{
		RS_74HC595_Init();
	}
#endif // INCLUDE_74HC595_GEAR_DISPLAY

#ifdef INCLUDE_TACHOMETER
	if (ENABLE_TACHOMETER) {
		rpmTone.begin(pinTacho);
	}
#endif

#ifdef INCLUDE_6c595_GEAR_DISPLAY
	if (ENABLE_6c595_GEAR_DISPLAY == 1) {
		pinMode(RS_6c595_DATAPIN, OUTPUT);
		pinMode(RS_6c595_LATCHPIN, OUTPUT);
		pinMode(RS_6c595_SLAVEPIN, OUTPUT);
		SPI.begin();
		digitalWrite(RS_6c595_SLAVEPIN, LOW); // << RCLK line goes low
		SPI.transfer(g_6c595fontArray[8]);  //  << SRCLK goes  high-low 8 times to output 8 bits of data
		digitalWrite(RS_6c595_SLAVEPIN, HIGH); // data outputs change on this rising edge << RCLK line goes high to move data into output register
	}
#endif // INCLUDE_6c595_GEAR_DISPLAY

	// LCD INIT
#ifdef INCLUDE_I2CLCD
	if (I2CLCD_enabled == 1) {
		I2CLCD.init();
		I2CLCD.backlight();
		I2CLCD.print("Hello world...");
		I2CLCD.clear();
	}
#endif

#ifdef INCLUDE_LEDBACKPACK
	// ADA_HT16K33_7SEGMENTS INIT
	if (ENABLE_ADA_HT16K33_7SEGMENTS == 1) {
		ADA_HT16K33_7SEGMENTS.begin(ADA_HT16K33_7SEGMENTS_I2CADDRESS);
	}

	// ADA_HT16K33_MATRIX INIT
	if (ENABLE_ADA_HT16K33_Matrix == 1) {
		ADA_HT16K33_MATRIX.begin(ADA_HT16K33_MATRIX_I2CADDRESS);
	}
#endif

#ifdef INCLUDE_OLED
	glcd1.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	glcd1.display();
#endif

	// EXTERNAL BUTTONS INIT
	for (int btnIdx = 0; btnIdx < ENABLED_BUTTONS_COUNT; btnIdx++) {
		pinMode(BUTTON_PINS[btnIdx], INPUT_PULLUP);
	}

#ifdef INCLUDE_SHAKEITADASHIELD
	if (ADAMOTORS_SHIELDSCOUNT >= 1)
		Shield1.begin();
	if (ADAMOTORS_SHIELDSCOUNT >= 2)
		Shield2.begin();
	if (ADAMOTORS_SHIELDSCOUNT >= 3)
		Shield3.begin();
#endif // INCLUDE_SHAKEITADASHIELD

#ifdef INCLUDE_SHAKEITDKSHIELD
	if (DKMOTOR_SHIELDSCOUNT > 0) {
		setPwmFrequency(3, 1);
		setPwmFrequency(5, 1);
		setPwmFrequency(6, 1);

		dkmotor1.run(FORWARD);
		dkmotor1.run(FORWARD);
		dkmotor1.run(FORWARD);
		dkmotor1.run(FORWARD);
	}
#endif

#ifdef  INCLUDE_SHAKEITL298N
	pinMode(L98N_enA, OUTPUT);
	pinMode(L98N_enB, OUTPUT);
	pinMode(L98N_in1, OUTPUT);
	pinMode(L98N_in2, OUTPUT);
	pinMode(L98N_in3, OUTPUT);
	pinMode(L98N_in4, OUTPUT);

	digitalWrite(L98N_enA, LOW);
	digitalWrite(L98N_enB, LOW);

	digitalWrite(L98N_in1, LOW);
	digitalWrite(L98N_in2, HIGH);

	digitalWrite(L98N_in3, LOW);
	digitalWrite(L98N_in4, HIGH);
#endif
}

#ifdef INCLUDE_TM1638
void TM1638_SetDisplayFromSerial(TM1638 * screen)
{
	for (i = 0; i < 8; i++) {
		displayValues[i] = FlowSerialTimedRead();
	}
	screen->setDisplay(displayValues);

	// Leds

	for (i = 0; i < 8; i++) {
		char state = (char)FlowSerialTimedRead();

		// Swap led colors if requested
		if (TM1638_SWAPLEDCOLORS == 1) {
			if (state == 'G')
			{
				state = 'R';
			}
			else if (state == 'R')
			{
				state = 'G';
			}
		}

		if (state == 'G') {
			screen->setLED(TM1638_COLOR_GREEN, i);
		}
		else if (state == 'R') {
			screen->setLED(TM1638_COLOR_RED, i);
		}
		else if (state == 'Y') {
			screen->setLED(TM1638_COLOR_RED + TM1638_COLOR_GREEN, i);
		}
		else {
			screen->setLED(TM1638_COLOR_NONE, i);
		}
	}
}
#endif

#ifdef INCLUDE_MAX7221_MODULES
void MAX7221_SetDisplayFromSerial(int idx)
{
	// Digits
	for (i = 0; i < 8; i++) {
		displayValues[i] = MAX7221_ByteReorder((char)FlowSerialTimedRead());
	}

	for (i = 0; i < 8; i++) {
		MAX7221.setRow(idx, 7 - i, displayValues[i]);
	}
}
#endif

#ifdef INCLUDE_LEDBACKPACK
void ADA7SEG_SetDisplayFromSerial(int idx)
{
	// Digits
	for (i = 0; i < 8; i++) {
		displayValues[i] = (char)FlowSerialTimedRead();
	}

	for (i = 0; i < 2; i++) {
		ADA_HT16K33_7SEGMENTS.writeDigitRaw(i, displayValues[i]);
	}

	ADA_HT16K33_7SEGMENTS.writeDigitRaw(2, 0);

	for (i = 2; i < 4; i++) {
		ADA_HT16K33_7SEGMENTS.writeDigitRaw(i + 1, displayValues[i]);
	}

	ADA_HT16K33_7SEGMENTS.writeDisplay();
}
#endif

#ifdef INCLUDE_GAMEPAD
void UpdateGamepadState() {
	int btnidx = 0;
#ifdef INCLUDE_TM1638
	for (i = 0; i < TM1638_ENABLEDMODULES; i++) {
		byte buttonsState = TM1638_screens[i]->Screen->getButtons();

		for (int i = 0; i < 8; i++) {
			Joystick.setButton(btnidx, buttonsState & (1 << i));
			btnidx++;
		}
	}
#endif

	for (i = 0; i < ENABLED_BUTTONS_COUNT; i++) {
		Joystick.setButton(btnidx, digitalRead(BUTTON_PINS[i]) == HIGH ? 0 : 1);
		btnidx++;
	}

	Joystick.sendState();
}

#endif

void sendButtonState() {
	bool sendButtons = false;
#ifdef INCLUDE_TM1638
	for (i = 0; i < TM1638_ENABLEDMODULES; i++) {
		TM1638_screens[i]->Buttons = TM1638_screens[i]->Screen->getButtons();
		if (TM1638_screens[i]->Buttons != TM1638_screens[i]->Oldbuttons) {
			sendButtons = true;
		}
		TM1638_screens[i]->Oldbuttons = TM1638_screens[i]->Buttons;
	}
#endif

#ifdef INCLUDE_TM1638
	for (i = 0; i < TM1638_ENABLEDMODULES; i++) {
		FlowSerialWrite(TM1638_screens[i]->Buttons);
	}
#endif

	for (i = 0; i < ENABLED_BUTTONS_COUNT; i++) {
		FlowSerialWrite(digitalRead(BUTTON_PINS[i]) == HIGH ? 0 : 1);
	}

	FlowSerialFlush();
}

#ifdef INCLUDE_MAX7221MATRIX
void MAX7221_MATRIX_Read() {
	int luminosity = FlowSerialTimedRead();

	if (MAX7221_MATRIX_LUMINOSITY != luminosity) {
		MAX7221_MATRIX.setIntensity(0, luminosity);
		MAX7221_MATRIX_LUMINOSITY = luminosity;
	}

	for (int j = 0; j < 8; j++) {
		MAX7221_MATRIX.setRow(0, 7 - j, FlowSerialTimedRead());
	}
}
#endif // INCLUDE_MAX7221MATRIX

#ifdef INCLUDE_LEDBACKPACK
void ADA_HT16K33_Matrix_Read() {
	int luminosity = FlowSerialTimedRead();

	if (ADA_HT16K33_Matrix_luminosity != luminosity) {
		ADA_HT16K33_MATRIX.setBrightness(luminosity);
		ADA_HT16K33_Matrix_luminosity = luminosity;
	}

	for (int j = 0; j < 8; j++) {
		byte row = FlowSerialTimedRead();
		for (int c = 0; c < 8; c++) {
			ADA_HT16K33_MATRIX.drawPixel(j, c, ((row & (2 ^ c)) > 0) ? LED_GREEN : LED_OFF);
		}
	}

	ADA_HT16K33_MATRIX.writeDisplay();
}
#endif

#ifdef INCLUDE_TM1637
void TM1637_SetDisplayFromSerial(TM1637 * screen)
{
	for (i = 0; i < 4; i++) {
		screen->rawDisplay(i, FlowSerialTimedRead());
	}

	// Skip 4 remaining chars
	for (i = 0; i < 4; i++) {
		FlowSerialTimedRead();
	}
}
#endif

#ifdef INCLUDE_I2CLCD
void Read20x4LCD() {
	if (FlowSerialTimedRead() > 0) {
		//I2CLCD.backlight();
	}
	else {
		//I2CLCD.noBacklight();
	}
	int row = FlowSerialTimedRead();

	I2CLCD.setCursor(0, row);

	I2CLCD.print(FlowSerialReadStringUntil('\n'));
}
#endif

void SetBaudrate() {
	int br = FlowSerialTimedRead();

	delay(200);

	if (br == 1) FlowSerialBegin(300);
	if (br == 2) FlowSerialBegin(1200);
	if (br == 3) FlowSerialBegin(2400);
	if (br == 4) FlowSerialBegin(4800);
	if (br == 5) FlowSerialBegin(9600);
	if (br == 6) FlowSerialBegin(14400);
	if (br == 7) FlowSerialBegin(19200);
	if (br == 8) FlowSerialBegin(28800);
	if (br == 9) FlowSerialBegin(38400);
	if (br == 10) FlowSerialBegin(57600);
	if (br == 11) FlowSerialBegin(115200);
	if (br == 12) FlowSerialBegin(230400);
	if (br == 13) FlowSerialBegin(250000);
	if (br == 14) FlowSerialBegin(1000000);
	if (br == 15) FlowSerialBegin(2000000);
	if (br == 16) FlowSerialBegin(200000);
}

#if defined(INCLUDE_NOKIALCD) || defined(INCLUDE_OLED)
uint8_t  fontSize;
int16_t  posX;
int16_t  posY;
char action;
int16_t v[4 * 2];
uint16_t color;
int16_t w;
int16_t h;
int16_t r;
uint8_t align = 0;
boolean wrap = 0;

int16_t boundX;
int16_t boundY;
uint16_t boundW;
uint16_t boundH;

uint8_t nokiaIndex;
int fontType;

#endif
#if defined(INCLUDE_NOKIALCD)
Adafruit_PCD8544* currentNokia;
#endif
#if defined(INCLUDE_OLED)
Adafruit_SSD1306* currentNokia;
#endif

uint8_t header = 0;
char opt;

void loop() {

#ifdef INCLUDE_SHAKEITL298N
	L298NMotorsSafetyCheck();
#endif

#ifdef INCLUDE_SHAKEITADASHIELD
	AdaMotorsSafetyCheck();
#endif

#ifdef INCLUDE_SHAKEITDKSHIELD
	DKMotorsSafetyCheck();
#endif

#ifdef INCLUDE_GAMEPAD
	UpdateGamepadState();
#endif

	// Wait for data
	if (FlowSerialAvailable() > 0) {
		// Reader header
		header = FlowSerialRead();

		if (header == MESSAGE_HEADER)
		{
			// Read command
			opt = FlowSerialTimedRead();

			// Hello command
			if (opt == '1') {
				FlowSerialTrigger = FlowSerialTimedRead();
				delay(10);
				FlowSerialPrint('h');
				FlowSerialFlush();
			}

			// Set baudrate
			if (opt == '8') {
				SetBaudrate();
			}

			// Simple buttons count
			if (opt == 'J') {
				FlowSerialWrite((byte)(ENABLED_BUTTONS_COUNT));
				FlowSerialFlush();
			}

			//  Module count command
			if (opt == '2') {
				FlowSerialWrite((byte)(TM1638_ENABLEDMODULES));
				FlowSerialFlush();
			}

			//  SIMPLE Module count command
			if (opt == 'B') {
				FlowSerialWrite((byte)(MAX7221_ENABLEDMODULES + TM1637_ENABLEDMODULES + ENABLE_ADA_HT16K33_7SEGMENTS));
				FlowSerialFlush();
			}

			// ACQ Packet
			if (opt == 'A') {
				FlowSerialWrite(0x03);
				FlowSerialFlush();
			}

			// Buttons state
			if (opt == 'C') {
				sendButtonState();
				FlowSerialFlush();
			}

			// Device Name
			if (opt == 'N') {
				FlowSerialPrint(DEVICE_NAME);
				FlowSerialPrint("\n");
				FlowSerialFlush();
			}

			// Tachometer
			if (opt == 'T') {
#ifdef INCLUDE_TACHOMETER
				int freq = FlowSerialReadStringUntil('\n').toInt();
				if (freq > 0) {
					rpmTone.play(freq);
					//tone(pinTacho, freq);
				}
				else {
					rpmTone.stop();
					//noTone(pinTacho);
				}
#endif
			}

			// Boost gauge
			if (opt == 'U') {
#ifdef INCLUDE_BOOSTGAUGE
				int level = FlowSerialReadStringUntil('\n').toInt();
				analogWrite(pinBoost, level);
#endif
			}

			// Features command
			if (opt == '0') {
				delay(10);

				// Matrix
				if (MAX7221_MATRIX_ENABLED == 1 || ENABLE_ADA_HT16K33_Matrix == 1) {
					FlowSerialPrint("M");
				}

				// LCD
				if (I2CLCD_enabled == 1) {
#ifdef INCLUDE_I2CLCD
					FlowSerialPrint("L");
#endif
				}

				if (ENABLED_NOKIALCD > 0 || ENABLED_OLEDLCD > 0) {
					FlowSerialPrint("K");
				}

				// Gear
				FlowSerialPrint("G");

				// Name
				FlowSerialPrint("N");

				// Additional buttons
				FlowSerialPrint("J");

				// Custom Protocol Support
				FlowSerialPrint("P");

				// RGB MATRIX
				if (WS2812B_MATRIX_ENABLED > 0) {
					FlowSerialPrint("R");
				}

#if defined(INCLUDE_SHAKEITADASHIELD) || defined(INCLUDE_SHAKEITDKSHIELD) || defined(INCLUDE_SHAKEITL298N)
				// Afafuit motorshields
				FlowSerialPrint("V");
#endif // INCLUDE_SHAKEITADASHIELD

#ifdef INCLUDE_TACHOMETER
				if (ENABLE_TACHOMETER > 0) {
					FlowSerialPrint("T");
				}
#endif

#ifdef INCLUDE_BOOSTGAUGE
				if (ENABLE_BOOSTGAUGE > 0) {
					FlowSerialPrint("U");
				}
#endif

				FlowSerialPrint("\n");
				FlowSerialFlush();
			}

			// Write 7seg data
			if (opt == '3') {
#ifdef INCLUDE_TM1638
				// TM1638
				for (int j = 0; j < TM1638_ENABLEDMODULES; j++) {
					// Wait for display data
					int newIntensity = FlowSerialTimedRead();
					if (newIntensity != TM1638_screens[j]->Intensity) {
						TM1638_screens[j]->Screen->setupDisplay(true, newIntensity);
						TM1638_screens[j]->Intensity = newIntensity;
					}

					TM1638_SetDisplayFromSerial(TM1638_screens[j]->Screen);
				}
#endif
			}

			// "Vibe" motors and fans
			if (opt == 'V') {
#if defined(INCLUDE_SHAKEITADASHIELD) || defined(INCLUDE_SHAKEITDKSHIELD) || defined(INCLUDE_SHAKEITL298N)

				char action = FlowSerialTimedRead();

				// Count
				if (action == 'C') {
					FlowSerialWrite(ADAMOTORS_SHIELDSCOUNT + min(1, DKMOTOR_SHIELDSCOUNT) + min(1, L98NMOTORS_ENABLED));
				}
				// Set motors
				else if (action == 'S') {
#ifdef  INCLUDE_SHAKEITADASHIELD
					ReadAdaMotors();
#endif
#ifdef  INCLUDE_SHAKEITDKSHIELD
					ReadDKMotors();
#endif
#ifdef  INCLUDE_SHAKEITL298N
					ReadL298NMotors();
#endif
				}
#endif
			}

			// No leds 7 segments displays
			if (opt == 'S') {
#ifdef INCLUDE_TM1637
				// TM1637
				for (int j = 0; j < TM1637_ENABLEDMODULES; j++) {
					// Intensity
					TM1637_screens[j]->set(FlowSerialTimedRead());
					TM1637_SetDisplayFromSerial(TM1637_screens[j]);
				}
#endif
				// MAX7221
#ifdef INCLUDE_MAX7221_MODULES
				for (int j = 0; j < MAX7221_ENABLEDMODULES; j++) {
					// Wait for display data
					int newIntensity = FlowSerialTimedRead();
					if (newIntensity != MAX7221_screens[j]->Intensity) {
						MAX7221.setIntensity(j, newIntensity * 2 + 1);
						MAX7221_screens[j]->Intensity = newIntensity;
					}

					MAX7221_SetDisplayFromSerial(j);
				}
#endif // INCLUDE_MAX7221_MODULES

#ifdef INCLUDE_LEDBACKPACK
				// Simple ADA display
				for (int j = 0; j < ENABLE_ADA_HT16K33_7SEGMENTS; j++) {
					int newIntensity = FlowSerialTimedRead();
					ADA_HT16K33_7SEGMENTS.setBrightness(newIntensity * 2 + 1);

					ADA7SEG_SetDisplayFromSerial(j);
				}
#endif
			}

			//  RGBLED count command
			if (opt == '4') {
				FlowSerialWrite((byte)(WS2812B_RGBLEDCOUNT + WS2801_RGBLEDCOUNT));
				FlowSerialFlush();
			}

			// Write RGB LEDS data
			if (opt == '6') {
#ifdef INCLUDE_WS2812B
				for (uint8_t j = 0; j < WS2812B_RGBLEDCOUNT; j++) {
					uint8_t r = FlowSerialTimedRead();
					uint8_t g = FlowSerialTimedRead();
					uint8_t b = FlowSerialTimedRead();
					if (WS2812B_RIGHTTOLEFT == 1) {
						WS2812B_strip.setPixelColor(WS2812B_RGBLEDCOUNT - j - 1, r, g, b);
					}
					else {
						WS2812B_strip.setPixelColor(j, r, g, b);
					}
				}
				if (WS2812B_RGBLEDCOUNT > 0) {
					WS2812B_strip.show();
				}

#endif

#ifdef INCLUDE_WS2801
				for (uint8_t j = 0; j < WS2801_RGBLEDCOUNT; j++) {
					uint8_t r = FlowSerialTimedRead();
					uint8_t g = FlowSerialTimedRead();
					uint8_t b = FlowSerialTimedRead();
					if (WS2801_RIGHTTOLEFT == 1) {
						WS2801_strip.setPixelColor(WS2801_RGBLEDCOUNT - j - 1, r, g, b);
					}
					else
					{
						WS2801_strip.setPixelColor(j, r, g, b);
					}
				}
				if (WS2801_RGBLEDCOUNT > 0) {
					WS2801_strip.show();
				}
#endif
				// Acq !
				FlowSerialWrite(0x15);
			}

			// Write RGB MATRIX data
			if (opt == 'R') {
#ifdef INCLUDE_WS2812B_MATRIX
				for (uint8_t j = 0; j < 64; j++) {
					uint8_t r = FlowSerialTimedRead();
					uint8_t g = FlowSerialTimedRead();
					uint8_t b = FlowSerialTimedRead();
					WS2812B_matrix.setPixelColor(j, r, g, b);
				}
				WS2812B_matrix.show();
#endif

				// Acq !
				FlowSerialWrite(0x15);
			}

			// MAX7221 MATRIX
			if (opt == 'M') {
#ifdef INCLUDE_MAX7221MATRIX
				if (MAX7221_MATRIX_ENABLED == 1) {
					MAX7221_MATRIX_Read();
				}
#endif // INCLUDE_MAX7221MATRIX

#ifdef INCLUDE_LEDBACKPACK
				if (ENABLE_ADA_HT16K33_Matrix == 1) {
					ADA_HT16K33_Matrix_Read();
				}
#endif
			}

			// GEAR
			if (opt == 'G') {
				char gear = FlowSerialTimedRead();

#ifdef INCLUDE_74HC595_GEAR_DISPLAY
				if (ENABLE_74HC595_GEAR_DISPLAY == 1) {
					RS_74HC595_SetChar(gear);
				}
#endif

#ifdef INCLUDE_6c595_GEAR_DISPLAY
				if (ENABLE_6c595_GEAR_DISPLAY == 1) {
					RS_6c595_SetChar(gear);
				}
#endif
				//
				// Do what you want with current gear here ;)
				//
			}

			// I2C LCD
			if (opt == 'L') {
#ifdef INCLUDE_I2CLCD
				Read20x4LCD();
#endif
			}

			// Nokia | OLEDS
			if (opt == 'K')
			{
#if defined(INCLUDE_NOKIALCD) || defined(INCLUDE_OLED)

				nokiaIndex = FlowSerialTimedRead();
				action = FlowSerialTimedRead();

				currentNokia = nokiaLCDs[nokiaIndex];

				if (action == 'C')
				{
					currentNokia->clearDisplay();
				}

				if (action == 'N')
				{
					FlowSerialWrite((byte)ENABLED_NOKIALCD);
					FlowSerialFlush();
				}
				if (action == 'O')
				{
					FlowSerialWrite((byte)ENABLED_OLEDLCD);
					FlowSerialFlush();
				}

				if (action == 'I')
				{
#ifdef INCLUDE_NOKIALCD
					currentNokia->setContrast(FlowSerialTimedRead());
#endif // INCLUDE_NOKIALCD
				}

				else if (action == 'D')
				{
					currentNokia->display();
				}
				else if (action == 'P')
				{
					fontSize = (uint8_t)FlowSerialTimedRead();
					fontType = (uint8_t)FlowSerialTimedRead();
					posX = (int16_t)FlowSerialTimedRead();
					posY = (int16_t)FlowSerialTimedRead();
					color = FlowSerialTimedRead();
					wrap = FlowSerialTimedRead() > 0;
					align = FlowSerialTimedRead();

					currentNokia->setFont();

					if (fontType == 0) {
					}
#ifdef CUSTOM_LCD_FONT_1
					else if (fontType == 1) {
						currentNokia->setFont(&CUSTOM_LCD_FONT_1);
					}
#endif
#ifdef CUSTOM_LCD_FONT_2
					else if (fontType == 2) {
						currentNokia->setFont(&CUSTOM_LCD_FONT_2);
					}
#endif
#ifdef CUSTOM_LCD_FONT_3
					else if (fontType == 3) {
						currentNokia->setFont(&CUSTOM_LCD_FONT_3);
					}
#endif

					currentNokia->setTextWrap(wrap);
					currentNokia->setTextSize(fontSize);
					currentNokia->setTextColor(color);

					String content = FlowSerialReadStringUntil('\n');
					String content2 = content + "\n ";
					if (align == 2)
					{
						currentNokia->getTextBounds((char*)content2.c_str(), 0, 0, &boundX, &boundY, &boundW, &boundH);
						posX = posX - (boundW / 2);
					}
					else if (align == 3)
					{
						currentNokia->getTextBounds((char*)content2.c_str(), 0, 0, &boundX, &boundY, &boundW, &boundH);
						posX = posX - boundW;
					}

					currentNokia->setCursor(posX, posY);
					currentNokia->print(content);
				}
				else if (action == 'L') {
					posX = (int16_t)FlowSerialTimedRead();
					posY = (int16_t)FlowSerialTimedRead();
					w = (int16_t)FlowSerialTimedRead(); // x2
					h = (int16_t)FlowSerialTimedRead(); // y2
					color = FlowSerialTimedRead();

					currentNokia->drawLine(posX, posY, w, h, color);
				}
				else if (action == 'T') {
					posX = (int16_t)FlowSerialTimedRead();
					posY = (int16_t)FlowSerialTimedRead();
					w = (int16_t)FlowSerialTimedRead(); // x2
					h = (int16_t)FlowSerialTimedRead(); // y2
					int thickness = FlowSerialTimedRead();
					color = FlowSerialTimedRead();

					float dx = posX - w;
					float dy = posY - h;
					float d = sqrtf(dx * dx + dy * dy);
					if (!d)
						return;

					int v[4 * 2];

					/* left up */
					v[0] = posX - thickness * dy / d;
					v[1] = posY + thickness * dx / d;
					/* right up */
					v[2] = posX + thickness * dy / d;
					v[3] = posY - thickness * dx / d;
					/* right down */
					v[4] = w + thickness * dy / d;
					v[5] = h - thickness * dx / d;
					/* left down */
					v[6] = w - thickness * dy / d;
					v[7] = h + thickness * dx / d;

					currentNokia->fillTriangle(v[0], v[1], v[6], v[7], v[2], v[3], color);
					currentNokia->fillTriangle(v[2], v[3], v[4], v[5], v[6], v[7], color);
				}

				else if (action == 'F' || action == 'R')
				{
					posX = (int16_t)FlowSerialTimedRead();
					posY = (int16_t)FlowSerialTimedRead();
					w = (int16_t)FlowSerialTimedRead();
					h = (int16_t)FlowSerialTimedRead();
					r = (int16_t)FlowSerialTimedRead();
					color = FlowSerialTimedRead();

					if (r == 0) {
						if (action == 'F')
							currentNokia->fillRect(posX, posY, w, h, color);
						else
							currentNokia->drawRect(posX, posY, w, h, color);
					}
					else {
						if (action == 'F')
							currentNokia->fillRoundRect(posX, posY, w, h, r, color);
						else
							currentNokia->drawRoundRect(posX, posY, w, h, r, color);
					}
				}

#endif
			}

			// Custom protocol for end users (See Wiki for more infos : https://github.com/zegreatclan/AssettoCorsaTools/wiki/Custom-Arduino-hardware-support)
			if (opt == 'P') {

				// -------------------------------------------------------
				// EXAMPLE 3 - Driving a E36 speed gauge connected to pin D3
				// Protocol formula must be set in simhub to round([DataCorePlugin.GameData.NewData.SpeedKmh],0)
				// format([DataCorePlugin.GameData.NewData.SpeedKmh],'0')
				// -------------------------------------------------------
				CustomProtocolExample3_E36Speedo();
			}
		}
	}
}


// -------------------------------------------------------
// EXAMPLE 3 - Driving a E36 speed gauge connected to pin D3
// Protocol formula must be set in simhub to round([DataCorePlugin.GameData.NewData.SpeedKmh],0)
// format([DataCorePlugin.GameData.NewData.SpeedKmh],'0')
// -------------------------------------------------------

Tone e36SppedTone;
bool e36SppedToneInitDone = false;
void CustomProtocolExample3_E36Speedo() {
	int speedPin = 3;
  int mpgPin = 4;
  int fuelPin = 5;
  int tempPin = 6;
	if (!e36SppedToneInitDone) {
		e36SppedTone.begin(speedPin);
		e36SppedToneInitDone = true;
	}

	int speed = FlowSerialReadStringUntil(';').toInt();
  int fuel = FlowSerialReadStringUntil(';').toInt();
  int mpg = FlowSerialReadStringUntil('\n').toInt();

	int speedoutput = map(speed, 0, 286, 0, 367);
  int mpgoutput = map(mpg, 0, 100, 255, 0);
  int fueloutput = map(fuel, 0, 100, 0, 162);

int speedcorrect = int(speed, HEX);
	if (speedoutput<1) {
		e36SppedTone.stop();
	}
	else {
		e36SppedTone.play(speedoutput);
	}
 analogWrite(mpgPin, mpgoutput); //Mpg Gauge
 analogWrite(fuelPin, fueloutput); //Fuel Gauge
 analogWrite(tempPin, 50); //Temp Gauge set to Midway
}

