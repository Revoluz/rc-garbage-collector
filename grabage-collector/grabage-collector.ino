// Motor driver
#include <L298N.h>
// Servo
#include <ESP32Servo.h>
// Blynk
#define BLYNK_TEMPLATE_ID "TMPL68EEdo8Q9"
#define BLYNK_TEMPLATE_NAME "test dinamo"
#define BLYNK_AUTH_TOKEN "7ydmmi59fWCBzsh1hr0OLBLLIEHjtY0r"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "A25";
char pass[] = "fanan123";

// Motor driver pins
const int motor1Pin1 = 5;
const int motor1Pin2 = 18;
const int enaA = 22;
const int motor2Pin3 = 19;
const int motor2Pin4 = 21;
const int enaB = 23;

// PWM properties
const int freq = 30000;        // Frekuensi PWM
const int pwmChannelA = 0;     // Channel PWM untuk enaA
const int pwmChannelB = 1;     // Channel PWM untuk enaB
const int resolution = 8;      // Resolusi PWM (8-bit)
int dutyCycle = 200;           // Default duty cycle

// Ultrasonic sensor pins
const int trigPin = 25;
const int echoPin = 33;

// Servo pins
const int servoPin1 = 14; // Capit
const int servoPin2 = 26; // Servo Naik/Turun 
const int servoPin3 = 27; // Servo Rotasi (opsional) kebalik



// Servo positions
int pos1 = 0; // Posisi servo capit
int pos2 = 0;   // Posisi servo naik/turun
int pos3 = 180;   // Posisi servo rotasi (opsional)

// Servo instances
Servo servo1;
Servo servo2;
Servo servo3;
// Ultrasonic distance
long duration;
float distance;

// Motor movement values
int valueForward = 0;
int valueBackward = 0;
int valueRight = 0;
int valueLeft = 0;

// Blynk virtual pin handlers
BLYNK_WRITE(V1) { valueForward = param.asInt(); }
BLYNK_WRITE(V2) { valueBackward = param.asInt(); }
BLYNK_WRITE(V3) { valueRight = param.asInt(); }
BLYNK_WRITE(V4) { valueLeft = param.asInt(); }
BLYNK_WRITE(V5) { dutyCycle = param.asInt(); }

// Motor movement functions
void moveForward() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, HIGH);
    ledcWrite(pwmChannelA, dutyCycle); // roda kiri
    ledcWrite(pwmChannelB, dutyCycle); // roda kanan
}

void moveBackward() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin3, HIGH);
    digitalWrite(motor2Pin4, LOW);
    ledcWrite(pwmChannelA, dutyCycle);
    ledcWrite(pwmChannelB, dutyCycle);
}

void moveRight() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, HIGH);
    ledcWrite(pwmChannelA, dutyCycle);
    ledcWrite(pwmChannelB, dutyCycle/2.5);
}

void moveLeft() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin3, LOW);
    digitalWrite(motor2Pin4, HIGH);
    ledcWrite(pwmChannelA, dutyCycle/2.5 );
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

// Servo functions
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



// Ultrasonic sensor function
float getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms
    return (duration * 0.0343) / 2;
}

// Trash handling function
void putTrash() {
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

void setup() {
    Serial.begin(115200);

    // Initialize motor driver pins
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor2Pin3, OUTPUT);
    pinMode(motor2Pin4, OUTPUT);
    ledcSetup(pwmChannelA, freq, resolution);
    ledcAttachPin(enaA, pwmChannelA);
    ledcSetup(pwmChannelB, freq, resolution);
    ledcAttachPin(enaB, pwmChannelB);

    // Initialize Blynk
    Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);

    // Initialize servo
    servo1.attach(servoPin1);
    servo2.attach(servoPin2);
    servo3.attach(servoPin3);
    servo1.write(pos1);
    servo2.write(pos2);
    servo3.write(pos3);

    // Initialize ultrasonic sensor
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);


    Serial.println("Setup complete.");
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


    // Ultrasonic distance measurement
    distance = getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Trash handling based on distance
    if (distance > 0 && distance <= 5) {
        putTrash();
        delay(1000);
    } else {
        Serial.println("No object detected. Waiting...");
        delay(1000);
    }
}
