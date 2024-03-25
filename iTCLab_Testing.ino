/*********************************************************************************
 * Program   : iTCLab_Testing
 * By        : Assoc. Prof. Dr. Basuki Rahmat, S.Si, MT, ITS-AI,
 *             Assoc. Prof. Dr. Muljono, S.Si, M.Kom, et al
 * Pro. Team : i-ot.net, io-t.net
 * R. Group  : Intelligent Control, Robotics and Automation Systems Research Group
 * Univ.     : Universitas Pembangunan Nasional "Veteran" Jawa Timur
 * Country   : Indonesia
 *********************************************************************************/
 
#include <Arduino.h>

// constants
const int baud = 115200;       // serial baud rate

// pin numbers corresponding to signals on the iTCLab Shield
const int pinT1   = 34;         // T1
const int pinT2   = 35;         // T2
const int pinQ1   = 32;         // Q1
const int pinQ2   = 33;         // Q2
const int pinLED  = 26;         // LED

// setting PWM properties
const int freq = 5000; //5000
const int ledChannel = 0;
const int Q1Channel = 1;
const int Q2Channel = 2;
const int resolutionLedChannel = 8; //Resolution 8, 10, 12, 15
const int resolutionQ1Channel = 8; //Resolution 8, 10, 12, 15
const int resolutionQ2Channel = 8; //Resolution 8, 10, 12, 15

float cel, cel1, degC, degC1;
const float upper_temperature_limit = 55;

// global variables
float Q1 = 0;                 // value written to Q1 pin
float Q2 = 0;                 // value written to Q2 pin
int iwrite_max = 255;          // integer value for writing
int iwrite_min = 0;            // integer value for writing

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baud); 
  while (!Serial) {
    ; // wait for serial port to connect.
  }

  // configure pinQ1 PWM functionalitites
  ledcSetup(Q1Channel, freq, resolutionQ1Channel);
  
  // attach the channel to the pinQ1 to be controlled
  ledcAttachPin(pinQ1, Q1Channel); 

  // configure pinQ2 PWM functionalitites
  ledcSetup(Q2Channel, freq, resolutionQ2Channel);
  
  // attach the channel to the pinQ2 to be controlled
  ledcAttachPin(pinQ2, Q2Channel);   

  // configure pinLED PWM functionalitites
  ledcSetup(ledChannel, freq, resolutionLedChannel);
  
  // attach the channel to the pinLED to be controlled
  ledcAttachPin(pinLED, ledChannel); 

  ledcWrite(Q1Channel,0);
  ledcWrite(Q2Channel,0); 
  ledcWrite(ledChannel,0); 
}

void Q1on(){
    ledcWrite(Q1Channel,iwrite_max/255*100);
    //Q1 = iwrite_max/255*100;
    //Serial.println(Q1);
}

void Q1off(){
    ledcWrite(Q1Channel,iwrite_min/255*100);
    //Q1 = iwrite_min/255*100;
    //Serial.println(Q1);
}

void Q2on(){
    ledcWrite(Q2Channel,iwrite_max/255*100);
    //Q2 = iwrite_max/255*100;
    //Serial.println(Q2);
}

void Q2off(){
    ledcWrite(Q2Channel,iwrite_min/255*100);
    //Q2 = iwrite_min/255*100;
    //Serial.println(Q2);
}

void ledon(){
    ledcWrite(ledChannel,iwrite_max);
}

void ledoff(){
    ledcWrite(ledChannel,iwrite_min);
}

void cektemp(){
  degC = analogRead(pinT1) * 0.322265625 ;    // use for 3.3v AREF
  cel = degC/10;
  degC1 = analogRead(pinT2) * 0.322265625 ;    // use for 3.3v AREF
  cel1 = degC1/10;

  Serial.print("Temperature: ");
  Serial.print(cel);   // print the temperature T1 in Celsius
  Serial.print("°C");
  Serial.print("  ~  "); // separator between Celsius and Fahrenheit
  Serial.print(cel1);   // print the temperature T2 in Celsius
  Serial.println("°C");
}
void loop() {
  // put your main code here, to run repeatedly:
  cektemp();
  if (cel > upper_temperature_limit){
    Q1off();
    ledon();
  }
  else {
    Q1on();
    ledoff();
  }
  if (cel1 > upper_temperature_limit){
    Q2off();
    ledon();
  }
  else {
    Q2on();
    ledoff();
  }
  delay (100);
}
