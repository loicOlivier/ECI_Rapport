// Simulation d'acquisition avec la carte arduino

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(A0, INPUT);
}

void loop() {
  // Lecture donnée
  int data = analogRead(A0);
  Serial.print("Lecture brute: ");
  Serial.println(data, BIN);
  
  int mask1 = 0b0011111111;
  int mask2 = 0b1111111100;
  int LSB = (data & mask1);
  int MSB = (data & mask2) >> 2;

  Serial.print("LSB: ");
  Serial.println(LSB, BIN);

  Serial.print("MSB: ");
  Serial.println(MSB, BIN);

  delay(100000);

}
