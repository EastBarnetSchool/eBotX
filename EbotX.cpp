#include "EbotX.h"
#include "Arduino.h"

//Setup Motor A
const int motorA_enable = 3;
const int motorA_pin1 = 4;
const int motorA_pin2 = 5;
const int motorA_enc = 0;

//Setup Motor B
const int motorB_enable = 6;
const int motorB_pin1 = 7;
const int motorB_pin2 = 8;
const int motorB_enc = 1;

//Setup ounting Stuff
int rotACount = 0;
int rotALast = 0;
int rotBCount = 0;
int rotBLast = 0;


//Setup SR04
const int SR04_Trig = 9;
const int SR04_Echo = 10;

//Setup Switch
const int switch_pin = 5;


//------ Motor Control ------

//Motor constructor
Motor::Motor(char motor){
	pinMode(motorA_enable, OUTPUT);
	pinMode(motorA_pin1, OUTPUT);
	pinMode(motorA_pin2, OUTPUT);

	pinMode(motorB_enable, OUTPUT);
	pinMode(motorB_pin1, OUTPUT);
	pinMode(motorB_pin2, OUTPUT);
	_motor = motor;

}

//Motor destructor
Motor::~Motor(){}

//Motor Forward
void Motor::forward(int speed){
	if (_motor == 'A'){
		analogWrite(motorA_enable, speed);
		digitalWrite(motorA_pin1, 1);
		digitalWrite(motorA_pin2, 0);
	}else if(_motor == 'B'){
		analogWrite(motorB_enable, speed);
		digitalWrite(motorB_pin1, 1);
		digitalWrite(motorB_pin2, 0);
	}
}

//Motor Reverse
void Motor::reverse(int speed){
	if (_motor == 'A'){
		analogWrite(motorA_enable, speed);
		digitalWrite(motorA_pin1, 0);
		digitalWrite(motorA_pin2, 1);
	}else if(_motor == 'B'){
		analogWrite(motorB_enable, speed);
		digitalWrite(motorB_pin1, 0);
		digitalWrite(motorB_pin2, 1);
	}
}




//Motor Stop
void Motor::stop(){
	if (_motor == 'A'){
		analogWrite(motorA_enable, 0);
		digitalWrite(motorA_pin1, 0);
		digitalWrite(motorA_pin2, 0);
	}else if(_motor == 'B'){
		analogWrite(motorB_enable, 0);
		digitalWrite(motorB_pin1, 0);
		digitalWrite(motorB_pin2, 0);
	}
}


void Motor::resetDistance(){
	if (_motor == 'A'){
		rotACount = 0;
	}else if(_motor == 'B'){
		rotBCount = 0;
	}
}


int Motor::checker(){
	if (_motor == 'A'){
		int sensorValueA = analogRead(7);
		if(sensorValueA <= 300){
		  return 0;
		}else{
		return 1;
		}
	}else if(_motor == 'B'){
		int sensorValueB = analogRead(0);
		if(sensorValueB <= 300){
		  return 0;
		}else{
		return 1;
		}
	}
}

int Motor::distance(){
	if (_motor == 'A'){
		if(Motor::checker() != rotALast){
			rotALast = Motor::checker();
		
			if(rotALast == 1){
			  rotACount++;
			  Serial.println(rotACount);
			}
		}
		return rotACount;
	}else if(_motor == 'B'){
		if(Motor::checker() != rotBLast){
			rotBLast = Motor::checker();
		
			if(rotBLast == 1){
			  rotBCount++;
			  Serial.println(rotBCount);
			}
		}
		return rotACount;
	}
}











// ------ SR04 Contorol ------

//SR04 Constructor
DistanceSensor::DistanceSensor(){
	pinMode(SR04_Trig, OUTPUT);
	pinMode(SR04_Echo, INPUT);
}

//DistanceSensor destructor
DistanceSensor::~DistanceSensor(){}

//DistanceSensor Read
long DistanceSensor::read(){
	digitalWrite(SR04_Trig, LOW);
	delayMicroseconds(2);
	digitalWrite(SR04_Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(SR04_Trig, LOW);
	duration = pulseIn(SR04_Echo, HIGH);
	distance = (duration/2) / 29.1;

	if (distance >= 200 || distance <= 0){
		return 250;
	} else {
		return distance;
	}
}





// ------ Microswitch Control ------

//MicroSwitch Constructor
MicroSwitch::MicroSwitch(){
}

//MicroSwitchdestructor
MicroSwitch::~MicroSwitch(){}

//MicroSwitch Read
boolean MicroSwitch::read(){
	value = analogRead(switch_pin);
	
	if (value > 1000){
		return 1;
	} else {
		return 0;
	}
}





// ------ LED Control ------

//LED Constructor
LED::LED( int led){
	LED_pin = led;
	pinMode(LED_pin, OUTPUT);
}

//LED Destructor
LED::~LED(){}

//LED On
void LED::on(){
	digitalWrite(LED_pin, HIGH);
}

//LED Off
void LED::off(){
	digitalWrite(LED_pin, LOW);
}

//LED Blink
void LED::blink(){
	digitalWrite(LED_pin, LOW);
	delay(1000);
	digitalWrite(LED_pin, HIGH);
	delay(1000);
}

//LED Blink Cust
void LED::blink(int delay_seconds){
	digitalWrite(LED_pin, LOW);
	delay(delay_seconds*1000);
	digitalWrite(LED_pin, HIGH);
	delay(delay_seconds*1000);
}