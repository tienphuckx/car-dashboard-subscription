#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Wi-Fi credentials in my Iphone
const char *ssid = "nguyentienphuc";
const char *password = "nguyentienphuc";

// DHT sensor config
#define DHTPIN 4        // this Pin for connected to the DHT sensor
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
const char* serverName = "https://tienphuckx.ueuo.com/automotive/api-car-dashboard.php";

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

void send_data_to_api(float temperature, float humidity, float speed, float fuel, int gear, String gps) {
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
    int httpResponseCode = http.POST(postData);
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

void setup() {
  Serial.begin(9600);
  dht.begin(); 
  connectToWiFi(); 
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
  float latOffset = (random(-1000, 1001)) / 100000.0; // Random offset from -0.01000 to +0.01000
  float lonOffset = (random(-1000, 1001)) / 100000.0; // Random offset from -0.01000 to +0.01000
  float newLat = baseLat + latOffset;
  float newLon = baseLon + lonOffset;
  return String(newLat, 6) + "," + String(newLon, 6);
}

void print_log(float humidity, float temperatureC, float speed, float fuel,int gear,String gps) {
    Serial.print("\nHumidity: ");
    Serial.print(humidity);
    
    Serial.print("\n%  Temperature: ");
    Serial.print(temperatureC);
    Serial.println("°C");

    Serial.print("\nSpeed: ");
    Serial.print(speed);

    Serial.print("\nFuel: ");
    Serial.print(fuel);

    Serial.print("\nGear: ");
    Serial.print(gear);

    Serial.print("\nGPS: ");
    Serial.print(gps);
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    
    // real time data from sensor
    float humidity = dht.readHumidity();
    float temperatureC = dht.readTemperature();
    
    // fake data (will be available in other version)
    float speed = getRandomSpeed(); 
    float fuel = getRandomFuel();  
    int gear = getRandomGear(); 
    String gps = getRandomGPS(37.7749, -122.4194);

    if (isnan(humidity) || isnan(temperatureC)) {
      Serial.println("ERROR: Failed to read from DHT sensor!");
      return;
    }
    print_log(humidity, temperatureC, speed, fuel, gear, gps);
    send_data_to_api(temperatureC, humidity, speed, fuel, gear, gps);
  } else {
    Serial.println("ERROR: WiFi not connected. Attempting to reconnect...");
    connectToWiFi();
  }
  delay(5000);
}
