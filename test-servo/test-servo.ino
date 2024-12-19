#include <ESP32Servo.h>

// Servo
const int servoPin1 = 14; // Capit
const int servoPin2 = 26; // Naik/Turun
const int servoPin3 = 27; // Rotasi (opsional)
const int trigPin = 25;
const int echoPin = 33;

long duration;
float distance;

int pos1 = 180; // Posisi capit
int pos2 = 0;   // Posisi naik/turun
int pos3 = 0;   // Posisi rotasi (opsional)

Servo servo1; 
Servo servo2; 
Servo servo3; 

void setup() {
    Serial.begin(115200);

    // Setup servo
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);

    servo1.write(pos1); 
    servo2.write(pos2); 
    servo3.write(pos3);

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.println("System Ready");
}

void capitBuka() {
    for (int i = pos1; i <= 180; i++) {
        servo1.write(i);
        delay(15);
    }
    pos1 = 180;
}

void capitTutup() {
    for (int i = pos1; i >= 0; i--) {
        servo1.write(i);
        delay(15);
    }
    pos1 = 0;
}

void servoNaik() {
    for (int i = pos2; i <= 180; i++) {
        servo2.write(i);
        servo3.write(i);
        delay(15);
    }
    pos2 = 180;
}

void servoTurun() {
    for (int i = pos2; i >= 0; i--) {
        servo2.write(i);
        servo3.write(i);
        delay(15);
    }
    pos2 = 0;
}

float getDistance() {
    long totalDistance = 0;
    for (int i = 0; i < 5; i++) {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        long duration = pulseIn(echoPin, HIGH);
        totalDistance += (duration * 0.0343) / 2;
        delay(50);
    }
    return totalDistance / 5;
}

void putTrash() {
    if (distance > 0 && distance <= 49) {
        Serial.println("Closing claw...");
        capitTutup();
        delay(1000);

        Serial.println("Lifting arm...");
        servoNaik();
        delay(1000);

        Serial.println("Dropping trash...");
        servoTurun();
        delay(1000);

        Serial.println("Releasing trash...");
        capitBuka();
        delay(1000);
    }
}

void loop() {
    distance = getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance <= 49) {
        putTrash();
    } else {
        Serial.println("No object detected. Waiting...");
        delay(1000);
    }
}
