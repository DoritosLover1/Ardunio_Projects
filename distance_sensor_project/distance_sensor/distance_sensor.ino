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
