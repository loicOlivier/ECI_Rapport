#define PWM_Output_Pin 5

void setup() {
  pinMode(PWM_Output_Pin, OUTPUT);
  Serial.begin(9600); // Important d'avoir la même valeur dans matlab  
}

void loop() {
  if (Serial.available() > 0) {
    byte matlabSignal = Serial.read(); // Read one byte of data from the serial port
    analogWrite(PWM_Output_Pin, matlabSignal);
  }
}
