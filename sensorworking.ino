#include <Wire.h>
#include <LiquidCrystal_I2C.h>


const int trigPin = 7;
const int echoPin = 8;
LiquidCrystal_I2C lcd(0x27, 16, 2);
//define variables

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  //Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  //Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  //Serial.println("with Arduino UNO R3");
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Distance: ");
 
 
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
  /*Serial.print("distance ");
  Serial.println(distance);*/
  lcd.setCursor(0, 1);
  if (distance < 200) {
      lcd.print(distance);
      lcd.print(" cm              ");
    }
  else {
    lcd.print("Error       ");
    }

  delay(100);
}
