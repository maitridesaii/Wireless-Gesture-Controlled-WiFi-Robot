#define REnable 14
#define LEnable 12
#define RMotor_1  2
#define RMotor_2  0
#define LMotor_1  13
#define LMotor_2  15

/* include library */
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
WiFiClient client;
/* defining server port */
ESP8266WebServer server(80);

/* Define WiFi Credentials */
const char* ssid = "Maitri"; /* Your SSID */
const char* password = "12345678"; /* Your Password */

String  direction = "";
int robospeed = 100; 

/* Defining right and left motor pins */
//int RMotor_1 = 18;/* Right Motor GPIO0(D3) */
//int RMotor_2 = 17;/* Right Motor GPIO2(D4) */
//int LMotor_1 = 7;/* Left Motor GPIO13(D7) */
//int LMotor_2 = 16;/* Left Motor GPIO15(D8) */

/* Defining L298N enable pins */
//int REnable = 5;/* Right Motor Enable Pin GPIO14(D5) */
//int LEnable = 6;/* Right Motor Enable Pin GPIO12(D6)  */

void setup() {
  Serial.begin(115200);
  Serial.println("GPIO test!");
  /* Initialize Motor Control Pins as Output */
  pinMode(RMotor_1, OUTPUT);
  pinMode(RMotor_2, OUTPUT);
  pinMode(LMotor_1, OUTPUT);
  pinMode(LMotor_2, OUTPUT);
  /* Initialize Motor Enable Pins as Output */
  pinMode(REnable, OUTPUT);
  pinMode(LEnable, OUTPUT);

  /* Connecting to WiFi */
  connectingToWiFi();

  server.on("/", handleRequest);
  server.onNotFound(handleRequest);

  /* Starting Server */
  server.begin();
  Serial.println("Server started");

  /* Starting Server */
  analogWrite(REnable, robospeed);
  analogWrite(LEnable, robospeed);
}
void loop() {

  /* Handling Request */
  server.handleClient();
  String direction = server.arg("direction");
  Serial.println(direction);
switch (direction)
{
  case "F":
  move_forward();
  break;
  case "B":
  move_backward();
  break;
  case "R":
  turn_right();
  break;
  case "L":
  turn_left();
  break;
  case "S":
  move_stop();
  break;
  default:
  rest();
}
}

void handleRequest() {
  if ( server.hasArg("direction") )
  {
    Serial.println(server.arg("direction"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void connectingToWiFi() {
  delay(3000);
  WiFi.disconnect();
  delay(1000);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(1000);
    Serial.print("...");
  }
  Serial.println("Connected");
  Serial.println("Local IP is : ");
  Serial.println((WiFi.localIP().toString()));
  delay(5000);
}

/* Move Forward */
void move_forward() {
  digitalWrite(RMotor_1, HIGH);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
}

/* Move Backward */
void move_backward() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, HIGH);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, HIGH);
}

/* Turn Right */
void turn_right() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
  delay(100);
  digitalWrite(RMotor_1, HIGH);
  digitalWrite(RMotor_2, LOW); 
}

/* Turn Left */
void turn_left() {
  digitalWrite(RMotor_1, HIGH);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, LOW);
  delay(100);
  
  digitalWrite(LMotor_1, HIGH);
  digitalWrite(LMotor_2, LOW);
}

/* Stop Move */
void move_stop() {
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, LOW);
}

void rest(){
  digitalWrite(RMotor_1, LOW);
  digitalWrite(RMotor_2, LOW);
  digitalWrite(LMotor_1, LOW);
  digitalWrite(LMotor_2, LOW);  
}
