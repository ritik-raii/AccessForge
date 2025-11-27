#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buzzerPin = 3;
Servo myServo;
const int servoPin = 5;

const unsigned long buzzerDuration = 200;

byte authorizedUID[4] = { 0x73, 0x1B, 0x51, 0x13 };

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  myServo.attach(servoPin);
  myServo.write(0);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID System Ready");
  lcd.setCursor(0, 1);
  lcd.print("Scan card...");

  SPI.begin();
  mfrc522.PCD_Init();
  delay(50);
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  byte readUID[4] = {0,0,0,0};
  for (byte i = 0; i < 4 && i < mfrc522.uid.size; i++) {
    readUID[i] = mfrc522.uid.uidByte[i];
  }

  bool authorized = true;
  for (byte i = 0; i < 4; i++) {
    if (readUID[i] != authorizedUID[i]) {
      authorized = false;
      break;
    }
  }

  if (authorized) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Granted");
    lcd.setCursor(0, 1);
    lcd.print("Welcome!");

    digitalWrite(buzzerPin, HIGH);
    myServo.write(180);
    delay(buzzerDuration);

    digitalWrite(buzzerPin, LOW);
    myServo.write(0);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    lcd.setCursor(0, 1);
    lcd.print("Try Again");

    digitalWrite(buzzerPin, HIGH);
    delay(200);
    digitalWrite(buzzerPin, LOW);
  }

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID System Ready");
  lcd.setCursor(0, 1);
  lcd.print("Scan card...");
  delay(200);
}
