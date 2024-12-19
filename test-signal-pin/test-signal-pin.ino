// motor driver
const int motor1Pin1 = 5;  // Kontrol arah motor 1
const int motor1Pin2 = 18;
const int enaA = 23;       // Kontrol kecepatan motor 1

const int motor2Pin3 = 19; // Kontrol arah motor 2
const int motor2Pin4 = 21;
const int enaB = 22;       // Kontrol kecepatan motor 2

// Setting PWM properties
const int freq = 30000;        // Frekuensi PWM
const int pwmChannelA = 0;     // Channel PWM untuk enaA
const int pwmChannelB = 1;     // Channel PWM untuk enaB
const int resolution = 8;      // Resolusi PWM (8-bit)

// Variabel duty cycle kecepatan
int dutyCycle = 200;
// sensor ultrasonic
const int trigPin = 25;
const int echoPin = 33;
long duration;
long distance;

//  servo
const int servoPin1 = 27; // Capit
const int servoPin2 = 14; // Servo Naik/Turun
const int servoPin3 = 26;  // Servo Rotasi (opsional)

void setup() {
  Serial.begin(115200); // Inisialisasi Serial Monitor

  pinMode(5, INPUT);  // Ganti '5' dengan nomor pin yang ingin dicek
}

void loop() {
  int pinStatus = digitalRead(5); // Membaca status pin
  if (pinStatus == HIGH) {
    Serial.println("Pin 5: HIGH"); // Pin terhubung ke sinyal HIGH
  } else {
    Serial.println("Pin 5: LOW"); // Pin terhubung ke sinyal LOW
  }
  delay(500); // Delay agar pembacaan lebih mudah dipantau
}