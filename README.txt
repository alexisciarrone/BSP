{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf460
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\paperw11900\paperh16840\margl1440\margr1440\vieww25400\viewh14500\viewkind0
\pard\tx566\tx1133\tx1700\tx2267\tx2834\tx3401\tx3968\tx4535\tx5102\tx5669\tx6236\tx6803\sl360\slmult1\pardirnatural\partightenfactor0

\f0\b\fs20 \cf0 \ul \ulc0 Bachelor Semester Project I - Smart Permaculture Garden\

\b0 \ulnone \

\b \ul Project description\

\b0 \ulnone The aim of the project is to create a smart indoor garden, by programming an Arduino with its sensors. All the information (this README, the code, the libraries) are located on the Github page : {\field{\*\fldinst{HYPERLINK "https://github.com/alexisciarrone/BSP"}}{\fldrslt https://github.com/alexisciarrone/BSP}}\
\

\b \ul Software\

\b0 \ulnone To be able to realize to project, you first need to download the Arduino IDE ({\field{\*\fldinst{HYPERLINK "https://www.arduino.cc/en/Main/Software"}}{\fldrslt https://www.arduino.cc/en/Main/Software}}) and follow the process depending on your operating system (Windows, macOS or Linux). Note that the Arduino language is based on C and C++.\
To use the sensors you then need the following libraries (posted on this Github page) :\
- Adafruit_TSL2561-master ({\field{\*\fldinst{HYPERLINK "https://github.com/alexiscrrn/BSP/tree/master/Adafruit_TSL2561-master"}}{\fldrslt https://github.com/alexiscrrn/BSP/tree/master/Adafruit_TSL2561-master}})\
- Adafruit_Unified_Sensor-1.0.2 ({\field{\*\fldinst{HYPERLINK "https://github.com/alexiscrrn/BSP/tree/master/Adafruit_Unified_Sensor-1.0.2"}}{\fldrslt https://github.com/alexiscrrn/BSP/tree/master/Adafruit_Unified_Sensor-1.0.2}})\
- DHT_sensor_library-1.3.0 ({\field{\*\fldinst{HYPERLINK "https://github.com/alexiscrrn/BSP/tree/master/DHT_sensor_library-1.3.0"}}{\fldrslt https://github.com/alexiscrrn/BSP/tree/master/DHT_sensor_library-1.3.0}})\
- LiquidCrystal ({\field{\*\fldinst{HYPERLINK "https://github.com/alexiscrrn/BSP/tree/master/LiquidCrystal"}}{\fldrslt https://github.com/alexiscrrn/BSP/tree/master/LiquidCrystal}})\
\
These libraries need to be placed on the libraries folder in your Arduino folder.\
\
The code used is named BSP.ino ({\field{\*\fldinst{HYPERLINK "https://github.com/alexisciarrone/BSP/blob/master/BSP.ino"}}{\fldrslt https://github.com/alexisciarrone/BSP/blob/master/BSP.ino}}).\
\

\b \ul Hardware
\b0 \ulnone \
For the project I\'92ve used 3 sensors :\
- DHT22 temperature & humidity sensor\
- Soil moisture sensor\
- TSL2561 ambient light sensor\
\
A peristaltic pump (DC motor) was used with a 12V power supply. You need to use the Arduino Motor Shield (or equivalent) to make the motor work.\
\
On the board and the motor shield, the following pins are used :\
- 3.3V (to TSL2561)\
- 5V\
- both GND (one of which to TSL2561)\
- A3 (to Soil moisture sensor)\
- A4 (to TSL2561)\
- A5 (to TSL2561)\
- 2, 4, 5, 6, 7, 8 (to LCD)\
- 10 (to DHT22)\
- 13 (to the positive side of the LED)\
- GND (to the negative side of the LED)\
- + and - (motor shield to the pump)\
- Vin and GND (motor shield to the 12V power supply)\
\
Moreover, 3 220-ohm resistors and a 4.7k-ohm resistor were used.\
\
}