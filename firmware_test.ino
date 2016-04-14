#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"



Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);// port M1
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);// port M2
int motorSpeed[] = {255, 150};
int motorDirection[] = {FORWARD, FORWARD};
boolean  Motor1Boolean ;
boolean Motor2Boolean ;
int Sensor0 ; // Sensor0 connected to this digital pin number
int Sensor1 ; // Sensor1 connected to this digital pin number
int Sensor2 ; // Sensor1 connected to this digital pin number
int PrevSensor0, PrevSensor1, PrevSensor2;
char inChar;


void setup() {
  // initialize things
  Motor1Boolean = false;
  Motor2Boolean = false;

  // set SENSOR pins as digital in
  Sensor0 = 5; // Sensor0 connected to this digital pin number
  Sensor1 = 6; // Sensor1 connected to this digital pin number
  Sensor2 = 7; // Sensor1 connected to this digital pin number
  pinMode(Sensor0, INPUT); // Define Sensor0 as a digital in pin
  pinMode(Sensor1, INPUT); // Define Sensor2 as a digital in pin
  pinMode(Sensor2, INPUT); // Define Sensor2 as a digital in pin

  // set MOTOR control pins as digital out
  //  int Motor1 = 8; // Sensor0 connected to this digital pin number
  //  int Motor2 = 9; // Sensor1 connected to this digital pin number
  //  pinMode(Motor1, INPUT); // Define Sensor0 as a digital in pin
  //  pinMode(Motor2, INPUT); // Define Sensor2 as a digital in pin

  // pinMode(13, OUTPUT);

  Serial.begin(9600);
  //Keyboard.begin();

  //initial motor speed
  initializeShield();
  PrevSensor0 = readSensor(Sensor0);//HIGH;
  PrevSensor1 = readSensor(Sensor1);//LOW;
  PrevSensor2 = readSensor(Sensor2);


}

// the loop function runs over and over again forever
void loop() {
//  if (Serial.available() > 0) {
//    inChar = Serial.read();
//    Serial.print("You sent me: \'");
//    Serial.write(inChar);
//    Serial.println("");
//    Serial.println("Prev0="+ PrevSensor0);// + " Prev1="+PrevSensor0+" prev2="+PrevSensor2);
//    
//  }


  if (PrevSensor0 == HIGH && readSensor(Sensor0) == LOW) // if hole
  {

    PrevSensor0 = readSensor(Sensor0);
    Motor1Boolean = true;
    Motor2Boolean = true;

    moveMotor(myMotor1, FORWARD); // move Motor1
    moveMotor(myMotor2, FORWARD); // move Motor2
    delay(10);
  }

  if ( Motor1Boolean == true)
  {
    if (PrevSensor1 == LOW && readSensor(Sensor1) == HIGH) // if hole
    {
      Motor1Boolean = false;
      stopMotor(myMotor1); // stop Motor1
    }
  }

  if ( Motor2Boolean == true)
  {
    if (PrevSensor2 == LOW && readSensor(Sensor2) == HIGH) // if hole
    {
      Motor2Boolean = false;
      stopMotor(myMotor2); // stop Motor2
    }
  }
}
int readSensor(int sensor) {
//  int highOrLow;
//  switch (inChar) {
//    case 'u':
//      // move mouse up
//      highOrLow = HIGH;
//      break;
//    case 'd':
//      // move mouse down
//      highOrLow = LOW;
//      break;
//  }
//  return highOrLow;
  return digitalRead(sensor);

}
void moveMotor(Adafruit_DCMotor *myMotor, int directionFB, uint8_t speed) {
  myMotor->setSpeed(speed);
  myMotor->run(directionFB);
  delay(10);
}

void moveMotor(Adafruit_DCMotor *myMotor, int directionFB) {
  moveMotor(myMotor, directionFB, motorSpeed[0]); // this needs to be assigned to the correct motor
}

void stopMotor(Adafruit_DCMotor *myMotor) {
  myMotor->run(RELEASE);
  delay(1000);
}

void initializeShield() {
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor1->setSpeed(motorSpeed[0]);
  myMotor2->setSpeed(motorSpeed[1]);

  //myMotor->run(FORWARD);
  // turn on motor
  //myMotor->run(RELEASE);
}
void initializeMotor() {

}
