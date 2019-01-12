#include <RTCZero.h>

#include <WiFi101.h>
//#include <WiFiUdp.h>
//#include <WiFiClient.h>
//#include <WiFiServer.h>

/*Global Constants
 * do not change during run-time
 * The following are constants that need to
 * to be 'global' or accessible by all methods
 */
  long interval = 1000;         // interval at which to blink (milliseconds)
  char* ssid = "WIFI_SSID";    //  your network SSID (name)
  char* password = "WIFI_PASSWORD";  // your network password
  int maxAttempts = 5;
  int moisturePin = A2;
  int threeshold = 800; //reading from dry soil

  /* some starter readings I had
   *  with totally dry soil: 1023,1013,1023,1021,1019,1022,1020,1021
   *
   *  with just watered ~tablespoon of water misted and waited 12:00- 12:20
   *  163,162,164,166,163,164,162,163,162,163,163,161,163
   */

/*Global Variables
 * may change during run-time
 * The following are variables that need to
 * to be 'global' or accessible by all methods
 */
  int ledState = LOW;                 // ledState used to set the LED
  unsigned long previousMillis = 0;    // will store last time LED was updated


/*The first method called.
 * This method is called once at the start of the app running.
 * It is used to setup and initialize connections and things
 * needed in the program.
 */
void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output.

  Serial.begin(9600); //Needed to read output over the USB port
  while (!Serial) { //wait for USB serial port to connect
   LEDblink();
   delay(1000); //try again in 1 second
  }
  LEDoff();
  Serial.println("Plant Communicator 1.0 Running!");
  Serial.println("Begin setup...");
    if(!connectWifi()){
      return; //just quit.
    }
  Serial.println("Ready! Starting program...");
}

void loop() {
    // put your main code here, to run repeatedly:
    LEDon();
    Serial.println("Report... ");
    Serial.print("     Moisture: ");
    Serial.println(get_average_moisture());

   //float temperature = 22;
   //int light = 40;
   //String warning = "This is a warning message";
   //message.replace(" ", "%20");
   //send_email(temperature, moistue, light, warning );

   LEDoff();
   delay(20000); //run sensor ever 20seconds

}

/* Get a moisture reading
 * return average value of 10 values readings taken over 1000 milliseconds
 */
int get_average_moisture() {
 int moistureValue = 0; // variable to temporarly store moisture value
 for (int a = 0; a < 10; a++) {
   moistureValue += analogRead(moisturePin);
   delay(100);
 }
 return moistureValue / 10;
}






/**************************
 * HERE BE DRAGONS
 **************************/

/*Connect to Wifi give ssid and password
 */
boolean connectWifi(){

// Check for the presence of the shield
  Serial.print("WiFi101 shield: ");
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("NOT PRESENT");
    Serial.println("ERROR: Unable to connect to WiFi");
    return false; // don't continue
  }else{
      Serial.println("DETECTED");

      // Print WiFi MAC address:
      printMacAddress();

      // scan for existing networks:
      Serial.println("Scanning available networks...");
      listNetworks();

     Serial.print("Connecting to: ");
     Serial.println(ssid);
     int connectionAttempt = 1; //while is the 1st attempt
     while (WiFi.begin(ssid, password) != WL_CONNECTED) {
       connectionAttempt++; //add one to the number of connection attempts
       Serial.print("     Attempt: ");
       Serial.println(connectionAttempt);
       if(connectionAttempt>maxAttempts){
        break; //If 200 attempts were made, give up
       }else{
        delay(500); //wait half a second
       }
     }

     if(connectionAttempt<maxAttempts){
       Serial.println("WiFi connected");
       return true;
     }else{
       Serial.print("ERROR: Unable to connect to SSID: ");
       Serial.println(ssid);
       Serial.println("Please validate password and try again.");
       return false;
     }
  }
}

void printMacAddress() {
  // the MAC address of your Wifi shield
  byte mac[6];

  // print your MAC address:
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
}

void listNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1){
    Serial.println("Couldn't get a wifi connection");
    return;
  }

  // print the list of networks seen:
  Serial.print("number of available networks:");
  Serial.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") ");
    Serial.print(WiFi.SSID(thisNet));
    Serial.print("\tSignal: ");
    Serial.print(WiFi.RSSI(thisNet));
    Serial.print(" dBm");
    Serial.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
    Serial.flush();
  }
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      Serial.println("WEP");
      break;
    case ENC_TYPE_TKIP:
      Serial.println("WPA");
      break;
    case ENC_TYPE_CCMP:
      Serial.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      Serial.println("None");
      break;
    case ENC_TYPE_AUTO:
      Serial.println("Auto");
      break;
  }
}

void LEDblink(){
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // save the last time you blinked the LED

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(LED_BUILTIN, ledState); // set the LED with the ledState of the variable:
  }
}

void LEDon(){
  ledState = HIGH;
  digitalWrite(LED_BUILTIN, ledState); // set the LED with the ledState of the variable:
}

void LEDoff(){
  ledState = LOW;
  digitalWrite(LED_BUILTIN, ledState); // set the LED with the ledState of the variable:
}

//void send_email(float temperature, int moisture, int light, String warning) {
// // convert values to String
// String _temperature = String(temperature);
// String _moisture = String(moisture);
// String _light = String(light);
// String _warning = warning;
// if (client.connect(host, 443)) {
//   client.println("POST " + httpsRequest + "temperature=" + _temperature + "&moisture=" + _moisture + "&light=" + _light + "&warning=" + _warning + " HTTP/1.1");
//   client.println("Host: " + String(host));
//   client.println("Connection: close");
//   client.println();
//   delay(1000);
//   while (client.available()) { // Print on the console the answer of the server
//     char c = client.read();
//     Serial.write(c);
//   }
//   client.stop();  // Disconnect from the server
// }
// else {
//   Serial.println("Failed to connect to client");
// }
//}
