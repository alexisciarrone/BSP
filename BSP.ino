//inclusion of all the libaries needed
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

#define DHTPIN 10 //pin which is connected to the DHT (moisture-temperature) sensor.
#define DHTTYPE DHT22 //we define the sensor DHT 22

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
LiquidCrystal lcd(2, 4, 5, 6, 7, 8); //we define the digital ports of the Arduino board used by the LCD display

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345); //we introduce the TSL2561 sensor

const int soilRead = A3; //moisture sensor connected to Analog pin 3
int soilMoisture = 0;

const int
PWM_A = 3, //motor's power controlled by Digital pin 3
DIR_A = 12, //motor's direction controlled by Digital pin 12
BRAKE_A = 9; //motor's braking controlled by Digital pin 9

void setup() //first part, the initialization function which only repeat once
{
    Serial.begin(9600); //opens serial port, sets data rate to 9600 bits per second
    
  //LCD :
    lcd.begin(16, 2); //we define the LCD's format : 16x2
    dht.begin(); //initialize the DHT.
    // Print temperature sensor details.
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    
    delayMS = sensor.min_delay / 1000;
   
  //MOISTURE SENSOR + MOTOR :
    pinMode(soilRead, INPUT); //sets the character soilRead (the moisture level, connected to pin A3) as input
    pinMode(BRAKE_A, OUTPUT);// sets the braking of the motor (digital pin 9) as output

  //AMBIENT LIGHT SENSOR :
    pinMode(LED_BUILTIN, OUTPUT); //we set the LED as output
  
  if(!tsl.begin()) // initialize the sensor
  {
    Serial.print("No TSL2561 detected ! Check your wiring."); //this message indicates that there was a problem detecting the TSL2561 sensor. We need to check the connections

    while(1);
  }
    Serial.println(""); //skip a line    
}

void loop() //second part, the main function that loops consecutively
{
//LCD + DHT :    
  //Delay between measurements.
    delay(delayMS);
    
  //Get temperature event and print its value.
    sensors_event_t event; 
    dht.temperature().getEvent(&event);
    
  if (isnan(event.temperature)) //if the temperature cannot be read, then the following message appears in the serial monitor
 {
    Serial.println("Error reading temperature!");
 }

  else //if it can be read, then :
 {
    Serial.println("Temperature : "); //displays this in the serial monitor (it allows us to see what is displayed)
    Serial.print(event.temperature); //temperature measured by the sensor...
    Serial.println(" *C"); //... in degree Celsius
    Serial.println(""); //skip a line
    
    lcd.setCursor(0,0); //defines the position on the screen : 0, 0 = left upper side of the LCD
    lcd.print("Temp "); //what is displayed on the LCD (to see what it is)
    lcd.print(event.temperature); //temperature measured by the sensor (in degree Celsius) 
    lcd.print(" C"); //C for degree Celsius
 }
 
  //Get humidity event and print its value
    dht.humidity().getEvent(&event);
    
  if (isnan(event.relative_humidity)) //if the moisture cannot be read, then the following message appears in the serial monitor
 {
    Serial.println("Error reading humidity!");
 }
 
  else
 {
    Serial.println("Ambient humidity : "); //displays this in the serial monitor (it allows us to see what is displayed)
    Serial.print(event.relative_humidity); //ambient humidity measured by the sensor...
    Serial.println("%"); //...corresponding to a percentage
    Serial.println(""); //skip a line
    
    lcd.setCursor(0,1); //defines the position on the screen : 0, 1 = left lower side of the LCD 
    lcd.print("Amb Hum "); //what is displayed on the LCD (to see what it is)
    lcd.print(event.relative_humidity); //ambient humidity measured by the sensor...
    lcd.print(" %"); //... displayed as a percentage

    delay(3000); //the delay (in ms, so 3000 ms = 3 seconds) for which information regarding temperature and ambient humidity are displayed on the LCD...

    lcd.clear(); //... before clearing the content of the screen
 }
 
  //MOISTURE SENSOR + MOTOR
  soilMoisture = analogRead(soilRead); //read pin A3 then assign soilMoisture to that value
  Serial.println("Soil moisture level :"); 
  Serial.print (soilMoisture); //print the value on Serial Monitor
  Serial.print(" = ");
  soilMoisture = map(soilMoisture, 295, 1023, 100,0) ; //here we use the map func to map the moisture measured by the sensor obtained as a number, to a percentage
  // (295 when completely wet and 1023 when dry)

  
  Serial.print(soilMoisture); Serial.println(" %");// print the moisture as an ASCII (American Standard Code for Information Interchange)-encoded decimal
  Serial.println(""); //skip a line

  lcd.setCursor(0,0); //after clearing the LCD content, we display information regarding soil moisture and ambient lighting
  lcd.print("Soil Hum ");
  lcd.print(soilMoisture);
  lcd.print(" %");
  
  if(soilMoisture<=55) //if the moisture level is smaller than 55% or equal to 55%, then :
  {
    digitalWrite(DIR_A, HIGH); //the motor turns in a direction (if the parameter was LOW, the motor would turn backwards)
    digitalWrite(BRAKE_A, LOW); //the brake is released
    analogWrite(PWM_A, 250); //the power of the motor is set to 250
  }
  else
  {
    analogWrite(PWM_A, 0); //if the if-condition is not respected (i.e. the moisture level is greater than 55%), then the motor stops
  }
  
  //AMBIENT LIGHT SENSOR
  tsl.getEvent(&event);

   Serial.println("Ambient light :");
   Serial.print(event.light); Serial.println(" lux"); //here we display the results (measured in lux)
   Serial.println("");

   lcd.setCursor(0,1); 
   lcd.print("Light ");
   lcd.print(event.light);
   lcd.print(" lux");
   
  if (event.light<=30) //if the light level is smaller than 30 lux or equal to 30 lux, then :
  {
    digitalWrite(LED_BUILTIN, HIGH); //the LED turns on
  }
  else //if the light level is greater than 30 lux, then :
  {
   digitalWrite(LED_BUILTIN, LOW); //the LED turns off
  }
  
  delay(1000);
}
