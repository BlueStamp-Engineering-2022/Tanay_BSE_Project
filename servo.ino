// Include the Servo library 
#include <Servo.h> 


// Create a servo object 
Servo MG995_tilt; 
Servo MG996_pan;
Servo LEFT_BROW;
Servo RIGHT_BROW; 
int pos = 0;
void setup() { 
  Serial.begin(9600);
  
   // We need to attach the servo to the used pin number 
   MG995_tilt.attach(11); 
   MG996_pan.attach(9);
   LEFT_BROW.attach(12);
   RIGHT_BROW.attach(13);
    
   //small servo without top thing is pin 13
   //small servo with top thing is pin 12
   //big servo 995 is pin 11
   //big servo 996 is pin 9
}
void loop(){ 
   //Serial.println("test");

   
   for(pos; pos<=300; pos+=30)
   {
    MG995_tilt.write(pos); 
    delay(10);
    Serial.println("995 works");
    break;
   }
   for(pos; pos<=300; pos+=30)
   {
    MG996_pan.write(pos);
    delay(10);
    Serial.println("996 works");
    break;
   }
   for(pos; pos<=300; pos+=30)
   {
    LEFT_BROW.write(pos);
    delay(10);
    Serial.println("left works");
    break;
   }
   for(pos; pos<=300; pos+=30)
   {
    RIGHT_BROW.write(pos);
    delay(10);
    Serial.println("right works");
    break;
   }
   exit(0);
}
