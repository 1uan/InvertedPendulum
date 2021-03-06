enum PinAssignments {
  encoderPinA = 2,
  encoderPinB = 3,
  clearButton = 8
};

volatile float encoderPos = 0;
float lastReportedPos = 1;


boolean A_set = false;
boolean B_set = false;


void setup() {

  pinMode(encoderPinA, INPUT); 
  pinMode(encoderPinB, INPUT); 
  pinMode(clearButton, INPUT);
  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);  
  digitalWrite(clearButton, HIGH);

// encoder pin on interrupt 0 (pin 2)
  attachInterrupt(0, doEncoderA, CHANGE);
// encoder pin on interrupt 1 (pin 3)
  attachInterrupt(1, doEncoderB, CHANGE);

  Serial.begin(9600);
}


void loop(){ 
  if (lastReportedPos != encoderPos) {
    
    Serial.print((encoderPos/4)*(.036) , DEC);
    

    Serial.println(((encoderPos/4)*(.036)-(lastReportedPos/4)*(.036)));
    lastReportedPos = encoderPos;
  }
  if (digitalRead(clearButton) == HIGH)  {
    encoderPos = 0;
    delay(1);
  }
}

// Interrupt on A changing state
void doEncoderA(){
  // Test transition
  A_set = digitalRead(encoderPinA) == HIGH;
  // and adjust counter + if A leads B
  encoderPos += (A_set != B_set) ? +1 : -1;
}

// Interrupt on B changing state
void doEncoderB(){
  // Test transition
  B_set = digitalRead(encoderPinB) == HIGH;
  // and adjust counter + if B follows A
  encoderPos += (A_set == B_set) ? +1 : -1;
}
