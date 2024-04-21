# iTCLab Testing

iTCLab_Testing is a simple iTCLab Kit testing program. The temperature is gradually increased to the desired upper limit of 55 degrees Celsius.
<br>
</br>

<p align="center">
  <img src="https://github.com/bsrahmat/itclab-01/blob/main/itclab01a.jpg" alt="" class="img-responsive" width="700">
</p>

## About these iTCLab kits :

iTCLab - Internet-Based Temperature Control Lab. Temperature control kit for feedback control applications with an ESP32 Microcontroller, LED, two heaters, and two temperature sensors. The heating power output is adjusted to maintain the desired temperature setpoint. Heat energy from the heater is transferred by conduction, convection, and radiation to the temperature sensor. Heat is also transferred from the device to the environment.

### More about iTCLab:

- It is inspired by <a href="https://apmonitor.com/pdc/index.php/Main/ArduinoTemperatureControl" target="_blank">The TCLab Product of Brigham Young University (BYU), one of the private campuses in Provo, Utah, United States of America.</a>
- Miniature Control System in a Pocket.
- Practical IoT Learning Package Tools.
- IoT programming Kits.
- IoT-Based Control System Practice Devices.
- It can be used to learn System Dynamics and Control Systems.
- It can be used to learn Arduino and Python programming.
- It can be used to learn AI and Machine Learning Programming.
- And others.

The fundamental difference between iTCLab and BYU's TCLab product is the replacement of the Arduino Uno microcontroller with the ESP32. By using the ESP32, iTCLab has the ability to connect to the Internet of Things (IoT).
<br>
</br>

## iTCLab Upper Temperature Limit Description:

The upper temperature limit of the iTCLab Kit is 60 degrees Celsius. Therefore, when experimenting with this Kit, this Upper Temperature Limit must not be exceeded. Violation of this provision could cause damage (burning) to the components.

Although the upper limit is 60 degrees Celsius, it is still sufficient for experimenting with this Kit. And it is sufficient to see the performance of a control method. For example, control using Proportional Integral and Derivative (PID). Or to see the effect of tuning the PID parameters using the Machine Learning method. An illustration of the capabilities of this iTCLab Kit can be seen from the illustration of the performance of the BYU TCLab, as seen in the following simulation.

<p align="center">
  <img src="https://github.com/bsrahmat/itclab-01/blob/main/pid_control.gif" alt="" class="img-responsive" width="700">
</p>

## Coding Upper Temperature Limit

It is necessary to set a limit so that the iTCLab Kit always operates in a safe area. It must not exceed the upper limit of 60 degrees Celsius. The following is an example of an Arduino program script that must be added every time you experiment with this Kit. In the Loop, it is added that if it reaches the specified upper limit (it can be lowered slightly, for example 55 degrees Celsius), then the heater must be turned off.

```
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

```
<br>
</br>

## iTCLab_Testing Program

iTCLab_Testing is a simple iTCLab Kit testing program. The temperature is gradually increased to the desired upper limit of 55 degrees Celsius.
<br>
</br>

## Required Equipment:

- <a href="https://shopee.co.id/product/78709625/11589970517/" target="_blank">iTCLab Kit</a>

- <a href="https://github.com/bsrahmat/itclab-01/blob/main/iTCLab_Testing.ino" target="_blank">iTCLab_Testing.ino Program</a>

- <a href="https://github.com/bsrahmat/itclab-01/blob/main/iTCLab_Testing.pdf" target="_blank">iTCLab_Testing.pdf Tutorial</a>


### Another alternative is to download the tutorial:

- <a href="https://www.academia.edu/115795927" target="_blank">https://www.academia.edu/115795927</a>

- <a href="https://www.researchgate.net/publication/378898855" target="_blank">https://www.researchgate.net/publication/378898855</a>

<br>
</br>

### Here is the complete coding for iTCLab_Testing:

```
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

```

<br>
</br>

An example of the test results is shown in the following figure.


<p align="center">
  <img src="https://github.com/bsrahmat/itclab-01/blob/main/iTCLab_Test1.png" alt="" class="img-responsive" width="700">
</p>

<br>
</br>

If the power adapter is connected to electricity, the measured temperature will go towards the upper limit:

<p align="center">
  <img src="https://github.com/bsrahmat/itclab-01/blob/main/iTCLab_Test2.png" alt="" class="img-responsive" width="700">
</p>

<br>
</br>

## An example of a publication related to this Kits:

