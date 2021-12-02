#include <DHT.h> //DHT Bibliothek laden

//Define für den DHT11
#define DHTPIN 3 //Der Sensor wird an PIN 2 angeschlossen    
#define DHTTYPE DHT11    // Es handelt sich um den DHT11 Sensor

//Define für den WaterLevelSensor
#define sensorPower 7
#define sensorPin A1    //Pin des WaterLevelSensors auf A0

DHT dht(DHTPIN, DHTTYPE); //Der Sensor wird ab jetzt mit „dth“ angesprochen

// Value for storing water level
int val = 0;

//Value for storing moisture level
int IN1 = 2;
int Pin1 = A0; 
float value1 = 0;

void setup() {
  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  
  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);

  // Set Pins for MoistureSensor
  pinMode(IN1, OUTPUT);
  pinMode(Pin1, INPUT);

  digitalWrite(IN1, HIGH);

  delay(500);
  
//Setup für den DHT11
  Serial.begin(9600); //Serielle Verbindung starten

  dht.begin(); //DHT11 Sensor starten
}

void loop() {
  //Loop für den DHT 11
  delay(5000); //Zwei Sekunden Vorlaufzeit bis zur Messung (der Sensor ist etwas träge)

  
  float Luftfeuchtigkeit = dht.readHumidity(); //die Luftfeuchtigkeit auslesen und unter „Luftfeutchtigkeit“ speichern
  
  float Temperatur = dht.readTemperature();//die Temperatur auslesen und unter „Temperatur“ speichern

  //get the reading from the function below and print it
  int level = readSensor();
  
  Serial.print("Luftfeuchtigkeit: "); //Im seriellen Monitor den Text und 
  Serial.print(Luftfeuchtigkeit); //die Dazugehörigen Werte anzeigen
  Serial.println(" %");
  Serial.print("Temperatur: ");
  Serial.print(Temperatur);
  Serial.println(" Grad Celsius");
  Serial.print("Water level: ");
  Serial.println(level);
  Serial.print("Bodenfeuchtigkeit:");
  value1 = analogRead(Pin1);
  Serial.println(value1);
  if(value1>500)
  {
      digitalWrite(IN1, LOW);
  }
  else
  {
    digitalWrite(IN1, HIGH);
    }
    Serial.println();
  
  delay(1000);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}