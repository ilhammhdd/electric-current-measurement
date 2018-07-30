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

int ScaleFactor = 66;
double Raw = 0;
double Voltage = 0;
double Amps = 0;
String bufferVoltage;
String bufferAmps;
String bufferZero;
String bufferRaw;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() 
{
  //Pembacaan di loop agar lebih presisi
  for (int i=0; i < 1000; i++){
    Raw = analogRead(A3)/1024.0;
    Voltage = Raw*5000;
  }

  //Arus dihitung dari tegangan yang didapatkan dikurangi dengan offet tegangan lalu dibagi dengan faktor skala modul ACS712-30A
  Amps = ((Voltage-2500)/ScaleFactor);
    
  Serial.println("\n-----------------------------------------");
  Serial.println("Before added raw offset : "+String(Amps,3));

  //Arus yang didapatkan ditambah dengan raw yang terbaca untuk hasil akhir
  Amps += Raw;
  Amps = Amps <= Raw ? 0 : Amps;
  
  bufferRaw += F("Titik nol: ");
  bufferRaw += String(Raw,3);
  bufferAmps+= String(Amps, 3);
  bufferAmps+= F("mA");

  Serial.println("Raw :"+bufferRaw);
  Serial.println("After added raw offset : "+bufferAmps);
  Serial.println("-----------------------------------------\n");

  lcd.setCursor(0,0);
  lcd.print(bufferRaw);
  lcd.setCursor(0,1);
  lcd.print(bufferAmps);
  
  delay(800);
  lcd.clear();
  bufferRaw="";
  bufferAmps= "";
}


