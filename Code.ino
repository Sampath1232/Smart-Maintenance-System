
//LPG GAS SENSOR     OUTPUT PIN =     A00
//AIR QUALITY SENSOR OUTPUT PIN =     A01
//FLAME SENSOR       OUTPUT PIN =     A02
//SOLAR MODULE 1     OUTPUT PIN =  A04&05
//SOLAR MODULE 2     OUTPUT PIN =  A06&07
//HUMI&TEMP SENSOR   OUTPUT PIN =     D02
//WATER FLOW SENSOR  OUTPUT PIN =  D03&04
//BLUETOOTH MODULE   OUTPUT PIN =  D10&11
//SOLAR MODULE 1     OUTPUT PIN =     D12
//SOLAR MODULE 2     OUTPUT PIN =     D13

#include <Servo.h>
#include<SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

SoftwareSerial BTserial(10, 11); // TX | RX
Servo myservo1;
Servo myservo2;
DHT dht(DHTPIN, DHTTYPE);

byte statusLed    = 13;
int led = 7;
byte sensorInterrupt = 0;  // 0 = digital pin 3
byte sensorPin       = 3;
byte sensorInterrupt1 = 1;  // 1 = digital pin 4
byte sensorPin1       = 4;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

volatile byte pulseCount;
volatile byte pulseCount1;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
float flowRate1;
unsigned int flowMilliLitres1;
unsigned long totalMilliLitres1;
float difference;

unsigned long oldTime;
unsigned long oldTime1;

int ldr1 = 4;
int ldr2 = 5;
int ldr3 = 6;
int ldr4 = 7;
int val1;
int val2;
int val3;
int val4;
int pos = 90;
int sensorPin2 = A2;
int sensorValue = 0;
int sensorValue0;
int sensorValue1;
const int gasPin = A0;

int LEDPin = 13;

void setup()
{
  Serial.begin(9600);
  BTserial.begin(9600);
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  pinMode(led, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
  pinMode(sensorPin1, INPUT);
  digitalWrite(sensorPin1, HIGH);

  pulseCount         = 0;
  flowRate           = 0.0;
  flowMilliLitres    = 0;
  totalMilliLitres   = 0;
  oldTime            = 0;
  pulseCount1        = 0;
  flowRate1          = 0.0;
  flowMilliLitres1   = 0;
  totalMilliLitres1  = 0;
  oldTime1           = 0;
  difference         = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  attachInterrupt(sensorInterrupt1, pulseCounter1, FALLING);

  dht.begin();
  myservo1.attach(12);
  myservo2.attach(13);
  myservo1.write(pos);
  myservo2.write(pos);

}

void loop()
{

  ////////////////////////////////////////SOLAR TRACKING////////////////////////////////////
  val1 = analogRead(ldr1);
  val2 = analogRead(ldr2);
  val1 = map(val1, 0, 1023, 0, 180);
  val2 = map(val2, 0, 1023, 0, 180);
  if (val1 > (val2 + 50))
  {
    if (pos < 180)
      pos = pos + 1;
    myservo1.write(pos);
    Serial.println("backward");
    delay(10);
  }
  else if (val2 > (val1 + 50))
  {
    if (pos > 0)
      pos = pos - 1;
    myservo1.write(pos);
    Serial.println("forward");
    delay(10);
  }

  val3 = analogRead(ldr3);
  val4 = analogRead(ldr4);
  val3 = map(val3, 0, 1023, 0, 180);
  val4 = map(val4, 0, 1023, 0, 180);
  if (val3 > (val4 + 50))
  {
    if (pos < 180)
      pos = pos + 1;
    myservo2.write(pos);
    Serial.println("backward");
    delay(10);
  }
  else if (val4 > (val3 + 50))
  {
    if (pos > 0)
      pos = pos - 1;
    myservo2.write(pos);
    Serial.println("forward");
    delay(10);
  }


  //////////////////////////////////////////CONTROL LIGHT//////////////////////////////////
  if (BTserial.available())
  {
    char daten = BTserial.read();
    if (daten == 'H')
    {
      digitalWrite(LEDPin, HIGH);
      BTserial.print("LED on");
      BTserial.print(";");
    }
    else if (daten == 'L')
    {
      digitalWrite(LEDPin, LOW);
      BTserial.print("LED off");
      BTserial.print(";");
    }
  }

  ///////////////////////////////////////AIR QUALITY//////////////////////////////////////
  sensorValue0 = analogRead(1); // read analog input pin 1
  Serial.println(sensorValue0);
  if (sensorValue0 > 600)
  {
    BTserial.println("Harmful Gas Detected");
    BTserial.print(";");
    delay(5000);
  }

  ///////////////////////////////////////////GAS/////////////////////////////////////////
  sensorValue1 = analogRead(gasPin); // read analog input pin 1
  Serial.println(sensorValue1);
  if (sensorValue1 > 100)
    //  {
    //    BTserial.println("Flamable Gas Detected");
    //    BTserial.print(";");
    //    delay(5000);
    //  }

    ///////////////////////////////////////////FIRE///////////////////////////////////////
    sensorValue = analogRead(sensorPin2);
  Serial.println(sensorValue);
  if (sensorValue < 100)
  {
    BTserial.println("Fire Detected");
    BTserial.print(";");
    delay(1000);
  }

  ////////////////////////////////////////TEMP&HUMI/////////////////////////////////////
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.println(h);
  if (h > 70)
  {
    BTserial.println("High Humidity Detected");
    BTserial.print(";");
    delay(5000);
  }
  Serial.println(t);
  if (t > 35)
  {
    BTserial.println("Heat Detected");
    BTserial.print(";");
    delay(5000);
  }

  ///////////////////////////////////////WATERFLOW///////////////////////////////////////
  delay(100);

  if ((millis() - oldTime) > 1000)   // Only process counters once per second
  {
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
    detachInterrupt(sensorInterrupt1);

    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    flowRate1 = ((1000.0 / (millis() - oldTime)) * pulseCount1) / calibrationFactor;
    difference = flowRate - flowRate1;
    if (difference > 2)
    { digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);               // wait for a second
      digitalWrite(led, LOW);
    }

    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();

    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;

    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;

    unsigned int frac;

    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate1));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\n");
    Serial.print("Difference: ");
    Serial.print(int(difference));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\n");
    if (difference < 0)
    {
      BTserial.println("Water Leakage Detected");
      BTserial.print(";");
      delay(5000);
    }
    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    pulseCount1 = 0;

    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    attachInterrupt(sensorInterrupt1, pulseCounter1, FALLING);
  }
}

/*
  Insterrupt Service Routine
*/
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
void pulseCounter1()
{
  // Increment the pulse counter
  pulseCount1++;
}
