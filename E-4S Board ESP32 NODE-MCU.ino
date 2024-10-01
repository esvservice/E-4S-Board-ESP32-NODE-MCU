/*
 Name:		E_4S_Board_ESP32_NODE_MCU.ino
 Created:	1/10/2024 11:26:31 AM
 Author:	JESS - ON4JES 
*/

// the setup function runs once when you press reset or power the board
#include "E4SBoard.h"
#include "LiquidCrystal_I2C.h"
#include "Temperature_LM75_Derived.h"
int lcdColumns = 20;
int lcdRows = 4;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);   // base adress=0x27 of 3F
Generic_LM75 temperature(0x48);
E4SClass E4SBoard;


void setup() {
	E4SBoard.Begin();
	lcd.begin();
	lcd.backlight();
	lcd.print ("ON4IPR - E4SBOARD - SAMPLE");
}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
