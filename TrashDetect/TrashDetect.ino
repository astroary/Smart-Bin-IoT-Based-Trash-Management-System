/* 
 Name: Aryansingh Chauhan, Ackchat Omar
 Net ID: achauh9, aomar22
 Group/Team #: 85
 Abstract: Bored of checking when to take out the trash? Introducing a smart trash management system that eradicates the need to constantly keep on checking how much trash is occupied in the bin.
           With today’s technology, the smart trash will notify the user via different output methods that trash needs to be removed. By having the user notified without having them open the bin themselves to check trash levels,
           The aim is to reduce daily human effort and at the same time make sure trash is being removed from households rather than being collected.
 Project name: Smart Bin
 Project Description: Using ultrasonic sensors, I am calculating the trash stored in a bin and communicating it to the
                      user via different output devices so that they are aware of when to clear out the trash.
 References: https://docs.arduino.cc/built-in-examples/sensors/Ping
*/

// Sensor 1 pin numbers
const int trigPin1 = 8;
const int echoPin1 = 7;
// Sensor 2 pin numbers
const int trigPin2 = 11;
const int echoPin2 = 12;
// Sensor 3 pin numbers
const int trigPin3 = 3;
const int echoPin3 = 4;
// Push button pin numbers
const int button1 = 10;
const int button2 = 9;
// boolean to indicate when trash is being detected
bool isStarted = false;

// defines variables
int d0 = -1; // Original Distance of the bin. At start it is set to -1
long duration1;
int distance1;
long duration2;
int distance2;
long duration3;
int distance3;
int curDist;

void setup() {

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

  pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin3, INPUT); // Sets the echoPin as an Input

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  
  Serial.begin(9600); // Starts the serial communication
}

// helper function that calculates distance for a given sensor
int sensorDetect(int trigpin, int echoPin) {
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);  // delay to ensure that the sensors don't interrupt each others readings
  digitalWrite(trigpin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void loop() {

  if (digitalRead(button1) == HIGH && d0 == -1) {  // Button 1 when pressed
      // Button 1 is pressed to detect height of bin/d0 uisng the 3 sensors
      distance1 = sensorDetect(trigPin1, echoPin1);
      delay(100);
      distance2 = sensorDetect(trigPin2, echoPin2);
      delay(100);
      distance3 = sensorDetect(trigPin3, echoPin3);
    // Calculating average of distances:
      d0 = (distance1 + distance2 + distance3)/3;
      delay(500);  // Debounce delay      
  }

  // Button 2 when pressed i.e. we are now detecting trash
  if (digitalRead(button2) == HIGH && !isStarted && d0 != -1) {
    isStarted = true;
  }

  if (isStarted) { // checking if we are now detecting trash
      distance1 = sensorDetect(trigPin1, echoPin1);
      delay(100);
      distance2 = sensorDetect(trigPin2, echoPin2);
      delay(100);
      distance3 = sensorDetect(trigPin3, echoPin3);
      curDist = (distance1 + distance2 + distance3) / 3;
      delay(5000);
      float trashPercentage = (float(d0 - curDist) / float(d0)) * 100.0;
      if (trashPercentage < 0.0) {
        trashPercentage = 0.0;
      }

      // Serial.print("Trash Filled Percentage: ");
      Serial.println(trashPercentage);  // sending data to second arduino
  }
    delay(1000);
}