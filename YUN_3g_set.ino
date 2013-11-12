/*
 Set 3G/UMTS env
 created 11-2013
 by Mirco Piccin
 */

#include <Process.h>

void setup() {
  Bridge.begin();	// Initialize the Bridge
  Serial.begin(9600);	// Initialize the Serial

  Process p;  

  // Wait until a Serial Monitor is connected.
  while(!Serial);

  Serial.println("**Set 3G/UMTS environment**");
  Serial.println();
  Serial.println("Updating repository...");

  p.runShellCommand("/bin/opkg update");
  while(p.running()); 
  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }  
  
  Serial.println();
  Serial.println("Installing needed packages...");

  p.runShellCommand("/bin/opkg install unzip kmod-usb2 kmod-usb-core kmod-usb-serial kmod-usb-serial-option kmod-usb-serial-wwan usb-modeswitch usb-modeswitch-data libusb-1.0 comgt chat");
  while(p.running()); 
  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }
  
  Serial.println();
  Serial.println("Downloading & installing luci 3G conf page...");

  p.runShellCommand("/usr/bin/curl -k https://raw.github.com/pictux/Yun_3g/master/luci-proto-3g_svn-r9931-1_ar71xx.ipk -o /tmp/luci-proto-3g_svn-r9931-1_ar71xx.ipk");
  while(p.running()); 
  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }

  p.runShellCommand("/bin/opkg install /tmp/luci-proto-3g_svn-r9931-1_ar71xx.ipk");
  while(p.running()); 
  while (p.available()>0) {
    char c = p.read();
    Serial.print(c);
  }

  Serial.println();
  Serial.println("***** ALL DONE *****");
  Serial.println();
  Serial.println("Rebooting...");
  p.runShellCommand("/sbin/reboot");
  
  Serial.flush();
}

void loop() {

}









