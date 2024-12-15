#include <L298N.h>

/*************************************************************
 Note: If you don't have the ESP32-S in your IDE 'Boards Manager' 
 and cannot search for it,
 then please copy and paste the following URLS 
 to your 'Additional Boards Manager' 
 under Arduino IDE -> Settings...:

 Once added, try searching for and adding 'ESP32' boards to Arduino IDE.
 GOOD LUCK! 
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID "TMPL68EEdo8Q9"
#define BLYNK_TEMPLATE_NAME "test dinamo"
#define BLYNK_AUTH_TOKEN "7ydmmi59fWCBzsh1hr0OLBLLIEHjtY0r"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "BeeCraft";
char pass[] = "yaelahcoy";

// Pin untuk motor
const int motor1Pin1 = 5;  // Kontrol arah motor 1
const int motor1Pin2 = 18;
const int enaA = 23;       // Kontrol kecepatan motor 1

const int motor2Pin3 = 19; // Kontrol arah motor 2
const int motor2Pin4 = 21;
const int enaB = 22;       // Kontrol kecepatan motor 2

// Setting PWM properties
const int freq = 5000;        // Frekuensi PWM (disarankan untuk L298N)
const int pwmChannelA = 0;    // Channel PWM untuk enaA
const int pwmChannelB = 1;    // Channel PWM untuk enaB
const int resolution = 8;     // Resolusi PWM (8-bit)

// Duty cycle default
int dutyCycle = 200;

// Fungsi Blynk untuk move forward
BLYNK_WRITE(V1) {  // Slider pada Virtual Pin V1
  int sliderValue = param.asInt(); // Nilai dari slider (0-255)
  Serial.println("Move Forward");

  // Atur arah motor maju
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin3, LOW);
  digitalWrite(motor2Pin4, HIGH);

  // Atur kecepatan motor
  ledcWrite(pwmChannelA, dutyCycle);
  ledcWrite(pwmChannelB, dutyCycle);
}

void setup() {
  // Inisialisasi Serial Monitor
  Serial.begin(115200);

  // Inisialisasi pin sebagai output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enaA, OUTPUT);
  pinMode(motor2Pin3, OUTPUT);
  pinMode(motor2Pin4, OUTPUT);
  pinMode(enaB, OUTPUT);

  // Setup PWM untuk masing-masing motor
  ledcSetup(pwmChannelA, freq, resolution);
  ledcAttachPin(enaA, pwmChannelA);

  ledcSetup(pwmChannelB, freq, resolution);
  ledcAttachPin(enaB, pwmChannelB);

  // Inisialisasi Blynk
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 8080);
}

void loop() {
  Blynk.run(); // Jalankan koneksi Blynk
}
