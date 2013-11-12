/*
 Set 3G/UMTS env
 created 11-2013
 by Mirco Piccin
 */

#include <Process.h>

static String APN="internet.wind"; //provider apn
static String PIN="1131";  //sim pin (disabled pin is a problem!)
static String DEVICE="/dev/ttyUSB0"; //don't touch here if you don't know what it is

void setup() {
  Bridge.begin();	
  Serial.begin(9600);	

  Process p;

  while(!Serial);

  Serial.println("**Set 3G/UMTS environment**");
  Serial.println();
  Serial.println("Downloading script for setting up 3G...");

  p.runShellCommand("/usr/bin/curl -k https://raw.github.com/pictux/Yun_3g/master/linino_set3g.sh -o /tmp/linino_set3g.sh");
  while(p.running());  
  while (p.available()) {
    char c = p.read();
    Serial.print(c);
  } 

  Serial.println();
  Serial.println("Chmod script...");

  p.runShellCommand("/bin/chmod +x /tmp/linino_set3g.sh ");
  while(p.running());  
  while (p.available()) {
    char c = p.read();
    Serial.print(c);
  } 


  Serial.println();
  Serial.println("Execute script...");

  p.runShellCommand("/tmp/linino_set3g.sh -p " + PIN + " -a " + APN + " -d " + DEVICE);
  while(p.running());  
  while (p.available()) {
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
  //nothing to do here *
}













