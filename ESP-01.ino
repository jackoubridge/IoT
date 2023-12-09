#include <ESP8266WiFi.h>
 
const char* ssid = "";
const char* password = "";

int redPin = 2;
int greenPin = 1;
int bluePin = 3;

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();

  Serial.print(WiFi.localIP());
  
  // Signal to show successful setup when no serial monitor available
  digitalWrite(greenPin, HIGH);
  delay(250);
  digitalWrite(greenPin, LOW);
  delay(250);
  digitalWrite(greenPin, HIGH);
  delay(250);
  digitalWrite(greenPin, LOW);
}
 
void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  while(!client.available()){
    delay(1);
  }

  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/red") != -1){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  if (request.indexOf("/green") != -1){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, LOW);
  }
  if (request.indexOf("/blue") != -1){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
  if (request.indexOf("/off") != -1){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");

  client.print("<!DOCTYPE html><html lang='en'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Jack's Project</title><link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.3.1/dist/css/bootstrap.min.css' integrity='sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T' crossorigin='anonymous'></head><body><div class='mycontainer m-0 p-0 position-relative d-flex justify-content-center'><a class='box' style='background-color: red;' href='red'></a><a class='box' style='background-color: green;' href='green'></a><a class='box' style='background-color: blue;' href='blue'></a><a class='box' style='background-color: white;border-color: gray' href='off'></div></body><style>.mycontainer{width: 100vw;height: auto;flex-wrap: wrap !important;flex-shrink: 0;}.box{border: 0.25rem solid transparent;transition: ease all 0.25s;margin: 2rem;width: 15rem !important;height: 15rem;}.box:active{border-color: black;}</style></html>");
  delay(1);
}
