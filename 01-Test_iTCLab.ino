/*************************************
 * Program : Pengujian Kit iTCLab 1
 * Menggunakan Kit iTCLab
 * Oleh : Tim io-t.net
 * Surabaya, 10 April 2022
 * ***********************************/

#include <Arduino.h>
#include <analogWrite.h>

#define T1       34
#define T2       35
#define LED      26
#define Q1       32
#define Q2       33

//Q1 32 - T1 34
//Q2 33 - T2 35

float cel, cel1, degC, degC1;
const float batas_suhu_atas = 55;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  analogWriteFrequency(5000); // set frequency to 10 KHz for all pins
  analogWriteResolution(LED, 10);
  analogWriteResolution(Q1, 10);
  analogWriteResolution(Q2, 10);
}

void Q1on(){
  analogWrite(Q1, 341, 5000, 10, 0); // analogwrite(pin,period,frequency,resolusi,phase)
}

void Q1off(){
  analogWrite(Q1,0);
}

void Q2on(){
  analogWrite(Q2, 341, 5000, 10, 341); // analogwrite(pin,period,frequency,resolusi,phase)
}

void Q2off(){
  analogWrite(Q2,0);
}

void ledon(){
  analogWrite(LED,255);
}

void ledoff(){
  analogWrite(LED,0);
}

void cektemp(){
  degC = analogRead(T1) * 0.322265625 ;    // use for 3.3v AREF
  cel = degC/10;
  degC1 = analogRead(T2) * 0.322265625 ;    // use for 3.3v AREF
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
  if (cel > batas_suhu_atas){
    Q1off();
    ledon();
  }
  else {
    Q1on();
    ledoff();
  }
  if (cel1 > batas_suhu_atas){
    Q2off();
    ledon();
  }
  else {
    Q2on();
    ledoff();
  }
  
  delay (100);
}
