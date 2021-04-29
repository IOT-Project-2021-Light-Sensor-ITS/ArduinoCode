//Define
#define BLYNK_PRINT Serial
#define LED 4

//Include
#include <Bridge.h>
#include <BlynkSimpleYun.h>

//Blynk auth token plz don't steal 
char auth[] = "HzRW32t0aFYNja3w7R2R3qlQ6fu-tj4w";

const int numReadings = 4;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

int inputPin = A0;

//Instance of Blynk timer
BlynkTimer timer;

//Timer event, sends current light reading to app
void myTimerEvent()
{
  //Setup sensorValue to read a value from Analog Port A0
  int sensorValue = analogRead(A0);
  Blynk.virtualWrite(V5, sensorValue);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  
  //Demo LED setup
  pinMode(LED, OUTPUT);
  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  //Default LED to ON
  digitalWrite(LED, HIGH);
  Blynk.begin(auth);
  // Setup a function to be called every 2 seconds
  timer.setInterval(2000L, myTimerEvent);
}

void loop()
{
  //Setup sensorValue to read a value from Analog Port A0
  int sensorValue1 = analogRead(A0);

  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(inputPin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(average);
  
  Blynk.virtualWrite(V7, average);
  
  WidgetLED led1(V6);
  
  Blynk.run();
  timer.run(); // Initiates BlynkTimer

  if((sensorValue1 > average - 10) && (sensorValue1 < average + 10) )
  {   
    //LED to OFF
    digitalWrite(LED, LOW);
    led1.off();
    delay(5000);
  }
  else
  {
    //LED to ON
    digitalWrite(LED, HIGH);
    led1.on();
    delay(10000);
  }
}
