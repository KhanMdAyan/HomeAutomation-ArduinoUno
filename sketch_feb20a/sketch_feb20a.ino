#include "WiFiEsp.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

char ssid[] = "Ayan";   // your network SSID (name) 
char pass[] = "packdalwalo";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiEspClient  client;

// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial esp(6, 7); // RX, TX
#define ESP_BAUDRATE  19200
#else
#define ESP_BAUDRATE  115200
#endif

// Weather station channel details
unsigned long ChannelNumber = 1658268;
unsigned int AC = 1;

// Counting channel details

const char * ReadAPIKey = "N6BUH89WR6FZRIO8";
const char * myWriteAPIKey = "8XCV5D8PFVTG5U61";
int number =0;


void setup() {
 //Initialize serial and wait for port to open
  Serial.begin(115200);  
  while(!Serial){
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  Serial.print("Start");
  // initialize serial for ESP module  
  setEspBaudRate(ESP_BAUDRATE);
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

  int statusCode = 0;
  
  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected");
  }
  int x = ThingSpeak.writeField(ChannelNumber, AC, number, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
    esp.println('AT+HTTPCPOST="https://api.thingspeak.com/update?api_key=N6BUH89WR6FZRIO8&field1=987"');
    Serial.print("\n link");
  }

  // change the value
  number++;
  if(number > 99){
    number = 0;
  }


  // Read in field 1 of the private channel which is a counter  
  long count = ThingSpeak.readLongField(ChannelNumber,AC, ReadAPIKey);  

   // Check the status of the read operation to see if it was successful
  statusCode = ThingSpeak.getLastReadStatus();
  if(statusCode == 200){
    Serial.println("Counter: " + String(count));
  }
  else{
    Serial.println("Problem reading channel. HTTP error code " + String(statusCode)); 
  }
//  
  delay(15000); // No need to read the counter too often.
  
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
