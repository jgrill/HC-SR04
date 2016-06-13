#include <LiquidCrystal.h>
#include <NewPing.h>
#include <DHT.h>

#define TRIGGER_PIN  8
#define ECHO_PIN     9
#define MAX_DISTANCE 200
#define GRN_LED      10
#define RED_LED      11

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  pinMode(GRN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delay(50);
  int uS = sonar.ping_median();
  int cm = uS / US_ROUNDTRIP_CM;

  if (cm <= 8) {
    digitalWrite(GRN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  } else if (cm <= 20) {
    digitalWrite(GRN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  } else {
    digitalWrite(GRN_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }

  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println("cm");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(cm);
  lcd.print("cm");
}
