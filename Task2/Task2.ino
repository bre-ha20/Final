#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define SDA 13 //Define SDA pins 
#define SCL 14 //Define SCL pins
#define LED 2

// WiFi
const char *ssid = "Ha's Network"; // Enter your WiFi name
const char *password = "Dragon@7276";  // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esp32/test";
const char *mqtt_username = "bre";
const char *mqtt_password = "ha";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  Wire.begin(SDA, SCL);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Pick a #1-10!");

  pinMode(LED, OUTPUT);
  
 // Set software serial baud to 115200;
 Serial.begin(115200);
 // connecting to a WiFi network
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_broker, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 // publish and subscribe
 client.publish(topic, "Pick a Number 1-10");
 client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 String message;
 for (int i = 0; i < length; i++) {
     message = message + (char) payload[i];
 }

 //Nice messages
 if (message == "1"){
  digitalWrite(LED, LOW); //led off
  lcd.setCursor(0,1);
  lcd.print("Your Amazing");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "2"){
  digitalWrite(LED, HIGH); //led on
  lcd.setCursor(0,1);
  lcd.print("Big head");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "3"){
  digitalWrite(LED, LOW); //led off
  lcd.setCursor(0,1);
  lcd.print("I love you!");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "4"){
  digitalWrite(LED, LOW); //led off
  lcd.setCursor(0,1);
  lcd.print("Go get em!");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "5"){
  digitalWrite(LED, LOW); //led off
  lcd.setCursor(0,1);
  lcd.print("Don't give up!");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "6"){
  digitalWrite(LED, HIGH); //led on
  lcd.setCursor(0,1);
  lcd.print("You stink :/");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "7"){
  digitalWrite(LED, HIGH); //led on
  lcd.setCursor(0,1);
  lcd.print("Haha loser");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "8"){
  digitalWrite(LED, LOW); //led off
  lcd.setCursor(0,1);
  lcd.print("Beautiful");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "9"){
  digitalWrite(LED, HIGH); //led on
  lcd.setCursor(0,1);
  lcd.print("Hey ugly");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 if (message == "10"){
  digitalWrite(LED, LOW); //led off
  lcd.setCursor(0,1);
  lcd.print("Ur doing great!");
  delay(3000);
  lcd.setCursor(0,1);
  lcd.print("                ");
 }
 
 Serial.println();
 Serial.println("-----------------------");
 
}

void loop() {
 client.loop();
}
