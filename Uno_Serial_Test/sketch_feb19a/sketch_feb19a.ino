#include<ESP8266WiFi.h>
#include "ThingSpeak.h" 
WiFiClient client;
unsigned long myChannelNumber = 1658268;
const char * myWriteAPIKey = "TDCVIERDTH2W2CS8";
int number = 0;
const char * myReadAPIKey = "8XCV5D8PFVTG5U61";
int statusCode=0;
void setup() {
  Serial.begin(9600);
  WiFi.begin("Ayan", "packdalwalo");
  Serial.print("Connecting...");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("\n Waiting to connect to wifi");
  }
  Serial.print("Connected");
  Serial.print(WiFi.localIP());
  ThingSpeak.begin(client);
  
}

void loop() {
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  long temp = ThingSpeak.readLongField(myChannelNumber, 1, myReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200){
    Serial.println("t"+temp);
  }
  else{
    Serial.println("Not here");
  }

  // change the value
  number++;
  if(number > 99){
    number = 0;
  }
  
  delay(5000);


}
