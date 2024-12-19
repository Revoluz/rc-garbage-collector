// test servo
// servo
#include <ESP32Servo.h>
//  servo
const int servoPin1 = 27; // Capit
const int servoPin2 = 26; // Servo Naik/Turun
const int servoPin3 = 14;  // Servo Rotasi (opsional)
// sensor ultrasonic
const int trigPin = 25;
const int echoPin = 33;
long duration;
long distance;

int pos1 = 180; // Posisi servo capit
int pos2 = 0; // Posisi servo naik/turun
int pos3 = 0; // Posisi servo rotasi (opsional)

Servo servo1; // Servo capit
Servo servo2; // Servo naik/turun
Servo servo3; // Servo naik/turun
void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);
  // setup servo
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Hello, ESP32!");
  servo1.write(pos1);
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
    servo3.write(pos2);
    servo2.write(pos2);
    delay(15);
  }
}

void servoTurun() {
  for (; pos2 >= 0; pos2--) {
    servo3.write(pos2);
    servo2.write(pos2);
    delay(15);
  }
}

void putTrash() {
  if(distance > 0 && distance <= 49) {
    Serial.println("Closing claw...");
    capitTutup(); // Menutup capit
    delay(1000);

    Serial.println("Lifting arm...");
    servoNaik(); // Mengangkat servo
    delay(1000);

    Serial.println("Dropping trash...");
    servoTurun(); // Menurunkan servo
    delay(1000);

    Serial.println("Releasing trash...");
    capitTutup(); // Membuka capit
    delay(1000);
  }
}

void loop() {
    // Mengukur jarak menggunakan sensor ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2; // Konversi ke cm

  // Menampilkan jarak di Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Menjalankan fungsi pengolahan sampah
  putTrash();
}
