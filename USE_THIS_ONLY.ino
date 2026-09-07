/*
 * Robot: Continuous Obstacle Avoidance + PIR Motion Alerts
 * PIR Pin: D11 | Ultrasonic: D8 (Trig), D9 (Echo)
 */

// --- Pins ---
const int pirPin = 11;    
const int in1 = 2;        // Motor A
const int in2 = 3;
const int ena = 5;
const int in3 = 4;        // Motor B
const int in4 = 7;
const int enb = 6;
const int trigPin = 8;    
const int echoPin = 9;

// --- Variables ---
int pirState = LOW;       
int val = 0;              

void setup() {
  // Motor Pins
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT); pinMode(ena, OUTPUT);
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT); pinMode(enb, OUTPUT);
  
  // Sensor Pins
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(pirPin, INPUT);
  
  Serial.begin(9600);
  Serial.println("--- System Online: Moving & Scanning ---");
}

void loop() {
  // 1. Check PIR Sensor for background alerts
  val = digitalRead(pirPin); 
  if (val == HIGH) {
    if (pirState == LOW) {
      Serial.println(">> ALERT: Human/Motion detected nearby! <<");
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) {
      Serial.println(">> Notice: Area is now still. <<");
      pirState = LOW;
    }
  }

  // 2. Obstacle Avoidance Logic (Always Running)
  float distance = getDistance();
  
  if (distance > 40) {
    Serial.println("Path Clear: Full Speed.");
    moveForward(255); 
  } 
  else if (distance <= 40 && distance > 20) {
    Serial.print("Object Ahead (");
    Serial.print(distance);
    Serial.println("cm): Slowing down...");
    moveForward(150); 
  } 
  else {
    Serial.println("!! OBSTACLE DETECTED !! Maneuvering...");
    stopMotors();
    delay(200);
    moveBackward(180); 
    delay(600);
    turnRight(200);   
    delay(600);
  }
  
  delay(50); 
}

// --- Movement Functions ---

void moveForward(int speed) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(ena, speed); analogWrite(enb, speed);
}

void moveBackward(int speed) {
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(ena, speed); analogWrite(enb, speed);
}

void turnRight(int speed) {
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
  analogWrite(ena, speed); analogWrite(enb, speed);
}

void stopMotors() {
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
  analogWrite(ena, 0);   analogWrite(enb, 0);
}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.0343 / 2;
}