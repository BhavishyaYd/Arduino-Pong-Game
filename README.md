# Arduino Pong Game

A classic Pong arcade game implemented on an ATmega328P microcontroller (Arduino Uno). The system is built around a finite state machine that manages menus, gameplay, and pause logic. It demonstrates real-world microcontroller concepts including I2C display interfacing, non-blocking input handling, floating-point physics, collision detection, and PWM audio — all running without an operating system on constrained hardware.

---

## Functionality

| Feature | Description |
|---|---|
| **Game Modes** | 1 Player vs AI or 2 Player local multiplayer |
| **AI Difficulty** | Easy, Medium, and Hard levels with varying AI speed and starting ball velocity |
| **Ball Physics** | Angle-based deflection where the output angle depends on where the ball hits the paddle. Centre hits go flat, edge hits go steep |
| **Progressive Speed** | Ball accelerates on every paddle hit, with per-mode increments (Easy: +0.03, Medium: +0.05, Hard: +0.08, PvP: +0.10) and a cap at 2.5x |
| **Pause Menu** | Accessible at any time with Resume and Main Menu options |
| **Audio Feedback** | Distinct tones for wall bounce (1200 Hz), paddle hit (2000 Hz), score (400 Hz), and win (1500 Hz) |
| **Non-blocking Input** | Button debouncing via `millis()` timestamps, no blocking delays in the game loop |
| **Win Screen** | Displays winner and final score, then returns to the main menu |

---

## Components Used

| Component | Details |
|---|---|
| **Arduino Uno** | ATmega328P, 16 MHz, 5V logic |
| **SSD1306 OLED Display** | 128×64 pixels, I2C address `0x3C` |
| **Push Buttons** | 6× tactile switches — P1 Up/Down, P2 Up/Down, Pause, Select |
| **Passive Buzzer** | PWM tone output on pin D6 |
| **Breadboard & Jumper Wires** | For prototyping |

---

## Libraries

- **Wire.h** — I2C communication
- **Adafruit_GFX.h** — Graphics primitives
- **Adafruit_SSD1306.h** — OLED display driver

---

## Pin Mapping

| Pin | Function |
|---|---|
| D2 | Player 1 Up |
| D3 | Player 1 Down |
| D4 | Player 2 Up / Menu Navigate |
| D5 | Player 2 Down / Menu Navigate |
| D6 | Buzzer |
| D7 | Pause Button |
| A4 (SDA) | OLED I2C Data |
| A5 (SCL) | OLED I2C Clock |