# 🕹️ Arduino Pong Game

A fully functional Pong game built on an Arduino Uno with a 128x64 SSD1306 OLED display.
Supports single-player vs AI and two-player local multiplayer, with difficulty selection,
physics-based ball mechanics, and audio feedback via a passive buzzer.

---

## 📋 Abstract

This project implements a classic Pong arcade game on an ATmega328P microcontroller.
The system is built around a finite state machine that manages menus, gameplay, and pause logic.
It demonstrates real-world microcontroller concepts including I2C display interfacing,
non-blocking input handling, floating-point physics, collision detection, and PWM audio —
all running without an operating system on constrained hardware.

---

## ⚙️ Functionality

| Feature | Description |
|---|---|
| Game Modes | 1 Player vs AI or 2 Player local multiplayer |
| AI Difficulty | Easy, Medium, Hard — varying AI speed and starting ball velocity |
| Ball Physics | Angle-based deflection based on hit position on paddle |
| Progressive Speed | Ball accelerates every hit, capped at 2.5x starting speed |
| Pause Menu | Resume or return to Main Menu at any time |
| Audio Feedback | Distinct tones for wall bounce, paddle hit, score, and win |
| Input Debounce | millis()-based non-blocking debounce, no blocking delays |
| Win Screen | Displays winner and final score, auto-returns to menu |

### Speed Increment by Mode

| Mode / Difficulty | Increment per Hit | Starting Multiplier |
|---|---|---|
| AI — Easy | +0.03 | 0.8x |
| AI — Medium | +0.05 | 1.0x |
| AI — Hard | +0.08 | 1.3x |
| Player vs Player | +0.10 | 1.0x |

---

## 🔧 Components Used

| Component | Details |
|---|---|
| Arduino Uno | ATmega328P, 16 MHz, 5V logic |
| SSD1306 OLED Display | 128x64 pixels, I2C address 0x3C |
| Push Buttons | 6x tactile switches — P1 Up/Down, P2 Up/Down, Pause, Select |
| Passive Buzzer | PWM tone output on pin D6 |
| Breadboard & Jumper Wires | For prototyping |

---

## 📌 Pin Mapping

| Pin | Label | Function |
|---|---|---|
| D2 | P1_UP | Player 1 move up |
| D3 | P1_DOWN | Player 1 move down |
| D4 | P2_UP | Player 2 move up / menu navigate |
| D5 | P2_DOWN | Player 2 move down / menu navigate |
| D6 | BUZZER | Passive buzzer PWM output |
| D7 | PAUSE_BTN | Pause / resume game |
| A4 | SDA | OLED I2C data line |
| A5 | SCL | OLED I2C clock line |

---

## 📚 Libraries

- [`Wire.h`](https://www.arduino.cc/reference/en/language/functions/communication/wire/) — I2C communication
- [`Adafruit_GFX`](https://github.com/adafruit/Adafruit-GFX-Library) — Graphics primitives
- [`Adafruit_SSD1306`](https://github.com/adafruit/Adafruit_SSD1306) — OLED display driver

---

## 📸 Screenshots

![WhatsApp Image 2026-03-08 at 8 19 03 PM](https://github.com/user-attachments/assets/34f09af1-d99e-42a7-b941-a6270bf16330)
![WhatsApp Image 2026-03-08 at 8 16 25 PM](https://github.com/user-attachments/assets/c6ed71ef-4ae9-437f-9a02-cf7c3d62345d)
![WhatsApp Image 2026-03-08 at 8 16 26 PM](https://github.com/user-attachments/assets/8ae821e9-10c8-4e49-b0ee-a87b8e7a4cd7)
![WhatsApp Image 2026-03-08 at 8 16 25 PM (3)](https://github.com/user-attachments/assets/515dc33c-160f-4c19-84c7-5e508b33842d)

---

## 🚀 How to Use

1. Wire components as per the pin mapping above
2. Install the required libraries via Arduino Library Manager
3. Open `pong.ino` in the Arduino IDE
4. Select **Arduino Uno** as the board and the correct COM port
5. Upload and play

---

## 🔮 Future Improvements

- EEPROM-based high score storage across power cycles
- Countdown timer before each serve
- Ball-spin mechanic based on paddle movement direction
- Wireless second player via Bluetooth or IR
- Animated splash screen on startup
