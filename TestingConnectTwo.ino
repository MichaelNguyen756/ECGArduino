#include <Usb.h>
#include <adk.h>

USB Usb;
ADK adk(&Usb,"Michael Nguyen", // Manufacturer Name
             "TestingConnectTwo", // Model Name
             "Example sketch for the USB Host Shield", // Description (user-visible string)
             "1.0", // Version
             "www.ilearn.mq.edu.au", // URL (web page to visit if no installed apps support the accessory)
             "123456789"); // Serial Number (optional)
             
int firstCount = 0;
int secondCount = 0;
             
void setup()
{
  Serial.begin(115200);
  Serial.print("\r\nADK demo start");
  if (Usb.Init() == -1) {
    Serial.print("\r\nOSCOKIRQ failed to assert");
    while(1); //halt
  }
  
  //pinMode(buttonPin, INPUT);
}

void loop()
{    
  Usb.Task();
  if(adk.isReady()) {
    if(firstCount < 3){
      Serial.println("Accessory is connected");
      firstCount++;
      secondCount = 0;
    }   
  }else{
    if(secondCount < 3){
      Serial.println("Accessory is NOT connected");
      secondCount++;
      firstCount = 0;
    }
  }  
}
