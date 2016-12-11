enum PinAssignments {
  PENencoderPinA = 2,
  PENencoderPinB = 3,
  FRencoderPinA  = 18,
  FRencoderPinB  = 19,
  FLencoderPinA  = 20,
  FLencoderPinB  = 21,

};

float PENencoderPos = 0;
float PENlastReportedPos = 1;
float FRencoderPos = 0;
float FRlastReportedPos = 1;
float FLencoderPos = 0;
float FLlastReportedPos = 1;
float realPen;
float realFR;
float realFL;


boolean PEN_A_set = false;
boolean PEN_B_set = false;
boolean FR_A_set = false;
boolean FR_B_set = false;
boolean FL_A_set = false;
boolean FL_B_set = false;


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

  Serial.begin(38400);
}


void loop() {
  if (PENlastReportedPos != PENencoderPos) {
    realPen = (PENencoderPos / 4) * (.036);
    Serial.print(realPen , DEC);


    Serial.println(realPen - PENlastReportedPos);
    PENlastReportedPos = realPen;
  }

  if (FRlastReportedPos != FRencoderPos) {
    realFR = (FRencoderPos / 4);
    Serial.print(realFR , DEC);


    Serial.println(realFR - FRlastReportedPos);
    FRlastReportedPos = realFR;

  }
  if (FLlastReportedPos != FLencoderPos) {
    realFL = (FLencoderPos / 4);
    Serial.print(realFL , DEC);


    Serial.println(realFL - FLlastReportedPos);
    FLlastReportedPos = realFL;

  }
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
