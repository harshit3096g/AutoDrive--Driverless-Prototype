/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 
#include <elapsedMillis.h>
#include <Servo.h> 

elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs 
Servo myservo;  // create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
int pos = 30;    // variable to store the servo position 
unsigned int interval = 4000;
 
void setup() 
{ 
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(65); 
} 
 
void loop() 
{ 
 timeElapsed = 0; 
 while (timeElapsed < interval) 
 {
  analogWrite(3,155); // Right       FWD WITH FULL SPEED
analogWrite(11,155); // Left
analogWrite(A0,0);//Right
analogWrite(A1,0);//Left
analogWrite(A2,255);//Right
analogWrite(A3,255);//Left
 }

 analogWrite(3,100); // Right       FWD WITH FULL SPEED
analogWrite(11,100); // Left
analogWrite(A0,0);//Right
analogWrite(A1,0);//Left
analogWrite(A2,255);//Right
analogWrite(A3,255);//Left
  
   for(pos = 65; pos <= 95; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
 myservo.write(95); 

   timeElapsed = 0; 
 while (timeElapsed < 3500) 
 {
  analogWrite(3,100); // Right       FWD 
analogWrite(11,100); // Left
analogWrite(A0,0);//Right
analogWrite(A1,0);//Left
analogWrite(A2,255);//Right
analogWrite(A3,255);//Left
 }

  for(pos = 95; pos>=65; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15); 
  }
    myservo.write(65); 
 /*   
     timeElapsed = 0; 
 while (timeElapsed < interval) 
 {
  analogWrite(3,155); // Right       FWD 
analogWrite(11,155); // Left
analogWrite(A0,0);//Right
analogWrite(A1,0);//Left
analogWrite(A2,255);//Right
analogWrite(A3,255);//Left
 } 


analogWrite(3,100); // Right       FWD WITH FULL SPEED
analogWrite(11,100); // Left
analogWrite(A0,0);//Right
analogWrite(A1,0);//Left
analogWrite(A2,255);//Right
analogWrite(A3,255);//Left
  
   for(pos = 65; pos <= 95; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
 myservo.write(95); 

   timeElapsed = 0; 
 while (timeElapsed < 3800) 
 {
  analogWrite(3,100); // Right       FWD 
analogWrite(11,100); // Left
analogWrite(A0,0);//Right
analogWrite(A1,0);//Left
analogWrite(A2,255);//Right
analogWrite(A3,255);//Left
 }

  for(pos = 95; pos>=65; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15); 
  }
    myservo.write(65); 
    
/*
  for(pos = 100; pos>=30; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }*/ 

} 

