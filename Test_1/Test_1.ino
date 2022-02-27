#include <LiquidCrystal.h>
#include <DHT.h>




#define LCDrsPin 7
#define LCDenPin 6
#define LCDdb4Pin 5
#define LCDdb5Pin 4
#define LCDdb6Pin 3
#define LCDdb7Pin 2
#define LEDRPin A0
#define LEDGPin A1
#define LEDBPin A2
#define FanPin 7
#define DHTPin 8 
#define PIRPin 8
#define ssid "Corona"
#define password "coronavirus"
//#define WindowPin D11

LiquidCrystal lcd(LCDrsPin, LCDenPin, LCDdb4Pin, LCDdb5Pin, LCDdb6Pin, LCDdb7Pin);
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(LEDRPin, redValue);
  analogWrite(LEDGPin, greenValue);
  analogWrite(LEDBPin, blueValue);
}
DHT dht(DHTPin, DHT11);

void setup() 
{
   dht.begin();
   lcd.begin(16, 2);
   Serial.begin(9600);

   

   
   pinMode(LEDRPin, OUTPUT);
   pinMode(LEDGPin, OUTPUT);
   pinMode(LEDBPin, OUTPUT);
   pinMode(FanPin, OUTPUT);
//   pinMode(WindowPin, OUTPUT);
   pinMode(LCDrsPin, OUTPUT);
   pinMode(LCDenPin, OUTPUT);
   pinMode(LCDdb4Pin, OUTPUT);
   pinMode(LCDdb5Pin, OUTPUT);
   pinMode(LCDdb6Pin, OUTPUT);
   pinMode(LCDdb7Pin, OUTPUT);
   pinMode(DHTPin, INPUT);
   pinMode(PIRPin, INPUT);

   
   lcd.setCursor(0, 0);
   lcd.print("MUHAHAHAHA");
   delay(1000);  //Wait time for all the components
   lcd.clear();
}

void loop() {
  setColor(130,255,0);
  digitalWrite(FanPin, HIGH);
  float Temp = dht.readTemperature();
  float Humidity = dht.readHumidity(); 
  delay(1000);
//  Serial.println(Temp);
//  Serial.println(Humidity);
  if(PIRPin == HIGH){
    Serial.println("Lol");
  }
  
//int gas_value = analogRead(DHTPin);

//if(gas_value==HIGH)
//{
//  digitalWrite(buzzer, HIGH);
//  lcd.setCursor(1, 0);
//  lcd.print("GAS DETECTED");
//  delay(2000);
//  lcd.clear();
//  delay(200);
//  
//}
//else
//{
// digitalWrite(buzzer, LOW); 
//}
//  

}
