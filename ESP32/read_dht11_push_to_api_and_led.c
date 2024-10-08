#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Define constants for display
#define i2c_Address 0x3c 
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1   
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define WiFi credentials
const char *ssid = "nguyentienphuc";
const char *password = "nguyentienphuc";

// Define DHT sensor
#define DHTPIN 4        
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

// API server
const char* serverName = "https://tienphuckx.ueuo.com/automotive/api-car-dashboard.php";

// Utility functions
void connectToWiFi() {
  Serial.print("[WiFi] Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  int tryDelay = 500;
  int numberOfTries = 20;
  
  while (WiFi.status() != WL_CONNECTED && numberOfTries > 0) {
    delay(tryDelay);
    Serial.print(".");
    numberOfTries--;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFi] Connected!");
    Serial.print("[WiFi] IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("[WiFi] Failed to connect.");
  }
}

void sendDataToAPI(float temperature, float humidity, float speed, float fuel, int gear, String gps) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String postData = "temperature=" + String(temperature) +
                      "&humidity=" + String(humidity) +
                      "&speed=" + String(speed) +
                      "&fuel=" + String(fuel) +
                      "&gear=" + String(gear) +
                      "&gps=" + gps;

    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  // HTTP header

    // Send the POST request
    int httpResponseCode = http.POST(postData);

    // Check for success
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode); 
      Serial.println(response);       
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
}

void displayData(float humidity, float temperatureC, float speed, float fuel, int gear, String gps) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.print("Humidity: ");
  display.print(humidity);
  display.print("%\nTemp: ");
  display.print(temperatureC);
  display.print(" C\nFuel: ");
  display.print(fuel);
  display.print("\nSpeed: ");
  display.print(speed);
  display.print("\nGear: ");
  display.print(gear);
  display.print("\nGPS: ");
  display.print(gps);

  display.display();
}

void printLog(float humidity, float temperatureC, float speed, float fuel, int gear, String gps) {
  Serial.print("\nHumidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperatureC);
  Serial.println("°C");

  Serial.print("Speed: ");
  Serial.print(speed);
  Serial.print("\nFuel: ");
  Serial.print(fuel);
  Serial.print("\nGear: ");
  Serial.print(gear);
  Serial.print("\nGPS: ");
  Serial.print(gps);
}

float getRandomValue(float from, float to) {
  return random(from * 10, (to * 10) + 1) / 10.0;
}

float getRandomSpeed() {
  return getRandomValue(50.1, 199.5);
}

float getRandomFuel() {
  return getRandomValue(10.7, 99.7);
}

int getRandomGear() {
  return (int)getRandomValue(1, 6);
}

String getRandomGPS(float baseLat, float baseLon) {
  float latOffset = random(-1000, 1001) / 100000.0;
  float lonOffset = random(-1000, 1001) / 100000.0;
  float newLat = baseLat + latOffset;
  float newLon = baseLon + lonOffset;
  return String(newLat, 6) + "," + String(newLon, 6);
}

void setup() {
  Serial.begin(9600);
  dht.begin(); 
  connectToWiFi();

  // Initialize the display
  display.begin(i2c_Address, true); 
  display.display(); 
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float humidity = dht.readHumidity();
    float temperatureC = dht.readTemperature();

    float speed = getRandomSpeed();
    float fuel = getRandomFuel();
    int gear = getRandomGear();
    String gps = getRandomGPS(37.7749, -122.4194);

    if (isnan(humidity) || isnan(temperatureC)) {
      Serial.println("ERROR: Failed to read from DHT sensor!");
      return;
    }

    printLog(humidity, temperatureC, speed, fuel, gear, gps);
    displayData(humidity, temperatureC, speed, fuel, gear, gps); // for LCD OLED
    sendDataToAPI(temperatureC, humidity, speed, fuel, gear, gps); // send data to server

  } else {
    Serial.println("ERROR: WiFi not connected. Attempting to reconnect...");
    connectToWiFi();
  }

  delay(3000);
}
