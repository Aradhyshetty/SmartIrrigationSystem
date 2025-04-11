#include <DHT.h>
#include <Servo.h>
#include <UbidotsESPMQTT.h>
#include <Servo.h>
Servo myservo;
#define soilPin A0
#define DHTPin 4
#define DHTTYPE DHT22
#define relayPin D5
#define waterPin A0
//d5
DHT dht(DHTPin, DHTTYPE);

#define r_hum 80  //actual 70
#define r_temp 30
#define r_moist 50

#define w_hum 80  //actual 50
#define w_temp 25
#define w_moist 50

int soilPerc;
float humidity;
float temperature;
int cropType=-1;
int pos;
int pumpState=0;

#define TOKEN "BBUS-vdfjlVjQ24UqTxUS8Y5e9hBW18wPrL"  // Your Ubidots TOKEN
#define WIFINAME "RK"                                // Your SSID
#define WIFIPASS "12345678"                          // Your Wifi Pass

Ubidots client(TOKEN);
// Soil Moisture Thresholds
// const int RagimoistureThreshold = 400;
// Adjust based on your soil moisture sensor
/****************************************
 * Auxiliar Functions
 ****************************************/
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  char payloadString[length + 1];  // Create a buffer to store the payload as a string
  for (unsigned int i = 0; i < length; i++) {
    payloadString[i] = (char)payload[i];  // Copy payload data to buffer
  }
  payloadString[length] = '\0';  // Null-terminate the string

  // Convert the string to a float (if needed)
  int value = atoi(payloadString);  // Convert string to int

  // Print only the value
  Serial.print("Value: ");
  Serial.println(value);
  cropType  = 0;
  Serial.println("CropType is :");
  Serial.println(cropType);
}
void setup() {
  Serial.begin(115200);
  myservo.attach(D4);
  client.setDebug(true);  // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  client.ubidotsSubscribe("esp8266", "source1");
  dht.begin();
  pinMode(soilPin, INPUT);
  pinMode(DHTPin, INPUT);
  pinMode(waterPin, INPUT);
  pinMode(relayPin, OUTPUT);
  Serial.println("Smart irrigation System Started");
}
void loop() {
  myservo.write(180);
  int soilValue = analogRead(soilPin);
  soilPerc = map(soilValue, 0, 1023, 100, 0);
  Serial.print("Soil moisture in percentage:");
  Serial.println(soilPerc);
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.println(" %");
  int status = 200;
  status = analogRead(waterPin);
  int percentage = map(status, 200, 800, 0, 100);
  Serial.print("Water level:");
  Serial.println(percentage);
  if (status> 200) {
    if (cropType==0) 
    {
        Serial.println("Irrigation for Raagi");
        crop(r_hum, r_temp, r_moist);
    }
    else if(cropType==1)
    {
        Serial.println("Irrigation for wheat");
        crop(w_hum, w_temp, w_moist);
    }
    else
    {

        Serial.println("No crop selected");
        crop(r_hum, r_temp, r_moist);
      
    }
  } else {
    Serial.println("Water tank is empty.Please fill the tank");
    delay(5000);
  }
  if (!client.connected()) {
    client.reconnect();
    client.ubidotsSubscribe("esp8266", "source1");  // Insert the dataSource and Variable's Labels
  }
  client.add("temp", temperature);
  client.add("humidity", humidity);
  client.add("water_level", percentage);
  client.add("Soil_moisture", soilPerc);
  client.add("Pump_Status",pumpState);

  client.ubidotsPublish("source1");
  client.loop();
  delay(5000);
}
void crop(int hum, int temp, int moist) {
  Serial.println("====================================================================");
  Serial.println("Starting  phase 1");
  if ((soilPerc < moist) && (humidity < hum && temperature < temp)) {
    Serial.print("Soil moisture: ");
    Serial.println(soilPerc);
    Serial.println("Land is dry");
    delay(1000);
    Serial.println("Water pump is Starting...");
    delay(2000);
    digitalWrite(relayPin, HIGH);
    Serial.println("Supplying water............");
    pumpState=1;
   
    delay(5000);
    digitalWrite(relayPin, LOW);
    Serial.println("Pump is Off");
    pumpState=0;
  
    Serial.println("========================Water is supplied.Check Soil moisture Again========================");
    delay(1000);
  }

  else {
    Serial.println("Phase 1 is watered ");
    Serial.println(" Checking phase 2 soil moisture level.....");
    delay(2000);
    int soilPerc2 = 30;
    Serial.print("Soil moisture of phase 2:");
    Serial.println(soilPerc2);
    if ((soilPerc2 < moist) || (humidity < hum && temperature < temp)) {
      Serial.println("Land is dry");
      delay(2000);
      Serial.println("Valve is opening for phase 2.....");
      myservo.write(0);
      Serial.println("Valve is opened");
      digitalWrite(relayPin, HIGH);
      Serial.println("Supplying water............");
      pumpState=1;
      client.add("Pump_Status", pumpState); // Send the ON state to Ubidots
    client.ubidotsPublish("source1");

      delay(5000);
      digitalWrite(relayPin, LOW);
      Serial.println("Pump is Off");
      pumpState=0;
      client.add("Pump_Status", pumpState); // Send the ON state to Ubidots
    client.ubidotsPublish("source1");

      delay(2000);
      Serial.println("========================Water is supplied.===========================");
      delay(1000);
    } else {
      Serial.println(" Phase 2 is watered.");
      delay(2000);
    }
  }
}