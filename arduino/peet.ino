
// Library
#include <LCD_I2C.h>
#include <WiFiS3.h>
#include <PubSubClient.h>

//Lcd variable
LCD_I2C lcd(0x27, 16, 2);

//mqtt variable
const char MQTT_BROKER_ADRRESS[] = "test.mosquitto.org";  // CHANGE TO MQTT BROKER'S ADDRESS
const int MQTT_PORT = 1883;
const String MQTT_CLIENT_ID = String(random(1000, 9999));

const String SUBSCRIBE_TOPIC = "Phycom/Peet/" + MQTT_CLIENT_ID;

WiFiClient network;
PubSubClient client(network);

// abstract Function
void showLCD();
void connectWifi();
void connectMqtt();
void spin(char* topic, byte* payload, unsigned int length);

// Default function
void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(9,  OUTPUT); 

  showLCD("Starting.", "");
  delay(1000);
  connectWifi();
  connectMqtt();
}

void loop() {
  client.loop();
}

// Function
void showLCD(String text1, String text2) {
  lcd.clear();
  lcd.print(text1);
  lcd.setCursor(0, 1);
  lcd.print(text2);
}

void connectWifi() {
  const char* ssid = "2.4G_LIA-2101";   // Your SSID
  const char* password = "0950812772";  // Your Password

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    showLCD("Waiting WiFi.", "");
    delay(500);
    showLCD("Waiting WiFi..", "");
    delay(500);
    showLCD("Waiting WiFi...", "");
  }

  showLCD("WiFi Connected.", "");
}

void connectMqtt() {
  // Connect to the MQTT broker
  client.setServer(MQTT_BROKER_ADRRESS, MQTT_PORT);

  // Create a handler for incoming messages
  client.setCallback(spin);
   
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(MQTT_CLIENT_ID.c_str())) {
      showLCD(MQTT_CLIENT_ID, "");
      Serial.println(SUBSCRIBE_TOPIC.c_str());
      client.subscribe(SUBSCRIBE_TOPIC.c_str());
    } else {
      showLCD("Waiting.", "");
      delay(5000);
    }
  }
}

void spin(char* topic, byte* payload, unsigned int length) {
  analogWrite(9, 100);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);

  delay(200);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  delay(2000);

  analogWrite(9, 150);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);

  delay(305);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  delay(1000);
}