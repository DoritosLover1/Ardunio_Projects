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

  if (distance < 10)
  {
    digitalWrite(SAFE_LED_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    delay(50);
    digitalWrite(LED_PIN, LOW);
    delay(50);
  } 
  else if (distance < 30)
  {
    digitalWrite(SAFE_LED_PIN, LOW);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(SAFE_LED_PIN, HIGH);
  }
  delay(120);
}
