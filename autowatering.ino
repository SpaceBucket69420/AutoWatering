/*
Chirp - arduino example

Connection 
Chirp pin 1 - no connection
Chirp pin 2 - Arduino VCC
Chirp pin 3 - Arduino A5
Chirp pin 4 - Arduino A4
Chirp pin 5 - Arduino pin 2
Chirp pin 6 - Arduino GND
*/

#include <Wire.h>

//DHT-------
#include <DHT.h>;
#define DHTPIN 13     // what pin we're connected to
#define DHTPIN2 12  
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
DHT dht2(DHTPIN2, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
//DHT-------


#define pump 7
long previousMillis = 0;        // will store last time LED was updated
long interval = 60000;   



void writeI2CRegister8bit(int addr, int value) {
  Wire.beginTransmission(addr);
  Wire.write(value);
  Wire.endTransmission();
}

unsigned int readI2CRegistepump6bit(int addr, int reg) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  delay(1100);
  Wire.requestFrom(addr, 2);
  unsigned int t = Wire.read() << 8;
  t = t | Wire.read();
  return t;
}


//DHT-------
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float hum2;  //Stores humidity value
float temp2; //Stores temperature value
float hum3;  //Stores humidity value
float temp3; //Stores temperature value
//DHT-------

void setup() {
  //DHT-------
    dht.begin();
  dht2.begin();
  //DHT-------
  Wire.begin();
  Serial.begin(9600);
  pinMode(pump, INPUT_PULLUP);
  pinMode(pump, OUTPUT);
  digitalWrite(pump,HIGH);

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW); //Reset the Chirp
  delay(1); //maybe allow some time for chirp to reset
  digitalWrite(2, HIGH); //Go out from reset
  writeI2CRegister8bit(0x20, 3); //send something on the I2C bus
  delay(1000); //allow chirp to boot
}

void loop() {
    unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

  Serial.println(readI2CRegistepump6bit(0x20, 0)); //read capacitance register
 
    Serial.println(hum3 / 2);

    Serial.println(temp3 / 2);


    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
        //Read data and store it to variables hum and temp
    hum2 = dht2.readHumidity();
    temp2= dht2.readTemperature();

    hum3= hum + hum2;
    
    temp3=temp + temp2;
  
  }
delay(1000);
int watering = 0;
if (20 < readI2CRegistepump6bit(0x20, 0)  && readI2CRegistepump6bit(0x20, 0)  < 350) {


   
 digitalWrite(pump,LOW);

delay(400000);

digitalWrite(pump,HIGH);

delay(1000);

 }
if (readI2CRegistepump6bit(0x20, 0) > 1500){


    Serial.println("799");
   delay (5000);





 }

}



