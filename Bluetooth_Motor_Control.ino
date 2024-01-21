//  Arduino, HM-10, App Inventor 2
//
//  Example Project Part 1: Turn an LED on and off basic
//  By Martyn Currey. www.martyncurrey.com
//
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  Arduino D8 (ASS RX) - BT TX no need voltage divider 
//  Arduino D9 (ASS TX) - BT RX through a voltage divider
//  Arduino D2 - Resistor + LED
 
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
#include <AltSoftSerial.h>
AltSoftSerial ASSserial; 

char Indicator='0';

const int ControlPin1 = 2;
const int ControlPin2 = 3;
const int EnabledPin = 6;
const int DirectionSwitchPin = 4;
const int OnOffSwitchStateSwitchPin = 5;
const int PotPin = A0;

int OnOffSwitchState = 0;
int PreviousOnOffSwitchState = 0;
int DirectionSwitchState = 0;
int PreviousDirectionSwitchState = 0;

int MotorEnabled = 0;
int MotorSpeed = 0;
int MotorDirection = 1;

void setup() 
{
    pinMode(DirectionSwitchPin, INPUT);
    pinMode(OnOffSwitchStateSwitchPin, INPUT);
    pinMode(ControlPin1, OUTPUT);
    pinMode(ControlPin2, OUTPUT);
    pinMode(EnabledPin, OUTPUT);

    digitalWrite(EnabledPin, LOW);

    
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    ASSserial.begin(9600);  
    Serial.println("ASSserial started at 9600");
    Serial.println(" ");
}

 
void loop()
{     
        OnOffSwitchState = digitalRead(OnOffSwitchStateSwitchPin);
        delay(1);
        DirectionSwitchState = digitalRead(DirectionSwitchPin);

        if (OnOffSwitchState != PreviousOnOffSwitchState)
        {
            if(OnOffSwitchState == HIGH)
            {
              MotorEnabled = !MotorEnabled;  
            }
        }

        if(DirectionSwitchState != PreviousDirectionSwitchState)
        {
            if (DirectionSwitchState == HIGH)
            {
              MotorDirection = !MotorDirection;
            }  
        }

        if(MotorDirection == 1)
        {
            digitalWrite(ControlPin1, HIGH);
            digitalWrite(ControlPin2, LOW);
        }
        else
        {
            digitalWrite(ControlPin1, LOW);
            digitalWrite(ControlPin2, HIGH);            
        }

        if(MotorEnabled == 1)
        {             
            analogWrite(EnabledPin, MotorSpeed);
            MotorSpeed = 50;
        }
        else
        {
            analogWrite(EnabledPin, 0);            
        }

        PreviousDirectionSwitchState = DirectionSwitchState;
        PreviousOnOffSwitchState = OnOffSwitchState;
        
}
