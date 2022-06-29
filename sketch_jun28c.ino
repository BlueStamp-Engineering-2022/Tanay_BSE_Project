#include "LedControlMS.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>


const int trigPin = 7;
const int echoPin = 8;

int randomNumber = 1;
LiquidCrystal_I2C lcd(0x27, 16, 1);
//define variables


#define NBR_MTX 2
#define NEUTRAL 1
#define SURPRISED 2
#define HAPPY 3
#define ANGRY 4
#define LOVE 5




int emotion = NEUTRAL;

LedControl lc = LedControl(11, 13, 12, NBR_MTX);

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


byte neutral[8] = {0x00, 0x3c, 0x42, 0x5a, 0x5a, 0x42, 0x3c, 0x00};
byte happy[8] = {0x00, 0x1c, 0x24, 0x5c, 0x5c, 0x24, 0x1c, 0x00};
byte angry[8] = {0x00, 0x3c, 0x42, 0x5a, 0x5a, 0x42, 0x3c, 0x00};
byte surprised[8] = {0x7e, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x7e};
byte love[8] = {0x00, 0x66, 0x99, 0x81, 0x42, 0x24, 0x18, 0x00};

void setup()
{

  lc.shutdown(0, false);
  lc.shutdown(1, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  lc.setIntensity(1, 8);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.clearDisplay(1);


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
    if (distance <= 5 && emotion != SURPRISED)  {
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      emotion = SURPRISED;
      printByte(surprised);
    }
    else if (5 < distance && distance <= 15 && emotion != LOVE )
    {
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      emotion = LOVE;
      printByte(love);
    }
    else if (15 < distance && distance < 25 && emotion != HAPPY)
    {
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      emotion = HAPPY;
      printByte(happy);
    }
    else if (distance >= 25 && emotion != NEUTRAL)
    {
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      emotion = NEUTRAL;
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
      printByte(love);
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
    lc.setRow(1, i, character[i]);
  }
}
