## 🚨 Ultrasonic Distance Sensor with LED Warning System

This project uses an **HC-SR04 ultrasonic sensor** to measure distance and control LEDs based on the detected range.
Goal: As an object gets closer to the sensor, the **warning LED** blinks faster. When the object is far enough, the **safe LED** stays ON.

---

### ⚡ Features

* **Close distance (<10cm):** Warning LED blinks very fast.
* **Medium distance (<30cm):** Warning LED blinks slower.
* **Far distance (≥30cm):** No danger, Safe LED stays ON.

---

### 🔌 Wiring

| Pin            | Arduino | Description            |
| -------------- | ------- | ---------------------- |
| TRIG\_PIN      | 2       | Ultrasonic sensor TRIG |
| ECHO\_PIN      | 3       | Ultrasonic sensor ECHO |
| LED\_PIN       | 4       | Warning LED            |
| SAFE\_LED\_PIN | 5       | Safe LED               |

---

### 🛠 Required Components

* 1x Arduino (Uno, Nano, or compatible)
* 1x HC-SR04 Ultrasonic Sensor
* 2x LEDs (Red = Warning, Green = Safe)
* 2x 220Ω resistors
* Breadboard + jumper wires

---

### 📜 Code

The code is ready to upload 👇

```cpp
#define TRIG_PIN 2
#define ECHO_PIN 3
#define LED_PIN 4
#define SAFE_LED_PIN 5

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SAFE_LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long distance = pulseIn(ECHO_PIN, HIGH) * 0.0343 / 2;

  if (distance < 10) {
    digitalWrite(SAFE_LED_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
    delay(50);
  } 
  else if (distance < 30) {
    digitalWrite(SAFE_LED_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  else {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(SAFE_LED_PIN, HIGH);
  }
  delay(120);
}
```

---

### 🎯 How It Works

1. The **TRIG pin** is pulsed HIGH for 10μs → sensor sends out an ultrasonic wave.
2. The **ECHO pin** receives the reflected signal → distance is calculated.
3. Based on the distance:

   * Warning LED blinks fast (close)
   * Warning LED blinks slow (medium)
   * Safe LED stays ON (far)

---

### 🚀 Possible Improvements

* Add a buzzer for sound alerts.
* Display distance on an LCD screen.
* Use an RGB LED for color-coded warnings.

---

### 🖼️ Images
![1](https://github.com/user-attachments/assets/7c3e2e31-16d4-4a7b-ac58-c062a71f272a)
![2](https://github.com/user-attachments/assets/944314a7-1c64-493d-bc05-7ee0cdd8dad8)
![3](https://github.com/user-attachments/assets/2d4c01e0-b443-49be-b634-80805ce0de4d)
