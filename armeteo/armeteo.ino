//THIS SOURCE CODE IS WRITTEN BY FODOR TIBOR in 2014 
//EVERY LIBRARY HAS IT`S LICENCE
//THIS CODE IS FREE TO USE

#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;
LiquidCrystal_I2C lcd(0x27,16,2);


//////////////
// RGB LED
int redPin = 9;
int greenPin = 10;
int bluePin = 11;
// RGB LED END
//////////////

void setup()
{
//////////////
// RGB LED
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
// RGB LED END
//////////////  
  
 setColor(0, 255, 255);
  
  lcd.init(); 
  lcd.backlight();
  lcd.print("Initializing");
  lcd.setCursor(0,1);
  lcd.print("hardware");
  dht.begin();
  
 Serial.begin(9600);
   if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
  delay(10000);
}

void loop()
{
  
  lcd.clear();
  lcd.print(dht.readHumidity());
  lcd.print("% Humidity ");
  setColor(255, 0, 0);  // red
  delay(5000);
  
  lcd.clear();
  lcd.print(bmp.readPressure());
  lcd.print(" Pa ");
  setColor(0, 255, 0);  // green
  delay(5000);
  
  lcd.clear();
  lcd.print(bmp.readTemperature());
  lcd.print(" *C ");
  setColor(0, 0, 255);  // blue
  delay(5000);
  
  lcd.clear();
  lcd.print(bmp.readAltitude());
  lcd.print(" meters ");
  setColor(80, 0, 80);
  delay(5000);
  
  seriSend();
  
}

void seriSend()
{
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.print(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.print(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.print(" meters");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.println();
}


void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
