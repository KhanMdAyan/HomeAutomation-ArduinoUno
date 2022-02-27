#include "WiFiEsp.h"

#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "Ayan";    //  your network SSID (name) 
char pass[] = "packdalwalo";   // your network password
           // your network key Index number (needed only for WEP)
#define rpin A5
WiFiEspClient  client;

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial esp(6, 7); // RX of arduino, TX of arduino
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

unsigned long myChannelNumber = 1658268;
const char * myWriteAPIKey = "TDCVIERDTH2W2CS8";
const char * myReadAPIKey = "8XCV5D8PFVTG5U61";
const int FieldNumber1 = 1;

int number = 0;

void setup() {
  Serial.begin(115200); //Initialize serial
  while(!Serial){
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }  
  
  // initialize serial for ESP module  
  setEspBaudRate(ESP_BAUDRATE);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  rpin = HIGH;
  delay(500);
  rpin = LOW;
  Serial.print("Searching for ESP8266..."); 
  // initialize ESP module
  WiFi.init(&esp);

  // check for the presence of the shield
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  Serial.println("found it!");
    
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  //Read from ThingSpeak
  long temp = ThingSpeak.readLongField(myChannelNumber, FieldNumber1, myReadAPIKey);
  statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode==200){
     ;
  }
  else{
    Serial.println("Unable to read channel");
  }
  
  }
  
  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, number, myWriteAPIKey);
  Serial.println(x);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  // change the value
  number++;
  if(number > 99){
    number = 0;
  }
  
  delay(20000); // Wait 20 seconds to update the channel again
}

// This function attempts to set the ESP8266 baudrate. Boards with additional hardware serial ports
// can use 115200, otherwise software serial is limited to 19200.
void setEspBaudRate(unsigned long baudrate){
  long rates[6] = {115200,74880,57600,38400,19200,9600};

  Serial.print("Setting ESP8266 baudrate to ");
  Serial.print(baudrate);
  Serial.println("...");

  for(int i = 0; i < 6; i++){
    esp.begin(rates[i]);
    delay(100);
    esp.print("AT+UART_DEF=");
    esp.print(baudrate);
    esp.print(",8,1,0,0\r\n");
    delay(100);  
  }
    
  esp.begin(baudrate);
}