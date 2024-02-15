#include <DHT.h>
#define DHTPIN 2  // Pin where the DHT11 is connected
#define DHTTYPE DHT11  // DHT 11 sensor type
#define RELAY_PIN 13  // Pin where the relay module is connected

DHT dht(DHTPIN, DHTTYPE);
float humidity;
int relayState = LOW;
float thresholdTemperature = 30.0;  // Set your desired temperature threshold here

void setup() {
  
  Serial.begin(115200);
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
}

void loop() {
  delay(2500);  // Delay between sensor readings

  // Read temperature from DHT11 sensor
  humidity = dht.readHumidity();

  // Check if temperature reading is successful
  if (isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.println(humidity);

  // Check if the temperature is above the threshold
  if (humidity > thresholdTemperature) {
    // Activate the relay
    digitalWrite(RELAY_PIN, HIGH);
    relayState = HIGH;
    Serial.println("Relay activated!");
    delay(2500);
    digitalWrite(RELAY_PIN, LOW);
    relayState = LOW;
  } else {
    // Deactivate the relay
    digitalWrite(RELAY_PIN, LOW);
    relayState = LOW;
    Serial.println("Relay deactivated!");
    
  }

  //delay(5000);  // Delay before next sensor reading
}