| Num  | iTCLab Publication Articles                                                                                                                                                     | Download BibTex Citation                                                                 |
| -----|---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|
|  01  |<a href="https://www.researchgate.net/publication/368801589">iTCLab Temperature Monitoring and Control System Based on PID and Internet of Things (IoT)</a>                      | [Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_iTCLab01.bib) |
|  02  |<a href="https://www.researchgate.net/publication/378937580">Temperature Monitoring via the Internet of Things Using PID-iTCLab</a>                                              | [Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_iTCLab02.bib) |
|  03  |<a href="https://www.researchgate.net/publication/378938102">On/Off Temperature Monitoring and Control via the Internet of Things Using iTCLab Kit</a>                           | [Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_iTCLab03.bib) |
|  04  |<a href="https://ieeexplore.ieee.org/document/10420130">ITCLab PID Control Tuning Using Deep Learning</a>                                                                        | [Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas01.bib)    |
<br>
</br>

## Scopus Publications:

| Num  | Scopus Publication Articles                                                                                                                                                      | Download BibTex Citation                                                                    |
| -----|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------|
|  01  |<a href="https://www.researchgate.net/publication/312337382">VLP Image Segmentation System Using Cellular Neural Network Optimized by Adaptive fuzzy & NFA</a>                    | [Rahmat et al. (2016)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas10.bib)       |
|  02  |<a href="https://www.researchgate.net/publication/313218211">Designing Intelligent Fishcarelab System (IFS) as Modern Koi Fish Farming System</a>                                 | [Rahmat et al. (2017)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas09.bib)       |
|  03  |<a href="https://www.researchgate.net/publication/332119322">An Improved Mean Shift Performance Using Switching Kernels for Indonesia VLP Tracking Video</a>                      | [Rahmat et al. (2018)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas08.bib)       |
|  04  |<a href="https://www.researchgate.net/publication/327382646">An Improved Mean Shift Using Adaptive Fuzzy Gaussian Kernel for Indonesia VLP Tracking</a>                           | [Rahmat et al. (2018)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas07.bib)       |
|  05  |<a href="https://www.researchgate.net/publication/349517987">Comparison of B-Value Predictions as Earthquake Precursors using ELM and Deep Learning</a>                           | [Rahmat et al. (2020)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas06.bib)       |
|  06  |<a href="https://www.researchgate.net/publication/343186219">Video-based Tancho Koi Fish Tracking System Using CSK, DFT, and LOT</a>                                              | [Rahmat et al. (2020)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas05.bib)       |
|  07  |<a href="https://ieeexplore.ieee.org/document/9321094">Combining of extraction butterfly image using color, texture and form features</a>                                         | [Dhian,Rahmat et al. (2020)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas17.bib) |
|  08  |<a href="https://www.researchgate.net/publication/350296152">Video-Based Container Tracking System Using Deep Learning</a>                                                        | [Rahmat et al. (2021)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas04.bib)       |
|  09  |<a href="https://www.researchgate.net/publication/356806533">ELM-Based Indonesia Vehicle License Plate Recognition System</a>                                                     | [Rahmat et al. (2021)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas03.bib)       |
|  10  |<a href="https://ieeexplore.ieee.org/document/10010310">Indonesia's Open Unemployment Rate Prediction System Using Deep Learning</a>                                              | [Rahmat et al. (2022)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas02.bib)       |
|  11  |<a href="https://www.engineeringletters.com/issues_v30/issue_3/EL_30_3_16.pdf">Performance of Optimized CSK, DFT, and LOT for Video-based Container Tracking System using SA</a>  | [Endra,Rahmat et al. (2022)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas16.bib) |
|  12  |<a href="https://ieeexplore.ieee.org/document/10010285">Poor Population Classification System Using Convolutional Neural Network</a>                                              | [Suaib,Rahmat et al. (2022)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas15.bib) |
|  13  |<a href="https://internetworkingindonesia.org/Issues/Vol14-No2-2022/iij_vol14_no2_2022_halim.pdf">Poverty Prediction System on Indonesian Population Using Deep Learning</a>      | [Suaib,Rahmat et al. (2022)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas14.bib) |
|  14  |<a href="https://ieeexplore.ieee.org/document/10420130">ITCLab PID Control Tuning Using Deep Learning</a>                                                                         | [Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas01.bib)       |
|  15  |<a href="https://ieeexplore.ieee.org/document/10420364/">CFD Simulation of the Effect of Adding a Sludge Zone to the Sequencing Batch Reactor for Fluid Turbulence</a>            | [Novi, Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas13.bib) |
|  16  |<a href="https://ieeexplore.ieee.org/document/10420129/">Detect Areas of Upward and Downward Fluctuations in Bitcoin Prices Using Patterned Datasets</a>                          | [Rizky,Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas12.bib) |
|  17  |<a href="https://ieeexplore.ieee.org/document/10419873">The Impact of Message Replication on VDTN Spray Protocol for Smart City</a>                                               | [Agus, Rahmat et al. (2023)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas11.bib) |
|  18  |<a href="https://joiv.org/index.php/joiv/article/view/1543">Minimum, Maximum, and Average Implementation of Patterned Datasets in Mapping Cryptocurrency Fluctuation Patterns</a> | [Rizky,Rahmat et al. (2024)](https://github.com/bsrahmat/itclab-01/blob/main/bib_bas18.bib) |

<br>
</br>

## Books Publications:

| Num  | Books Publication Articles                                                                                                                              | Download BibTex Citation                                                                        |
| -----|---------------------------------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------|
|  01  |<a href="https://github.com/bsrahmat/ebook-01">Fuzzy and Artificial Neural Networks Programming for Intelligent Control Systems (Indonesian version)</a> | [Rahmat et al. (2019)](https://github.com/bsrahmat/ebook-01/blob/main/EBook01_Fuzzy_JST.bib)    |
|  02  |<a href="https://github.com/bsrahmat/ebook-02">Intelligent Robot Programming Using Arduino (Indonesian version)</a>                                      | [Rahmat et al. (2020)](https://github.com/bsrahmat/ebook-02/blob/main/EBook02_Kinect_Robot.bib) |
|  03  |<a href="https://github.com/bsrahmat/ebook-03">Deep Learning Programming Using Python (Indonesian version)</a>                                           | [Rahmat et al. (2021)](https://github.com/bsrahmat/ebook-03/blob/main/EBook03_DL.bib)           |
|  04  |<a href="https://github.com/bsrahmat/ebook-04">MQTT Brokers as Supporting IoT Services (Indonesian version)</a>                                          | [Rahmat et al. (2022)](https://github.com/bsrahmat/ebook-04/blob/main/EBook04_MQTT_Broker.bib)  |
|  05  |<a href="https://github.com/bsrahmat/ebook-05">Integrated Web-Based E-Finance System (Indonesian version)</a>                                            | [Rahmat et al. (2023)](https://github.com/bsrahmat/ebook-05/blob/main/EBook05_EFinance.bib)     |
|  06  |<a href="https://github.com/bsrahmat/ebook-06">Asset Management Information System (Indonesian version)</a>                                              | [Rahmat et al. (2023)](https://github.com/bsrahmat/ebook-06/blob/main/EBook06_Simaset.bib)      |
|  07  |<a href="https://github.com/bsrahmat/ebook-07">Village Management Information System (Indonesian version)</a>                                            | [Rahmat et al. (2023)](https://github.com/bsrahmat/ebook-07/blob/main/EBook07_Simdes.bib)       |
|  08  |<a href="https://github.com/bsrahmat/ebook-08">Retribution Management Information System (Indonesian version)</a>                                        | [Rahmat et al. (2023)](https://github.com/bsrahmat/ebook-08/blob/main/EBook08_Simretribusi.bib) |
|  09  |<a href="https://github.com/bsrahmat/ebook-09">Gender Management Information System (Indonesian version)</a>                                             | [Rahmat et al. (2023)](https://github.com/bsrahmat/ebook-09/blob/main/EBook09_Sagada.bib)       |

<br></br>

## Other publications by the researcher:

https://fitri.academia.edu/BasukiRahmat

https://www.researchgate.net/profile/Basuki-Rahmat-2

https://scholar.google.com/citations?user=BjCi4AgAAAAJ&hl=en

<br>
</br>

## Buy the iTCLab Kits at Shopee:

<p align="center">
<a href="https://shopee.co.id/product/78709625/11589970517" target="_blank"><img src="https://github.com/bsrahmat/itclab-01/blob/main/shopee_kit1.jpg" alt="" class="img-responsive" width="700">
</a>
</p>
<br>
</br>

## Other research by the IO-T.Net research team can be found at:

https://www.io-t.net/

<p align="center">
<a href="https://www.io-t.net/" target="_blank"><img src="https://github.com/bsrahmat/robot-bnu/blob/main/iot.png" alt="" class="img-responsive" width="500">
</a>
</p>

<br>
</br>

## Other research by the I-OT.Net research team can be found also at:

https://www.i-ot.net/

<p align="center">
<a href="https://www.i-ot.net/" target="_blank"><img src="https://github.com/bsrahmat/fuzzy-neural/blob/main/iot_logo.png" alt="" class="img-responsive" width="500">
</a>
</p>

