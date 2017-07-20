#include <Servo.h>

#define trigPin1 46
#define echoPin1 47
#define trigPin2 48
#define echoPin2 49
#define trigPin3 50
#define echoPin3 51
#define trigPin4 52
#define echoPin4 53
#define RMotorSpeedPin 7
#define LMotorSpeedPin 4
#define RMotorDirA 6
#define RMotorDirB 5
#define LMotorDirA 3
#define LMotorDirB 2
#define ServoPin 8

Servo myservo;

long duration, distance, RightSensor,FRSensor,FLSensor,LeftSensor;
int pos = 30;
int i=1;

void setup()
{
Serial.begin (9600);

myservo.attach(8);  // attaches the servo on pin 9 to the servo object 
myservo.write(65);

analogWrite(RMotorSpeedPin,120);
analogWrite(LMotorSpeedPin,120);
ForwardDirectionSet();

pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);
pinMode(trigPin4, OUTPUT);
pinMode(echoPin4, INPUT);

pinMode(RMotorDirA, OUTPUT);
pinMode(RMotorDirB, OUTPUT);
pinMode(LMotorDirA, OUTPUT);
pinMode(LMotorDirB, OUTPUT);
pinMode(LMotorSpeedPin, OUTPUT);
pinMode(RMotorSpeedPin, OUTPUT);
}

void loop() {
SonarSensor(trigPin1, echoPin1);
RightSensor = distance;
SonarSensor(trigPin2, echoPin2);
FRSensor = distance;
SonarSensor(trigPin3, echoPin3);
FLSensor = distance;
SonarSensor(trigPin4, echoPin4);
LeftSensor = distance;

Serial.print(RightSensor);
Serial.print(" - ");
Serial.print(FRSensor);
Serial.print(" - ");
Serial.print(FLSensor);
Serial.print(" - ");
Serial.println(LeftSensor);

if ((RightSensor<65 && RightSensor>25) || (RightSensor>=2 && RightSensor<12)){
  SteerLeft();
 }
if ((LeftSensor<65 && LeftSensor>25) || (LeftSensor>=2 && LeftSensor<12)){
  SteerRight();
 }
if (FLSensor<50){
  SteerRight();
  //StopSet();
  //BackwardDirectionSet();
  //SteerLeft();
  //delay(300);
  //ForwardDirectionSet();
 }
 if (FRSensor<50){
  SteerLeft();
  //StopSet();
  //BackwardDirectionSet();
  //SteerRight();
  //delay(500);
  //ForwardDirectionSet();
 }
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH, 37000);
distance = (duration/2) / 29.1;
if (distance>300 || distance==0)
distance=300;
else 
distance=distance;
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

void SteerLeft(){//A is 1,4 and B is 2,3
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

void SteerRight(){//A is 1,4 and B is 2,3
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
