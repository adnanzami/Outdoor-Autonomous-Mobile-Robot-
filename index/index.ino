#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 2 RX. 
// Connect the HC-05 RX to Arduino pin 3 TX through a voltage divider.
//Motor Driver inputs
char c = ' ';
const int in_4 = 9 ;
const int in_5 = 5;
const int in_6 = 6;
const int in_7 = 10;
//IR Sensor
int sensor_1 = 0;     //initialize sensor_1
int sensor_2 = 0;     //initialize sensor_2

int ir_level = 300;   //IR sensor level
int turn_rate = 220;  //Reverse and turn rate
//PIR Sensor
int ledPin = 13;                // choose the pin for the LED
int inputPin = 8;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino is ready");
    pinMode(in_4,OUTPUT) ;  //Logic pins are also set as output
    pinMode(in_5,OUTPUT) ;
    pinMode(in_6,OUTPUT);
    pinMode(in_7,OUTPUT);
    pinMode(c, INPUT);
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
    BTserial.begin(9600);  
}
void loop()
{
    // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.println(c);
       
       if ( c == '0') //STOP
    {   
      digitalWrite(in_4,LOW) ;//motor1 input 1
      digitalWrite(in_5,LOW) ;//motor1 input 2
      digitalWrite(in_6,LOW) ;//motor2 input 1
      digitalWrite(in_7,LOW) ;//motor2 input 2
      } 
    if ( c == '2')  //BACKWARD
    { 
     for ( int pwm = 0 ; pwm < 255; pwm++){
      digitalWrite(in_4,LOW) ; //motor1 input 1
      analogWrite(in_5,pwm) ; //motor1 input 2
      digitalWrite(in_6,LOW) ; //motor2 input 1
      analogWrite(in_7,pwm) ; //motor2 input 2
      delay(1);
      }
    }
    
    if ( c == '1') //FORWARD
    {  for ( int pwm = 0 ; pwm < 255; pwm++){
      analogWrite(in_4,pwm) ; //motor1 input 1
      digitalWrite(in_5,LOW) ; //motor1 input 2
      analogWrite(in_6,pwm) ; //motor2 input 1
      digitalWrite(in_7,LOW) ; //motor2 input 2
      delay(1);
    }
    }
    
     if ( c == '3') //TURN LEFT
    {  for (  int pwm = 0 ; pwm < 255; pwm++){
      analogWrite(in_4,pwm) ;  //motor1 input 1
      digitalWrite(in_5,LOW) ; //motor1 input 2
      digitalWrite(in_6,LOW) ; //motor2 input 1
      digitalWrite(in_7,LOW) ; //motor2 input 2
      delay(1);
      }
    }
    
     if ( c == '4') //TURN RIGHT
    { for (int pwm = 0 ; pwm < 255; pwm++){
      digitalWrite(in_4,LOW) ;  //motor1 input 1
      digitalWrite(in_5,LOW) ;  //motor1 input 2
      analogWrite(in_6,pwm) ;   //motor2 input 1
      digitalWrite(in_7,LOW) ;  //motor2 input 2
      delay(1); 
      }
    }

//AUTONOMOUS 
    while ( c == 'a'){ //Autonomous using IR sensor
      
     sensor_1 = analogRead(A0);   //Sensor connection to the arduino
   sensor_2 = analogRead(A1); //Sensor connection to the Arduino

//PIR Sensor
val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
     (ledPin, HIGH);  // turn LED ON
      digitalWrite(in_4,LOW) ;//motor1 input 1    //Stop car
      digitalWrite(in_5,LOW) ;//motor1 input 2
      digitalWrite(in_6,LOW) ;//motor2 input 1
      digitalWrite(in_7,LOW) ;//motor2 input 2
    delay(1000);
  }
  digitalWrite(ledPin, LOW);
  delay(5000);      
  if ((sensor_1 < ir_level) || (sensor_2 < ir_level)){
    for ( int pwm = turn_rate  ; pwm > 0; pwm--){ //REVERSE
      digitalWrite(in_4,LOW) ; //motor1 input 1
      analogWrite(in_5,pwm) ; //motor1 input 2
      digitalWrite(in_6,LOW) ; //motor2 input 1
      analogWrite(in_7,pwm) ; //motor2 input 2
       delay(5);
      }
      delay(250);
      
      for ( int pwm = turn_rate ; pwm > 0; pwm--){ //Turn left
      digitalWrite(in_4,LOW) ; //motor1 input 1
      digitalWrite(in_5,LOW) ; //motor1 input 2
      digitalWrite(in_6,LOW) ; //motor2 input 1
      analogWrite(in_7,pwm) ; //motor2 input 2 
       delay(5);
      }
       delay (250);
  }
  else if ((sensor_1 < ir_level) && (sensor_2 < ir_level)){
    for ( int pwm = turn_rate  ; pwm > 0; pwm--){ //REVERSE
      digitalWrite(in_4,LOW) ; //motor1 input 1
      analogWrite(in_5,pwm) ; //motor1 input 2
      digitalWrite(in_6,LOW) ; //motor2 input 1
      analogWrite(in_7,pwm) ; //motor2 input 2
      delay(5);
      }
      
      delay(250);
      
      for ( int pwm = turn_rate ; pwm > 0; pwm--){ //Turn left
      digitalWrite(in_4,LOW) ; //motor1 input 1
      digitalWrite(in_5,LOW) ; //motor1 input 2
      digitalWrite(in_6,LOW) ; //motor2 input 1
      analogWrite(in_7,pwm) ; //motor2 input 2
      delay(5);
      }
      
      delay (250);
  }
  
  else    {
      analogWrite(in_4,100) ; //motor1 input 1
      digitalWrite(in_5,LOW) ; //motor1 input 2
      analogWrite(in_6,100) ; //motor2 input 1
      digitalWrite(in_7,LOW) ; //motor2 input 2
  }
} //End of Autonomous
 
      } //End of Bluetooth
    }//End of Loop

