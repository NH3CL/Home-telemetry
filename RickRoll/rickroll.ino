#include <ESP8266WiFi.h>

// Speaker
// + to NodeMCU D7 (GPIO13)
// - to NodeMCU GND

 
const char* ssid = "_YOUR_WIFI_SSID_";
const char* password = "_YOUR_WIFI_PASSWORD_";
 
int Speaker = 13; // GPIO13
WiFiServer server(80);


//Notes hertz

int c = 262;
int d = 294;
int e = 330;
int f = 349;
int g = 392;
int a = 440;
int b = 494;
int bf = 466;
int C = 523;
int frequency[56] = {
  c, d, f, d, a, a, g, c, d, f, d, g, g, f, e, d, c, d, f, d, f, g, e, d, c, c, g, f,
  c, d, f, d, a, a, g, c, d, f, d, C, e, f, e, d, c, d, f, d, f, g, e, d, c, c, g, f};
int duration[56] = {
  120, 120, 120, 120, 360, 360, 720, 120, 120, 120, 120, 360, 360, 480, 120, 240, 120, 120, 120, 120,
  480, 240, 360, 120, 480, 240, 480, 960,
  120, 120, 120, 120, 360, 360, 720, 120, 120, 120, 120, 360, 360, 480, 120, 240, 120, 120, 120, 120,
  480, 240, 360, 120, 480, 240, 480, 960};
int frequency2[89] = {
  f, g, c, g, a, C, bf, a, f, g, c, c, c, d, f, f, f, g, c, g, a, C, bf, a, f, g, c, e, f, f, 
  f, f, f, //33
  d, e, f, f, g, e, d, c, d, d, e, f, d, c, //47
  C, C, g, d, d, e, f, d, f, g, e, d, c, //64
  d, d, e, f, d, c, g, g, g, a, g, f, g, a, f, //80
  g, g, g, a, g, c, d, e, f, d, g, a, g}; //93
int duration2[89] = {
  620, 620, 410, 620, 620, 100, 100, 200, 620, 620, 1440, 100, 100, 100, 200, 100,
  620, 620, 410, 620, 620, 100, 100, 200, 620, 620, 410, 200, 200, 830, 100, 200, 510,
  200, 200, 200, 200, 200, 300, 100, 1660, 200, 200, 200, 200, 410, 200,
  410, 200, 1240, 200, 200, 200, 200, 200, 200, 200, 410, 200, 1240,
  200, 200, 200, 200, 200, 410, 200, 200, 200, 200, 830, 1030, 200, 200, 200,
  200, 200, 200, 200, 410, 1240, 200, 200, 200, 410, 200, 200, 620};
int frequency3[145] = {
  f, g, c, g, a, C, bf, a, f, g, c, c, c, d, f, f, f, g, c, g, a, C, bf, a, f, g, c, e, f, f, 
  f, f, f, //33
  d, e, f, f, g, e, d, c, d, d, e, f, d, c, //47
  C, C, g, d, d, e, f, d, f, g, e, d, c, //64
  d, d, e, f, d, c, g, g, g, a, g, f, g, a, f, //80
  g, g, g, a, g, c, d, e, f, d, g, a, g,
  c, d, f, d, a, a, g, c, d, f, d, g, g, f, e, d, c, d, f, d, f, g, e, d, c, c, g, f,
  c, d, f, d, a, a, g, c, d, f, d, C, e, f, e, d, c, d, f, d, f, g, e, d, c, c, g, f
  };
int duration3[145] = {
  620, 620, 410, 620, 620, 100, 100, 200, 620, 620, 1440, 100, 100, 100, 200, 100,
  620, 620, 410, 620, 620, 100, 100, 200, 620, 620, 410, 200, 200, 830, 100, 200, 510,
  200, 200, 200, 200, 200, 300, 100, 1660, 200, 200, 200, 200, 410, 200,
  410, 200, 1240, 200, 200, 200, 200, 200, 200, 200, 410, 200, 1240,
  200, 200, 200, 200, 200, 410, 200, 200, 200, 200, 830, 1030, 200, 200, 200,
  200, 200, 200, 200, 410, 1240, 200, 200, 200, 410, 200, 200, 620,
  120, 120, 120, 120, 360, 360, 720, 120, 120, 120, 120, 360, 360, 480, 120, 240, 120, 120, 120, 120,
  480, 240, 360, 120, 480, 240, 480, 960,
  120, 120, 120, 120, 360, 360, 720, 120, 120, 120, 120, 360, 360, 480, 120, 240, 120, 120, 120, 120,
  480, 240, 360, 120, 480, 240, 480, 960
  };

void rickroll(){ 
  for(int i=0; i<56; i++){ //run loop for all values of i 0 to __ 
    tone(Speaker, frequency[i]); //play tones in order from the frequency array
    delay(duration[i]);   //play all above tones for the corresponding duration in the duration array
    noTone(Speaker);   //turn off speaker for 30ms before looping back to the next note
    delay(10);
  }
}
void rickroll2(){ 
  for(int i=0; i<89; i++){ //run loop for all values of i 0 to __ 
    tone(Speaker, frequency2[i]); //play tones in order from the frequency array
    delay(duration2[i]);   //play all above tones for the corresponding duration in the duration array
    noTone(Speaker);   //turn off speaker for 30ms before looping back to the next note
    delay(10);
  }
}

void rickroll3(){ 
  for(int i=0; i<145; i++){ //run loop for all values of i 0 to __ 
    tone(Speaker, frequency3[i]); //play tones in order from the frequency array
    delay(duration3[i]);   //play all above tones for the corresponding duration in the duration array
    noTone(Speaker);   //turn off speaker for 30ms before looping back to the next note
    delay(10);
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(Speaker, OUTPUT);
  digitalWrite(Speaker, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/RR=CHORUS") != -1)  {
    rickroll();
    value = HIGH;
  }
  if (request.indexOf("/RR=INTRO") != -1)  {
    rickroll2();
    value = LOW;
  }
  if (request.indexOf("/RR=FULL") != -1)  {
    rickroll3();
    value = LOW;
  }
// Set Speaker according to the request
//digitalWrite(Speaker, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
 client.print("Rick Roll");
 
 // if(value == HIGH) {
 //   client.print("");
 // } else {
//    client.print("");
//  }
  client.println("<br><br>");  
  client.println("<a href=\"/RR=INTRO\"\"><button>Intro </button></a><br />");  
  client.println("<a href=\"/RR=CHORUS\"\"><button>Chorus </button></a><br />");
  client.println("<a href=\"/RR=FULL\"\"><button>Whole Song </button></a>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

