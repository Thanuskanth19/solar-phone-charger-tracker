#include <Servo.h>

// ---------- Pins ----------
const int LDR_LEFT  = A0;
const int LDR_RIGHT = A1;
const int LDR_UP    = A2;
const int LDR_DOWN  = A3;

const int SERVO_AZ_PIN  = 9;   // horizontal
const int SERVO_EL_PIN  = 10;  // vertical

// ---------- Tuning ----------
int DEADBAND = 60;       // min difference to move (0–1023)
int STEP     = 1;        // servo step per update (deg)
int DELAY_MS = 20;       // loop delay

// Servo travel limits (protects mechanics)
int AZ_MIN = 20,  AZ_MAX = 160;   // adjust for your mount
int EL_MIN = 20,  EL_MAX = 160;

// ---------- State ----------
Servo srvAz, srvEl;
int azPos = 90, elPos = 90;

int clamped(int v, int lo, int hi){ return v < lo ? lo : (v > hi ? hi : v); }

void centerServos(){
  azPos = clamped(azPos, AZ_MIN, AZ_MAX);
  elPos = clamped(elPos, EL_MIN, EL_MAX);
  srvAz.write(azPos);
  srvEl.write(elPos);
}

void setup() {
  srvAz.attach(SERVO_AZ_PIN);
  srvEl.attach(SERVO_EL_PIN);
  centerServos();

  analogReference(DEFAULT); // 5V ref
  // Optional: small delay to let power rails settle
  delay(1000);
}

void loop() {
  // Read sensors (simple averaging for noise)
  int L = analogRead(LDR_LEFT);
  int R = analogRead(LDR_RIGHT);
  int U = analogRead(LDR_UP);
  int D = analogRead(LDR_DOWN);

  int horizErr = (L - R); // + = too much left light -> rotate right
  int vertErr  = (U - D); // + = too much up light   -> tilt down

  // Horizontal control
  if (abs(horizErr) > DEADBAND) {
    azPos += (horizErr < 0 ? +STEP : -STEP); // if R brighter, move right
  }

  // Vertical control
  if (abs(vertErr) > DEADBAND) {
    elPos += (vertErr < 0 ? +STEP : -STEP); // if D brighter, move down
  }

  centerServos();
  delay(DELAY_MS);
}
