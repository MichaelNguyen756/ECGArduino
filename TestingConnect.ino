#include <Usb.h>
#include <adk.h>

USB Usb;
ADK adk(&Usb,"Michael Nguyen", // Manufacturer Name
             "TestingConnectThree", // Model Name
             "Example sketch for the USB Host Shield", // Description (user-visible string)
             "1.0", // Version
             "www.ilearn.mq.edu.au", // URL (web page to visit if no installed apps support the accessory)
             "123456789"); // Serial Number (optional)

const int buttonPin = 2;

int buttonState;
int lastButtonState = LOW;
int ledState = LOW;

uint16_t stateLen = 1;
uint8_t state = 0;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\nADK demo start");
  if (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    while(1); //halt
  }
  
  pinMode(buttonPin, INPUT);
}

void loop()
{    
  Usb.Task();
  if(adk.isReady()) {
    Serial.println("Ready");
    
    int reading = digitalRead(buttonPin);
    
    if(reading != lastButtonState){
      lastDebounceTime = millis();
    }
    
    if((millis() - lastDebounceTime) > debounceDelay){
      if(reading != buttonState){
        buttonState = reading;
        
        if(buttonState == HIGH){
          ledState = !ledState;
          
          uint8_t msg[1];
          msg[0] = ledState;
          
          uint16_t len = sizeof(msg);
          uint8_t rcode = adk.SndData(len, msg);
    
          if(rcode && rcode != hrNAK)
             USBTRACE2("Data snd. :", rcode);
          if(len > 0) {
            Serial.print(F("\r\nData Packet: "));
            Serial.print(msg[0]);
          }
        }
      }     
    }
    
    
  }  
}
