// motor driver
#include <L298N.h>
// servo
#include <ESP32Servo.h>
// wifi
// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL68EEdo8Q9"
#define BLYNK_TEMPLATE_NAME "test dinamo"
#define BLYNK_AUTH_TOKEN "7ydmmi59fWCBzsh1hr0OLBLLIEHjtY0r"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Redmi 13";
char pass[] = "belisendiri";

// Motor driver pins
const int motor1Pin1 = 21;
const int motor1Pin2 = 12;
const int enaA = 23;

const int motor2Pin3 = 18;
const int motor2Pin4 = 5;
const int enaB = 22;

// Setting PWM properties
const int freq = 30000;        
const int pwmChannelA = 0;     
const int pwmChannelB = 1;     
const int resolution = 8;      

// Variabel duty cycle kecepatan
int dutyCycle = 200;

// Sensor ultrasonic
const int trigPin = 25;
const int echoPin = 33;
long duration;
long distance;

// Servo pins
const int servoPin1 = 27; 
const int servoPin2 = 14; 
const int servoPin3 = 26; 

int pos1 = 180; 
int pos2 = 0; 
int pos3 = 0; 

Servo servo1; 
Servo servo2; 
Servo servo3; 

// Blynk button states
int valueForward = 0;
int valueBackward = 0;
int valueRight = 0;
int valueLeft = 0;

BLYNK_WRITE(V5) {
    dutyCycle = param.asInt();
}

BLYNK_WRITE(V1) {
    valueForward = param.asInt();
}

BLYNK_WRITE(V2) {
    valueBackward = param.asInt();
}

BLYNK_WRITE(V3) {
    valueRight = param.asInt();
}

BLYNK_WRITE(V4) {
    valueLeft = param.asInt();
}

void setup() {
    Serial.begin(115200);

    // Setup servo
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    servo1.write(pos1);

    // Setup motor driver
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enaA, OUTPUT);
    pinMode(motor2Pin3, OUTPUT);
    pinMode(motor2Pin4, OUTPUT);
    pinMode(enaB, OUTPUT);

    ledcSetup(pwmChannelA, freq, resolution);
    ledcAttachPin(enaA, pwmChannelA);

    ledcSetup(pwmChannelB, freq, resolution);
    ledcAttachPin(enaB, pwmChannelB);

    // Setup ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Setup Blynk
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
}

void moveForward() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin3, HIGH);
    digitalWrite(motor2Pin4, LOW);
    ledcWrite(pwmChannelA, dutyCycle);
    ledcWrite(pwmChannelB, dutyCycle);
}

void moveBackward() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, HIGH);
    ledcWrite(pwmChannelA, dutyCycle);
    ledcWrite(pwmChannelB, dutyCycle);
}

void moveRight() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, LOW);
    ledcWrite(pwmChannelA, dutyCycle);
    ledcWrite(pwmChannelB, dutyCycle / 2);
}

void moveLeft() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin3, HIGH);
    digitalWrite(motor2Pin4, LOW);
    ledcWrite(pwmChannelA, dutyCycle / 2);
    ledcWrite(pwmChannelB, dutyCycle);
}

void stopMotors() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, LOW);
    ledcWrite(pwmChannelA, 0);
    ledcWrite(pwmChannelB, 0);
}

void capitBuka() {
    for (; pos1 <= 180; pos1++) {
        servo1.write(pos1);
        delay(15);
    }
}

void capitTutup() {
    for (; pos1 >= 0; pos1--) {
        servo1.write(pos1);
        delay(15);
    }
}

void servoNaik() {
    for (; pos2 <= 180; pos2++) {
        servo2.write(pos2);
        delay(15);
    }
}

void servoTurun() {
    for (; pos2 >= 0; pos2--) {
        servo2.write(pos2);
        delay(15);
    }
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
    Blynk.run();

    if (valueForward) {
        moveForward();
        Serial.println("Maju");
    } else if (valueBackward) {
        moveBackward();
        Serial.println("Mundur");
    } else if (valueRight) {
        moveRight();
        Serial.println("Kanan");
    } else if (valueLeft) {
        moveLeft();
        Serial.println("Kiri");
    } else {
        stopMotors();
    }

    // Mengukur jarak dengan sensor ultrasonik
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = (duration * 0.0343) / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Menjalankan fungsi pengolahan sampah
    putTrash();
}
