# Arduino-Pong-Game
This project implements a classic Pong arcade game on an ATmega328P microcontroller. The system is built around a finite state machine that manages menus, gameplay, and pause logic. It demonstrates real-world microcontroller concepts including I2C display interfacing, non-blocking input handling, floating-point physics, collision detection, and PWM audio — all running without an operating system on constrained hardware.

Functionality

Game Modes — 1 Player vs AI or 2 Player local multiplayer
AI Difficulty — Easy, Medium, and Hard levels with varying AI speed and starting ball velocity
Ball Physics — Angle-based deflection where the output angle depends on where the ball hits the paddle. Centre hits go flat, edge hits go steep
Progressive Speed — Ball accelerates on every paddle hit, with per-mode increments (Easy: +0.03, Medium: +0.05, Hard: +0.08, PvP: +0.10) and a cap at 2.5x
Pause Menu — Accessible at any time with Resume and Main Menu options
Audio Feedback — Distinct tones for wall bounce (1200Hz), paddle hit (2000Hz), score (400Hz), and win (1500Hz)
Non-blocking Input — Button debouncing via millis() timestamps, no blocking delays in the game loop
Win Screen — Displays winner and final score, then returns to the main menu


Components Used
ComponentDetailsArduino UnoATmega328P, 16 MHz, 5V logicSSD1306 OLED Display128x64 pixels, I2C address 0x3CPush Buttons6x tactile switches — P1 Up/Down, P2 Up/Down, Pause, SelectPassive BuzzerPWM tone output on pin D6Breadboard & Jumper WiresFor prototyping

Libraries

Wire.h — I2C communication
Adafruit_GFX.h — Graphics primitives
Adafruit_SSD1306.h — OLED display driver


Pin Mapping
PinFunctionD2Player 1 UpD3Player 1 DownD4Player 2 Up / Menu NavigateD5Player 2 Down / Menu NavigateD6BuzzerD7Pause ButtonA4 (SDA)OLED I2C DataA5 (SCL)OLED I2C Clock
