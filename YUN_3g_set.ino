/*



 */

#include <Process.h>

void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial

  // Wait until a Serial Monitor is connected.
  while(!Serial);


  Process p;  
  p.runShellCommand("/bin/opkg update");

  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }  

  p.runShellCommand("/bin/opkg install kmod-usb2 kmod-usb-core kmod-usb-serial kmod-usb-serial-option kmod-usb-serial-wwan usb-modeswitch usb-modeswitch-data libusb-1.0");

  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }

  Serial.println("***** ALL DONE *****");
}

void loop() {

}




