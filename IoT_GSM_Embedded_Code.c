//Firebase Connection with ESP Module 

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
// Set these to run examples.
#define FIREBASE_HOST "celingfanregulator.firebaseio.com"
#define FIREBASE_AUTH "1qAnDEuPmdy4ef3d9QLEGtYcA1cOehKmpmzxUtLr"
#define WIFI_SSID "iPhone7.2"
#define WIFI_PASSWORD "qwerty123"
String Resivedata ;
#define PWM_PIN 14
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(PWM_PIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // used to enable communication
  Firebase.setString("Variable/Value", "FirstTestStrig"); //set the variables
}
void loop()
{
  Resivedata = Firebase.getString("Variable/Value");//get the variables
  Serial.println(Resivedata); 
  analogWrite(PWM_PIN, map(Resivedata.toInt(), 0, 80, 80, 0)); // map and analogwrite function.
  irSetup(Resivedata)
  Serial.println(Resivedata);
  delay(100);// delay of 100ms to reduce the hitcount.
}

/////////////////////////////////////////////////////////////////////////////////////////

//Connect ESP Module to Wifi exculsively
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#define ESP8266_BAUD 9600

char auth[] = "6bae2d0e7bfa4b6096feeaffa2030e4f";
char ssid[] = "iPhone7"; 

char pass[] = "qwerty123";  

SoftwareSerial EspSerial(2, 3); // RX, TX
WidgetLCD lcd(V0);

ESP8266 wifi(&EspSerial);

void setup()
{

  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  Blynk.begin(auth, wifi, ssid, pass);
  Serial.println(1, 1, "connection success");
}

void loop()
{
  Blynk.run();
}

/////////////////////////////////////////////////////////////////////////////////////////

//SETUP GSM Module

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
}

void loop()
{
  if (Serial.available()>0)
  {
  	RecieveMessage()
  }
  if (mySerial.available()>0)
   Serial.write(mySerial.read());
  
}

void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  delay(1000);
  irSetup("AT+CNMI=2,2,0,0,0")
 }

/////////////////////////////////////////////////////////////////////////////////////////

//SETUP IR Sensor

void irSetup(){
  pinMode(LED, OUTPUT);          // Pin 13 has an LED connected on  Arduino 
  pinMode(ProxSensor,INPUT);    //Pin 2 is connected to the output of proximity sensor
  Serial.begin(9600);

}

void loop() 
{
  long state = digitalRead(ProxSensor);
  if(state == HIGH)      //Check the sensor output
  {
    digitalWrite(LED, HIGH);   // set the LED on
    Serial.println(state);
    delay(1000);
  }
  else
  {
    digitalWrite(LED, LOW);    // set the LED off
    Serial.println(state);
    delay(1000);
  }

}



