#include <RTCZero.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <WiFiServer.h>

/*Global Variables
 * The following are variables that need to
 * to be 'global' or accessible by all methods
 */
const char* ssid = SECRET_SSID;    //  your network SSID (name) 
const char* password = SECRET_PSWD;  // your network password 

/*The first method called.
 * This method is called once at the start of the app running.
 * It is used to setup and initialize connections and things
 * needed in the program.
 */
void setup() {
  Serial.begin(9600); 
  while (!Serial) { 
   delay(2000); 
  }

Serial.println("Plant Communicator 1.0 Running!"); 
Serial.println("Begin setup..."); 
  connectWifi();
Serial.println("Setup complete!"); 
}

void loop() {
  // put your main code here, to run repeatedly:

}

/*Connect to Wifi give ssid and password
 */
void connectWifi(){
 Serial.print("Connecting Wifi: "); 
 Serial.println(ssid); 
 while (WiFi.begin(ssid, password) != WL_CONNECTED) { 
   Serial.print("."); 
   delay(500); 
 } 
 Serial.println(""); 
 Serial.println("WiFi connected"); 
}
 

void loop() { 
 float temperature = 22; 
 int moisture = 150; 
 int light = 40; 
 String warning = "This is a warning message"; 
 warning.replace(" ", "%20"); 
 send_email(temperature, moistue, light, warning ); 
 delay(20000) 
} 
void send_email(float temperature, int moisture, int light, String warning) { 
 // convert values to String 
 String _temperature = String(temperature); 
 String _moisture = String(moisture); 
 String _light = String(light); 
 String _warning = warning; 
 if (client.connect(host, 443)) { 
   client.println("POST " + httpsRequest + "temperature=" + _temperature + "&moisture=" + _moisture + "&light=" + _light + "&warning=" + _warning + " HTTP/1.1"); 
   client.println("Host: " + String(host)); 
   client.println("Connection: close"); 
   client.println(); 
   delay(1000); 
   while (client.available()) { // Print on the console the answer of the server 
     char c = client.read(); 
     Serial.write(c); 
   } 
   client.stop();  // Disconnect from the server 
 } 
 else { 
   Serial.println("Failed to connect to client"); 
 } 
}  
