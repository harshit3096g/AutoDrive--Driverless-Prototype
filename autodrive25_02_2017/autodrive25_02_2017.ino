// ---------------------------------------------------------------------------
// Autodrive Version 2.4
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Servo.h>
#include <SharpIR.h>

#define TRIGGER_PIN1  46  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     47  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2  48  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     49  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN3  50  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN3     51  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN4  52  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN4     53  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 90 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define RMotorSpeedPin 7
#define LMotorSpeedPin 4
#define RMotorDirA 6  //A is 1,4 and B is 2,3
#define RMotorDirB 5
#define LMotorDirA 3
#define LMotorDirB 2
#define ServoPin 8
#define irL A9                //Left
#define irR A12               //Right
#define model 20150


Servo myservo;

NewPing sonar1(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar4(TRIGGER_PIN4, ECHO_PIN4, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

SharpIR SharpIR_L(irL, model);
SharpIR SharpIR_R(irR, model);

unsigned long RightSensor,FRSensor,FLSensor,LeftSensor;
int pos = 30;

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.

  myservo.attach(8);  // attaches the servo on pin 9 to the servo object 
   myservo.write(65);

  analogWrite(RMotorSpeedPin,120);
  analogWrite(LMotorSpeedPin,120);
   ForwardDirectionSet();

  pinMode(RMotorDirA, OUTPUT);
  pinMode(RMotorDirB, OUTPUT);
  pinMode(LMotorDirA, OUTPUT);
  pinMode(LMotorDirB, OUTPUT);
  pinMode(LMotorSpeedPin, OUTPUT);
  pinMode(RMotorSpeedPin, OUTPUT);  
}

void loop() {
                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("A: ");
  LeftSensor=sonar1.convert_cm(sonar1.ping_median(1));
  Serial.print(LeftSensor); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("cm   ");
  
  Serial.print("B: ");
  FLSensor=sonar2.convert_cm(sonar2.ping_median(1));
  Serial.print(FLSensor); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("cm   ");
  
  Serial.print("C: ");
  FRSensor=sonar3.convert_cm(sonar3.ping_median(1));
  Serial.print(FRSensor); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("cm   ");
  
  Serial.print("D: ");
  RightSensor=sonar4.convert_cm(sonar4.ping_median(1));
  Serial.print(RightSensor); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.print("cm   ");

  unsigned int disL=SharpIR_L.distance();  // this returns the distance to the object you're measuring
  unsigned int disR=SharpIR_R.distance();  // this returns the distance to the object you're measuring
 
  if (disL>120){
    disL=120;
  }
  else if(disL>=0 && disL<17){
    disL=0;
  }
  if (disR>120){
    disR=120;
  }
  else if(disR>=0 && disR<17){
    disR=0;
  }
  
  Serial.print("IR Disr L: ");  // returns it to the serial monitor
  Serial.print(disL);
  Serial.print("   IR Disr R: ");  // returns it to the serial monitor
  Serial.println(disR);

if (RightSensor<=45 && RightSensor>2){
  SteerLeftS();
 }
if (LeftSensor<=45 && LeftSensor>2){
  SteerRightS();
 } 
if ((FLSensor<65 && FLSensor!=0) && (FRSensor<65 && FRSensor!=0)){
  //SteerRight();
  StopSet();
  //BackwardDirectionSet();
  //SteerLeft();
  //delay(300);
  //ForwardDirectionSet();
 }
 /*if (FRSensor<65 && FRSensor!=0){
  SteerLeft();
  //StopSet();
  //BackwardDirectionSet();
  //SteerRight();
  //delay(500);
  //ForwardDirectionSet();
 }*/
 /*
 if (FRSensor<40 && FLSensor<40 && FLSensor!=0 && FRSensor!=0){
  StopSet();
  BackwardDirectionSet();
  SteerRight();
  delay(400);
  ForwardDirectionSet();
 }
 */
 
if (disL<51){
  SteerRight();
}
if (disR<51){
  SteerLeft();
}
}

void ForwardDirectionSet(){//A is 1,4 and B is 2,3
digitalWrite(RMotorDirA,LOW);
digitalWrite(RMotorDirB,HIGH);
digitalWrite(LMotorDirA,LOW);
digitalWrite(LMotorDirB,HIGH);
}

void BackwardDirectionSet(){//A is 1,4 and B is 2,3
digitalWrite(RMotorDirA,HIGH);
digitalWrite(RMotorDirB,LOW);
digitalWrite(LMotorDirA,HIGH);
digitalWrite(LMotorDirB,LOW);
}

void StopSet(){//A is 1,4 and B is 2,3
digitalWrite(RMotorDirA,HIGH);
digitalWrite(RMotorDirB,HIGH);
digitalWrite(LMotorDirA,HIGH);
digitalWrite(LMotorDirB,HIGH);
}

void SteerRight(){//A is 1,4 and B is 2,3
for(pos = 65; pos >= 35; pos-=1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
  delay(120);
  for(pos = 35; pos<=65; pos+=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10); 
  }
}

void SteerLeft(){//A is 1,4 and B is 2,3
 for(pos = 65; pos <= 95; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10);                       // waits 15ms for the servo to reach the position 
  } 
  delay(120);
  for(pos = 95; pos>=65; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(10); 
  }
}

void SteerRightS(){//A is 1,4 and B is 2,3
for(pos = 65; pos >= 35; pos-=1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(8);                       // waits 15ms for the servo to reach the position 
  } 
  delay(30);
  for(pos = 35; pos<=65; pos+=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(8); 
  }
}

void SteerLeftS(){//A is 1,4 and B is 2,3
 for(pos = 65; pos <= 95; pos += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(8);                       // waits 15ms for the servo to reach the position 
  } 
  delay(30);
  for(pos = 95; pos>=65; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(8); 
  }
}
