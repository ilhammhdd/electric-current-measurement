#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/*
 * Pin :
 *  LCD1602 I2C :
 *    SDA : A4
 *    SCL : A5
 *  ACS217 : 
 *    OUT : A3
 * 
*/

LiquidCrystal_I2C lcd(0x27,16,2);

const int AnalogIn = A0;
int MVPerAmp = 185;
float ACOffset = 2490.0;//mv
unsigned int Raw = 0;
double Voltage = 0;
double Current = 0;
String Empty = "                ";

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() 
{
  for (int i=0; i < 64; i++){
    Raw = Raw + analogRead(AnalogIn);
  }

  Voltage = ((Raw/64)/1023.0)*5000; //mV
  Current = ((Voltage-ACOffset)/MVPerAmp); //A

  Serial.println("\n-------------------------------------");
  Serial.println("Raw : "+String(analogRead(AnalogIn)));
  Serial.println("Voltage : "+String(Voltage, 3)+" mV");
  Serial.println("Current : "+String(Current, 3)+" A");
  Serial.println("-------------------------------------\n");
  
  lcd.setCursor(0,0);
  lcd.print(String(Voltage, 2)+"mV");
  lcd.setCursor(0,1);
  lcd.print(String(Current, 2)+"A");
  
  Raw=0;
  
  delay(700);

  lcd.setCursor(0,0);
  lcd.print(Empty);
  lcd.setCursor(1,0);
  lcd.print(Empty);
}
