#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define P1_UP     2
#define P1_DOWN   3
#define P2_UP     4
#define P2_DOWN   5
#define BUZZER    6
#define PAUSE_BTN 7

#define WIN_SCORE    10
#define PADDLE_H     15
#define PADDLE_SPEED 3
#define MAX_SPEED    2.5f

int gameState = 0;
int menuIndex = 0;
int difficulty = 1;

float ballX, ballY;
float vx = 2, vy = 2;
float speedMultiplier = 1.0f;
float speedIncrement = 0.05f;

int p1Y = 25, p2Y = 25;
int score1 = 0, score2 = 0;
int aiSpeed = 2;

unsigned long lastInput = 0;
#define DEBOUNCE_MS 150

void beep(int f, int t) { tone(BUZZER, f, t); }

void resetBall() {
  ballX = 63;
  ballY = 31;
  do { vy = random(-3, 4); } while (vy == 0);
  vx = random(0, 2) ? 2 : -2;
  speedMultiplier = 1.0f;
}

void setup() {
  Serial.begin(9600);

  pinMode(P1_UP,     INPUT_PULLUP);
  pinMode(P1_DOWN,   INPUT_PULLUP);
  pinMode(P2_UP,     INPUT_PULLUP);
  pinMode(P2_DOWN,   INPUT_PULLUP);
  pinMode(PAUSE_BTN, INPUT_PULLUP);
  pinMode(BUZZER,    OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found");
    while (true);
  }

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();

  randomSeed(analogRead(0));
  resetBall();
}

void loop() {
  if      (gameState == 0) modeMenu();
  else if (gameState == 1) difficultyMenu();
  else                     gameLoop();
}

// ─── MODE MENU ───────────────────────────────────────────────

void modeMenu() {
  display.clearDisplay();
  display.setCursor(20, 5);
  display.println("=== PONG ===");
  display.setCursor(10, 25);
  display.println(menuIndex == 0 ? "> 1P vs AI" : "  1P vs AI");
  display.setCursor(10, 40);
  display.println(menuIndex == 1 ? "> 1P vs 2P" : "  1P vs 2P");
  display.setCursor(5, 56);
  display.print("UP/DN:select P1:ok");
  display.display();

  unsigned long now = millis();
  if (now - lastInput < DEBOUNCE_MS) return;

  if (digitalRead(P2_UP)   == LOW) { menuIndex = 0; beep(1000, 50); lastInput = now; }
  if (digitalRead(P2_DOWN) == LOW) { menuIndex = 1; beep(1000, 50); lastInput = now; }
  if (digitalRead(P1_UP)   == LOW) {
    beep(1500, 100);
    lastInput = now;
    if (menuIndex == 0) {
      gameState = 1;
    } else {
      speedIncrement = 0.1f;
      score1 = 0; score2 = 0;
      resetBall();
      gameState = 2;
    }
  }
}

// ─── DIFFICULTY MENU ─────────────────────────────────────────

void difficultyMenu() {
  display.clearDisplay();
  display.setCursor(15, 5);
  display.print("AI DIFFICULTY");
  display.setCursor(10, 25);
  display.print(difficulty == 0 ? "> EASY"   : "  EASY");
  display.setCursor(10, 37);
  display.print(difficulty == 1 ? "> MEDIUM" : "  MEDIUM");
  display.setCursor(10, 49);
  display.print(difficulty == 2 ? "> HARD"   : "  HARD");
  display.display();

  unsigned long now = millis();
  if (now - lastInput < DEBOUNCE_MS) return;

  if (digitalRead(P2_UP)   == LOW) { if (difficulty > 0) difficulty--; lastInput = now; }
  if (digitalRead(P2_DOWN) == LOW) { if (difficulty < 2) difficulty++; lastInput = now; }

  if (digitalRead(P1_UP) == LOW) {
    switch (difficulty) {
      case 0: aiSpeed = 1; speedMultiplier = 0.8f; speedIncrement = 0.03f; break;
      case 1: aiSpeed = 2; speedMultiplier = 1.0f; speedIncrement = 0.05f; break;
      case 2: aiSpeed = 4; speedMultiplier = 1.3f; speedIncrement = 0.08f; break;
    }
    score1 = 0; score2 = 0;
    resetBall();
    gameState = 2;
    beep(1500, 100);
    lastInput = now;
  }
}

// ─── PAUSE ───────────────────────────────────────────────────

