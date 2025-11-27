# AccessForge
A fast RFID authentication engine that verifies cards, unlocks via servo mechanism and visually communicates access states in real-time.
---
RFID Access Control System (RFID + LCD + Servo + Buzzer)

A simple access control project using **MFRC522 RFID**, **I2C LCD Display**, **Servo Motor**, and **Buzzer**.  
When an authorized UID card is scanned, the servo opens and a short buzzer signal indicates successful access.  
Unknown cards trigger a denial beep and access remains locked.

---

## Features

• Detects RFID card UID and compares with stored authorized UID  
• Displays real-time status on 16x2 I2C LCD  
• Servo unlocks at 180° for valid card  
• 200ms buzzer indication for access allowed or denied  
• Clean, minimal code for GitHub / production use

---

## Hardware Required

| Component | Qty |
|----------|-----|
| Arduino Uno / Nano / Mega | 1 |
| MFRC522 RFID Reader | 1 |
| SG90 / MG995 Servo | 1 |
| I2C 16x2 LCD Module | 1 |
| Active Buzzer | 1 |
| RFID Tag/Card | 1+ |
| Jumper Wires | As needed |

---

## Pin Connections

| RFID MFRC522 | Arduino |
|-------------|---------|
| 3.3V        | 3.3V |
| RST         | D9 |
| SDA/SS      | D10 |
| MOSI        | D11 |
| MISO        | D12 |
| SCK         | D13 |
| GND         | GND |

| LCD I2C | Arduino |
|--------|----------|
| VCC    | 5V |
| GND    | GND |
| SDA    | A4 |
| SCL    | A5 |

| Component | Pin |
|----------|-----|
| Buzzer   | D3 |
| Servo    | D5 |

---

## How It Works

1. Power the circuit and LCD shows **RFID System Ready**
2. Scan any card near the reader
3. Code reads and compares UID with authorized list
4. If matched  
   • Servo moves to 180  
   • Buzzer active 200ms  
   • LCD shows Access Granted  
5. If not matched  
   • System stays locked  
   • Short 200ms denial beep  

---

## Replace the UID

Find your card UID using serial monitor then replace inside code:
