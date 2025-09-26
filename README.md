## 🚨 Ultrasonic Distance Sensor with LED Warning System

This project uses an **HC-SR04 ultrasonic sensor** to measure distance and control LEDs based on the detected range.
Goal: As an object gets closer to the sensor, the **warning LED** blinks faster. When the object is far enough, the **safe LED** stays ON.

---

### ⚡ Features

* **Error distance (<10cm):** Warning LED blinks very fast, ERROR.
* **Too Close distance (<20cm):** Warning LED blinks fast, TOO CLOSE.
* **Close distance (<30cm):** Warning LED blinks little bit fast, CLOSE.
* **Safe distance (≥30cm):** No danger, Safe LED stays ON, SAFE.

---

### 🔌 Wiring

| Pin            | Arduino | Description            |
| -------------- | ------- | ---------------------- |
| TRIG\_PIN      | 2       | Ultrasonic sensor TRIG |
| ECHO\_PIN      | 3       | Ultrasonic sensor ECHO |
| LED\_PIN       | 4       | Warning LED            |
| SAFE\_LED\_PIN | 5       | Safe LED               |
| SCL\_OLED\_SCR | A5      | OLED                   |
| SDA\_OLDE\_SCR | A4      | OLED                   |

---

### 🛠 Required Components

* 1x Arduino (Uno, Nano, or compatible)
* 1x HC-SR04 Ultrasonic Sensor
* 2x LEDs (Red = Warning, Green = Safe)
* 1x 0.96 inç I2C OLED Ekran
* 2x 10K resistors
* Breadboard + jumper wires

---

### 📜 Code

The code is ready to upload 👇

```cpp
#define TRIG_PIN 2
#define ECHO_PIN 3
#define LED_PIN 4        
#define SAFE_LED_PIN 5   

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long previousMillis = 0;
unsigned long ledInterval = 500; 
bool ledState = LOW;

long distanceCalculator() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  return pulseIn(ECHO_PIN, HIGH) * 0.0343 / 2;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SAFE_LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 bulunamadi"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  long distance = distanceCalculator();
  Serial.print("Distance: ");
  Serial.println(distance);

  display.clearDisplay();
  display.setCursor(0,10);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");

  String durum;
  if(distance < 10){
    durum = "ERROR!";
    ledInterval = 100; 
    digitalWrite(SAFE_LED_PIN, LOW);
  } 
  else if(distance < 20){
    durum = "TOO CLOSE";
    ledInterval = 300;
    digitalWrite(SAFE_LED_PIN, LOW);
  }
  else if(distance < 30){
    durum = "CLOSE";
    ledInterval = 500;
    digitalWrite(SAFE_LED_PIN, LOW);
  }
  else {
    durum = "SAFE";
    digitalWrite(LED_PIN, LOW);
    digitalWrite(SAFE_LED_PIN, HIGH);
    ledState = LOW; 
  }

  display.setCursor(0,30);
  display.println(durum);
  display.display();

  if(distance < 30){
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= ledInterval){
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  }
}

```

---

### 🎯 How It Works

1. The **TRIG pin** is pulsed HIGH for 10μs → sensor sends out an ultrasonic wave.
2. The **ECHO pin** receives the reflected signal → distance is calculated.
3. Based on the distance:

   * Warning LED blinks very fast (ERROR)
   * Warning LED blinks little bit fast (TOO CLOSE)
   * Warning LED blinks fast (CLOSE)
   * Safe LED stays ON (SAFE)

---

### 🚀 Possible Improvements

* Add a buzzer for sound alerts.
* Use an RGB LED for color-coded warnings.

---

### 🤙 Done Improvements

* Display distance on an LCD screen.

---
### 🖼️ Images
ERROR
![WhatsApp Image 2025-09-26 at 19 08 45_31b3daf3](https://github.com/user-attachments/assets/287be16b-db9f-4837-8102-ca8b13b9010d)

TOO CLOSE
![WhatsApp Image 2025-09-26 at 19 08 46_69ce55fd](https://github.com/user-attachments/assets/52123f3a-6ced-46cd-9cad-a18577276be4)

CLOSE
![WhatsApp Image 2025-09-26 at 19 08 45_8b0975aa](https://github.com/user-attachments/assets/49288e2a-8dfb-4b77-a001-d09b2a339f32)

SAFE
![WhatsApp Image 2025-09-26 at 19 08 46_054017c8](https://github.com/user-attachments/assets/df59a02f-eb74-4823-bc41-7104c88438a7)

