  /////////////////
 // MODIFY HERE //
/////////////////

// Add your PushingBox Scenario DeviceID here:
  char devid[] = "vB2637136C91B82A";
  
  //////////////
 //   End    //
//////////////

int runNum = 0; //Int to record run number
char serverName[] = "api.pushingbox.com"; //PushingBox API url
int delayTime = 10000; //Delay to have between runs
#include <Bridge.h>
#include <HttpClient.h>

void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  
  Serial.begin(9600);
  while (!Serial); // wait for a serial connection
}

void loop() {
  // Initialize the client library
  HttpClient client;
  
  //Setup sensorValue to read a value from Analog Port A0
  int sensorValue = analogRead(A0);
  
  // Make a HTTP request:  
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=1&TimeStamp=" + runNum +"&TempC="+sensorValue;
  client.get (APIRequest);
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available())
{
    char c = client.read();
}
  Serial.flush();
  String UploadMessage;
  Serial.print("\nRun number: ");
  Serial.print(runNum);
  Serial.print("\nDelay value: ");
  Serial.print(delayTime);
  Serial.print("\nUploaded Light value: ");
  Serial.print(sensorValue);

  runNum = runNum + 1;
  delay(delayTime);
}
