#include <L298N.h>
#define BLYNK_TEMPLATE_NAME "test dinamo"
#define BLYNK_AUTH_TOKEN "7ydmmi59fWCBzsh1hr0OLBLLIEHjtY0r"
// const int motor1Pin1 = 5;  // Kontrol arah motor 1
// const int motor1Pin2 = 18;
// const int enaA = 23;       // Kontrol kecepatan motor 1

// const int motor2Pin3 = 19; // Kontrol arah motor 2
// const int motor2Pin4 = 21;
// const int enaB = 22;       // Kontrol kecepatan motor 2

// Motor driver pins
// const int motor1Pin1 = 5;
// const int motor1Pin2 = 18;
// const int enaA = 22;

const int motor2Pin3 = 19;
const int motor2Pin4 = 21;
const int enaB = 23;
// Setting PWM properties
const int freq = 30000;        // Frekuensi PWM
const int pwmChannelA = 0;     // Channel PWM untuk enaA
const int pwmChannelB = 0;     // Channel PWM untuk enaB
const int resolution = 8;      // Resolusi PWM (8-bit)

// Variabel duty cycle
int dutyCycle = 200;

void setup() {
  // Inisialisasi pin sebagai output
  // pinMode(motor1Pin1, OUTPUT);
  // pinMode(motor1Pin2, OUTPUT);
  // pinMode(enaA, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  pinMode(enaB, OUTPUT);

  // Setup PWM untuk masing-masing motor
  // ledcSetup(pwmChannelA, freq, resolution);
  // ledcAttachPin(enaA, pwmChannelA);

  ledcSetup(pwmChannelB, freq, resolution);
  ledcAttachPin(enaB, pwmChannelB);

  // Inisialisasi Serial Monitor
  Serial.begin(115200);
}

void loop() {
  // Gerakkan motor maju
  Serial.println("Moving Forward");
  // digitalWrite(motor1Pin1, HIGH);
  // digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin3, HIGH);
  digitalWrite(motor2Pin4, LOW);

  // ledcWrite(pwmChannelA, 230);  // Kecepatan awal motor 1
  ledcWrite(pwmChannelB, 230);  // Kecepatan awal motor 2
  delay(2000);

  // Hentikan motor
  Serial.println("Motor stopped");
  // digitalWrite(motor1Pin1, LOW);
  // digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, LOW);
  // ledcWrite(pwmChannelA, 0);
  ledcWrite(pwmChannelB, 0);
  delay(1000);

}
