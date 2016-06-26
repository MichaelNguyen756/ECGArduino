#include <Usb.h>
#include <adk.h>

#define DATA_READY 1
#define DATA_RECEIVED 2
#define DATA_ERROR 3

USB Usb;
ADK adk(&Usb,"Michael Nguyen", // Manufacturer Name
             "TestingConnectThree", // Model Name
             "Example sketch for the USB Host Shield", // Description (user-visible string)
             "1.0", // Version
             "www.ilearn.mq.edu.au", // URL (web page to visit if no installed apps support the accessory)
             "123456789"); // Serial Number (optional)

const int buttonPin = 2;

const int analogInPin = A0;

uint16_t stateLen = 1;
uint8_t state = 0;

long lastDebounceTime = 0;
long debounceDelay = 50;

int sensorValue = 0;
uint8_t outputValue = 0;

uint8_t count = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\nADK demo start");
  if (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    while(1); //halt
  }
}

void loop()
{    
  Usb.Task();
  if(adk.isReady()) {
    
      //Read Analog Pin
      sensorValue = analogRead(analogInPin);
      
      //outputValue = map(sensorValue, 0, 1023, 0, 255);
      outputValue = map(sensorValue, 0, 1023, -10, 10);
      
      //Send the data
      uint8_t msg[1];
      //msg[0] = HIGH;
      //msg[0] = count;
      
      msg[0] = outputValue;
      uint16_t len = sizeof(msg);
      uint8_t scode = adk.SndData(len, msg);
      
      if(scode && scode != hrNAK)
        USBTRACE2("Data snd. :", scode);
      if(len > 0) {
        Serial.print(F("\r\nData Packet: "));
        Serial.println(msg[0]);
      }
      
      count++;
      
      if(count > 20){
        count = 0;
      }
 
    delay(500);         
  }  
}
