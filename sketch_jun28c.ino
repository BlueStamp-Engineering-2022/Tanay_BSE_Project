 #include "LedControlMS.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


const int trigPin = 7;
const int echoPin = 8;
const int ledPin = 11;
char inputByte;
int randomNumber;
int pos;
int number;

//Emotions
/*
 * Love --> random motion
 * Sad --> slow motion
 * Angry --> Jerky
 *
*/

LiquidCrystal_I2C lcd(0x27, 16, 1);
//define variables


#define NBR_MTX 2
#define NEUTRAL 1
#define SURPRISED 2
#define HAPPY 3
#define ANGRY 4
#define LOVE 5
#define SAD 6

Servo MG995_tilt;
Servo MG996_pan;
Servo LEFT_BROW;
Servo RIGHT_BROW;


int emotion = NEUTRAL;

LedControl lc = LedControl(11, 13, 12, NBR_MTX);

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement


byte neutral[8] = {0x00, 0x3c, 0x42, 0x5a, 0x5a, 0x42, 0x3c, 0x00};
byte happy[8] = {0x00, 0x1c, 0x24, 0x5c, 0x5c, 0x24, 0x1c, 0x00};
byte angry[8] = {0x00, 0x3c, 0x42, 0x5a, 0x5a, 0x42, 0x3c, 0x00};
byte surprised[8] = {0x7e, 0x81, 0x81, 0x99, 0x99, 0x81, 0x81, 0x7e};
byte love[8] = {0x00, 0x66, 0x99, 0x81, 0x42, 0x24, 0x18, 0x00};
byte sad[8] = {0x00, 0x0c, 0x12, 0x3a, 0x5a, 0x42, 0x3c, 0x00};

void setup()
{

  int randomNumber = 1;

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
  
  //lcd.println("Distance: ");


  // We need to attach the servo to the used pin number
  MG995_tilt.attach(6);
  MG996_pan.attach(9);
  LEFT_BROW.attach(A3);
  RIGHT_BROW.attach(A2);
  



}

void neutralMethod() {
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  emotion = NEUTRAL;
  printByte(neutral);
  LEFT_BROW.write(90);
  RIGHT_BROW.write(90);

  delay(100);
MG996_pan.write(20);
  MG995_tilt.write(10);  

  delay(100);
}

void surprisedMethod() {
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  emotion = SURPRISED;
  printByte(surprised);

  LEFT_BROW.write(135);
  RIGHT_BROW.write(45);
  delay(100);
  LEFT_BROW.write(30);
  RIGHT_BROW.write(120);
  delay(100);
  LEFT_BROW.write(135);
  RIGHT_BROW.write(45);
  delay(100);
  MG996_pan.write(20);
  MG995_tilt.write(10);  
 

  delay(100);
}
void loveMethod() {
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  emotion = LOVE;
  printByte(love);

  LEFT_BROW.write(135);
  RIGHT_BROW.write(45);
  delay(100);
  LEFT_BROW.write(90);
  RIGHT_BROW.write(0);
  delay(100);
  LEFT_BROW.write(135);
  RIGHT_BROW.write(45);

  delay(10);
  MG996_pan.write(20);
  MG995_tilt.write(10);  
  delay(100);
}
void happyMethod() {
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  emotion = HAPPY;
  printByte(happy);

    LEFT_BROW.write(90);
  RIGHT_BROW.write(90);
  delay(100);

  LEFT_BROW.write(135);
  RIGHT_BROW.write(45);
  delay(100);
  MG996_pan.write(20);
  MG995_tilt.write(10);  
  delay(100);
  
}

void angryMethod() {
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  emotion = ANGRY;
  printByte(angry);


  LEFT_BROW.write(45);
  RIGHT_BROW.write(135);
  delay(100);
}
void sadMethod() {
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  emotion = SAD;
  printByte(sad);


  LEFT_BROW.write(120);
  RIGHT_BROW.write(60);
  delay(100);


  
 }

void loop()
{
  Serial.println("test");
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
  delay(10);
  Serial.print("distance ");
  Serial.println(distance);

   while(Serial.available()>0)
  {
    inputByte= Serial.read();
    Serial.println(inputByte);
    if (inputByte=='Z')
    {
    randomNumber = 1;
    }
    else 
    {
      randomNumber = 2;
    }
    //else if (inputByte=='z'){
    //digitalWrite(13,LOW); 
  }
  Serial.println(randomNumber);
  /*lcd.setCursor(0, 1);
    if (distance < 200) {
      lcd.print(distance);
      //lcd.print(" cm              ");
    }
    else {
    lcd.print("Error       ");
    }*/

    if (randomNumber == 1)
  {
    lcd.println("I am Happy            ");
  }
  else
  {
    lcd.println("I am Angry            ");
  }

  if (randomNumber == 1) {
    if (distance <= 5 && emotion != SURPRISED)  {
      surprisedMethod();
    }
    else if (5 < distance && distance <= 10 && emotion != LOVE )
    {
      loveMethod();
    }
    else if (10 < distance && distance < 25 && emotion != HAPPY)
    {
      happyMethod();
    }
    else if (distance >= 25 && emotion != NEUTRAL)
    {
      neutralMethod();
    }
  }



  else {

    if (distance <= 5 && emotion != SURPRISED)  {
      surprisedMethod();
    }
    else if (5 < distance && distance <= 10 && emotion != NEUTRAL )
    {
      neutralMethod();
    }
    else if (10 < distance && distance < 25 && emotion != ANGRY)
    {
      angryMethod();
    }

    else if (distance >= 25 && emotion != SAD)
    {
      
      sadMethod();
    }

  }





  delay(1000);

  lcd.clear();
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