void checkPause() {
  if (digitalRead(PAUSE_BTN) != LOW) return;
  delay(200);

  int pauseSel = 0;
  while (true) {
    display.clearDisplay();
    display.setCursor(40, 10);
    display.print("- PAUSED -");
    display.setCursor(30, 30);
    display.print(pauseSel == 0 ? "> Resume"    : "  Resume");
    display.setCursor(30, 44);
    display.print(pauseSel == 1 ? "> Main Menu" : "  Main Menu");
    display.display();

    unsigned long now = millis();
    if (now - lastInput >= DEBOUNCE_MS) {
      if (digitalRead(P2_UP)   == LOW) { pauseSel = 0; lastInput = now; }
      if (digitalRead(P2_DOWN) == LOW) { pauseSel = 1; lastInput = now; }
      if (digitalRead(P1_UP)   == LOW) {
        beep(1000, 100);
        lastInput = now;
        if (pauseSel == 1) {
          score1 = 0; score2 = 0;
          resetBall();
          gameState = 0;
        }
        return;
      }
    }
  }
}

// ─── GAME LOOP ───────────────────────────────────────────────

void gameLoop() {
  checkPause();

  // Player 1
  if (digitalRead(P1_UP)   == LOW) p1Y -= PADDLE_SPEED;
  if (digitalRead(P1_DOWN) == LOW) p1Y += PADDLE_SPEED;
  p1Y = constrain(p1Y, 0, SCREEN_HEIGHT - PADDLE_H);

  // Player 2 / AI
  if (menuIndex == 1) {
    if (digitalRead(P2_UP)   == LOW) p2Y -= PADDLE_SPEED;
    if (digitalRead(P2_DOWN) == LOW) p2Y += PADDLE_SPEED;
  } else {
    int paddleCenter = p2Y + PADDLE_H / 2;
    int ballCenter   = (int)ballY;
    if      (ballCenter > paddleCenter + 2) p2Y += aiSpeed;
    else if (ballCenter < paddleCenter - 2) p2Y -= aiSpeed;
  }
  p2Y = constrain(p2Y, 0, SCREEN_HEIGHT - PADDLE_H);

  // Move ball
  ballX += vx * speedMultiplier;
  ballY += vy * speedMultiplier;

  // Top/bottom bounce
  if (ballY <= 0) {
    ballY = 0; vy = abs(vy);
    beep(1200, 30);
  }
  if (ballY >= SCREEN_HEIGHT - 3) {
    ballY = SCREEN_HEIGHT - 3; vy = -abs(vy);
    beep(1200, 30);
  }

  // P1 paddle collision
  if (ballX <= 6 && ballX >= 2 && ballY + 3 >= p1Y && ballY <= p1Y + PADDLE_H) {
    vx = abs(vx);
    ballX = 7;
    float hitPos = (ballY - p1Y) / (float)PADDLE_H;
    vy = (hitPos - 0.5f) * 6.0f;
    if (vy == 0) vy = 0.5f;
    speedMultiplier = min(speedMultiplier + speedIncrement, MAX_SPEED);
    beep(2000, 40);
  }

  // P2 paddle collision
  if (ballX >= 119 && ballX <= 123 && ballY + 3 >= p2Y && ballY <= p2Y + PADDLE_H) {
    vx = -abs(vx);
    ballX = 118;
    float hitPos = (ballY - p2Y) / (float)PADDLE_H;
    vy = (hitPos - 0.5f) * 6.0f;
    if (vy == 0) vy = 0.5f;
    speedMultiplier = min(speedMultiplier + speedIncrement, MAX_SPEED);
    beep(2000, 40);
  }

  // Scoring
  if (ballX <= 0) {
    score2++;
    beep(400, 300);
    resetBall();
  }
  if (ballX >= SCREEN_WIDTH) {
    score1++;
    beep(400, 300);
    resetBall();
  }

  // Win check
  if (score1 >= WIN_SCORE || score2 >= WIN_SCORE) {
    display.clearDisplay();
    display.setCursor(25, 20);
    if (score1 > score2)
      display.print(menuIndex == 0 ? "YOU WIN!" : "P1 WINS!");
    else
      display.print(menuIndex == 0 ? "AI WINS!" : "P2 WINS!");
    display.setCursor(20, 38);
    display.print(score1);
    display.print(" - ");
    display.print(score2);
    display.display();
    beep(1500, 600);
    delay(3000);
    score1 = 0; score2 = 0;
    resetBall();
    gameState = 0;
    return;
  }

  drawGame();
  delay(16);
}

// ─── DRAW ────────────────────────────────────────────────────

void drawGame() {
  display.clearDisplay();

  // Dashed center line
  for (int y = 0; y < SCREEN_HEIGHT; y += 6)
    display.drawFastVLine(63, y, 3, WHITE);

  // Scores
  display.setCursor(45, 1);
  display.print(score1);
  display.setCursor(75, 1);
  display.print(score2);

  // Paddles
  display.fillRect(2,   p1Y, 3, PADDLE_H, WHITE);
  display.fillRect(123, p2Y, 3, PADDLE_H, WHITE);

  // Ball
  display.fillRect((int)ballX, (int)ballY, 3, 3, WHITE);

  display.display();
}