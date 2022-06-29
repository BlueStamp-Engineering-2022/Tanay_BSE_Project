#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "LedControl.h"

const int trigPin = 7;
const int echoPin = 8;

int randomNumber = random(1,2);
LiquidCrystal_I2C lcd(0x27, 16, 1);
//define variables
LedControl lc = LedControl(11, 13, 12, 1);
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


byte neutral[8] = {0x00, 0x3c, 0x42, 0x5a, 0x5a, 0x42, 0x3c, 0x00};
byte happy[8] = {0x00, 0x1c, 0x24, 0x5c, 0x5c, 0x24, 0x1c, 0x00};
byte angry[8] = {0x00, 0x3c, 0x42, 0x5a, 0x5a, 0x42, 0x3c, 0x00};
byte surprised[8] = {0x7e, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x7e};
byte love[8] = {0x00,0x66,0x99,0x81,0x42,0x24,0x18,0x00};
byte defualt[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

void setup()
{

  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  //Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  //Serial.println("with Arduino UNO R3");
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  if (randomNumber == 1)
  {
    lcd.println("I am Happy       ");
  }
  else
  {
    lcd.println("I am Angry        ");
  }
  //lcd.println("Distance: ");



}




void loop()
{

  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delay(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  delay(100);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("distance ");
  Serial.println(distance);
  /*lcd.setCursor(0, 1);
    if (distance < 200) {
      lcd.print(distance);
      //lcd.print(" cm              ");
    }
    else {
    lcd.print("Error       ");
    }*/


  if (randomNumber == 1) {
    if (distance <= 5) {
      lc.clearDisplay(0);
      printByte(surprised); 
    }
    else if (5 < distance && distance <= 15)
    {
      lc.clearDisplay(0);
      printByte(defualt);
    }
    else if (15 < distance && distance < 25)
    {
      lc.clearDisplay(0);
      printByte(happy);
    }
    else
    {
      lc.clearDisplay(0);
      printByte(neutral);
    }
  }


  
  else {

    if (distance <= 5) {
      lc.clearDisplay(0);
      printByte(surprised);
    }
    else if (5 < distance && distance <= 15)
    {
      lc.clearDisplay(0);
      printByte(defualt);
    }
    else if (15 < distance && distance < 25)
    {
      lc.clearDisplay(0);
      printByte(angry);
    }
    
    else
    {
      lc.clearDisplay(0);
      printByte(neutral);
    }
  }





  delay(100);
}

void printByte(byte character [])
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    lc.setRow(0, i, character[i]);
  }
}
