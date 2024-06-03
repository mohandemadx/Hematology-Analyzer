// Sensor pins
#define sensorPower1 7
#define sensorPower2 9
#define sensorPin1 A0
#define sensorPin2 A1
#define condRead A5

// LED pins

#define waterpump1 10 // Change the pin number according to your setup
#define waterpump2 11  // Change the pin number according to your setup

const int threshold1 = 400;
const int threshold2 = 650;

// Values for storing water levels
int val1 = 0;
int val2 = 0;

void setup() {
    // Set sensor power pins as OUTPUT
    pinMode(sensorPower1, OUTPUT);
    pinMode(sensorPower2, OUTPUT);
    
     // Set LED pins as OUTPUT
    pinMode(waterpump1, OUTPUT);
    pinMode(waterpump2, OUTPUT);


    // Set sensor power pins to LOW initially
    digitalWrite(sensorPower1, LOW);
    digitalWrite(sensorPower2, LOW);
    digitalWrite(waterpump1, LOW);
    digitalWrite(waterpump2, LOW);

    Serial.begin(9600);
}

void loop() {
    // Read water levels from both sensors
    int level1 = readSensor(sensorPower1, sensorPin1);
    int level2 = readSensor(sensorPower2, sensorPin2);
    int Voltvalue;
    float solution_resistance;
    // Check if water level is below threshold for sensor 1
    if (level2 > threshold2) {
        digitalWrite(waterpump1, HIGH); // Activate LED for sensor 1
    } else {
        digitalWrite(waterpump1, LOW); // Deactivate LED for sensor 1
    }

    // Check if water level is below threshold for sensor 2
    if (level1 > threshold1) {
        digitalWrite(waterpump2, HIGH); // Activate LED for sensor 2
    } else {
        digitalWrite(waterpump2, LOW); // Deactivate LED for sensor 2
    }

    Serial.print("Water level 1: ");
    Serial.println(level1);
    Serial.print("Water level 2: ");
    Serial.println(level2);
    if (level1< threshold1){
      if (level2< threshold2){
        Voltvalue = readCond(condRead);
        solution_resistance= ((1024 - Voltvalue)*(3300.0))/(Voltvalue);
        Serial.print("Number of Red Blood Cells:");
        Serial.println(((1/40.0) * solution_resistance));
      }
    }
    

    delay(10000);
}

// Function to read sensor
int readSensor(int powerPin, int sensorPin) {
    digitalWrite(powerPin, HIGH);   // Turn the sensor ON
    delay(10);                       // Wait 10 milliseconds
    int val = analogRead(sensorPin); // Read the analog value from sensor
    digitalWrite(powerPin, LOW);     // Turn the sensor OFF
    return val;                      // Return current reading
}


int readCond(int sensorPin){

  int val;
  digitalWrite(condRead, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(condRead,LOW);
  return val;



}
