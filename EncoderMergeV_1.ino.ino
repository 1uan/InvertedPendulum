enum PinAssignments {
  PENencoderPinA = 2,
  PENencoderPinB = 3,
  FRencoderPinA  = 18,
  FRencoderPinB  = 19,
  FLencoderPinA  = 20,
  FLencoderPinB  = 21,

};
#include <PID_v1.h>
#define PIN_OUTPUT 5

float PENencoderPos = 0;
float PENlastReportedPos = 1;
float FRencoderPos = 0;
float FRlastReportedPos = 1;
float FLencoderPos = 0;
float FLlastReportedPos = 1;
float realPen;
float realFR;
float realFL;
double Setpoint, Input, Output;

boolean PEN_A_set = false;
boolean PEN_B_set = false;
boolean FR_A_set = false;
boolean FR_B_set = false;
boolean FL_A_set = false;
boolean FL_B_set = false;
double Kp=1, Ki=0, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {

  pinMode(PENencoderPinA, INPUT);
  pinMode(PENencoderPinB, INPUT);
  pinMode(FRencoderPinA, INPUT);
  pinMode(FRencoderPinB, INPUT);
  pinMode(FLencoderPinA, INPUT);
  pinMode(FLencoderPinB, INPUT);
  digitalWrite(PENencoderPinA, HIGH);
  digitalWrite(PENencoderPinB, HIGH);
  digitalWrite(FRencoderPinA, HIGH);
  digitalWrite(FRencoderPinB, HIGH);
  digitalWrite(FLencoderPinA, HIGH);
  digitalWrite(FLencoderPinB, HIGH);


  // encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
  // encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);
  // encoder pin on interrupt 4 (pin 18)
  attachInterrupt(4, doEncoderC, CHANGE);
  // encoder pin on interrupt 5 (pin 19)
  attachInterrupt(5, doEncoderD, CHANGE);
  // encoder pin on interrupt 5 (pin 19)
  attachInterrupt(2, doEncoderE, CHANGE);
  // encoder pin on interrupt 5 (pin 19)
  attachInterrupt(3, doEncoderF, CHANGE);
 
  Input = realPen;
  Setpoint = 90;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);


  Serial.begin(38400);
}


void loop() {
  if (PENlastReportedPos != PENencoderPos) {
    realPen = (PENencoderPos / 4) * (.036);
    PENlastReportedPos = realPen;
  }
  if (FRlastReportedPos != FRencoderPos) {
    realFR = (FRencoderPos / 4);
    FRlastReportedPos = realFR;
  }
  if (FLlastReportedPos != FLencoderPos) {
    realFL = (FLencoderPos / 4);
    FLlastReportedPos = realFL;
  }
  Input = realPen;
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
}

// Interrupt on A changing state
void doEncoderA() {
  // Test transition
  PEN_A_set = digitalRead(PENencoderPinA) == HIGH;
  // and adjust counter + if A leads B
  PENencoderPos += (PEN_A_set != PEN_B_set) ? +1 : -1;
}

// Interrupt on B changing state
void doEncoderB() {
  // Test transition
  PEN_B_set = digitalRead(PENencoderPinB) == HIGH;
  // and adjust counter + if B follows A
  PENencoderPos += (PEN_A_set == PEN_B_set) ? +1 : -1;
}
// Interrupt on A changing state
void doEncoderC() {
  // Test transition
  FR_A_set = digitalRead(FRencoderPinA) == HIGH;
  // and adjust counter + if A leads B
  FRencoderPos += (FR_A_set != FR_B_set) ? +1 : -1;
}

// Interrupt on B changing state
void doEncoderD() {
  // Test transition
  FR_B_set = digitalRead(FRencoderPinB) == HIGH;
  // and adjust counter + if B follows A
  FRencoderPos += (FR_A_set == FR_B_set) ? +1 : -1;
}
void doEncoderE() {
  // Test transition
  FL_A_set = digitalRead(FLencoderPinA) == HIGH;
  // and adjust counter + if A leads B
  FLencoderPos += (FL_A_set != FL_B_set) ? +1 : -1;
}

// Interrupt on B changing state
void doEncoderF() {
  // Test transition
  FL_B_set = digitalRead(FLencoderPinB) == HIGH;
  // and adjust counter + if B follows A
  FLencoderPos += (FL_A_set == FL_B_set) ? +1 : -1;
}
