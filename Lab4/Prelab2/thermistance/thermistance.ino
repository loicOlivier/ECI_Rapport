#define tempPin A0

#define Vdd 5

#define R1 10000
#define R2 10000
#define R3 10000
#define R0 10000 //Valeur de la thermistance à température ambiante
#define beta 4300
#define T0 20 //Température ambiante


int T; // température calculé
int Rt; // Résistance calculé
int Vout;


void setup() {
  pinMode(A0, INPUT);
  Serial.begin(9600);

}

void loop() {
  // Lecture analogique
  Vout = analogRead(tempPin);

  // Calcul de la résistance instantannée Rt
  Rt = R3 * ((R2 / (R1 + R2)) - (Vout / 7 * Vdd)) / ((Vout / (7 * Vdd)) - (R2 / (R1 + R2)) + 1);

  // Calcul de la température
  T = 1 / (1/T0 + 1/beta * (log(Rt / R0)));

  Serial.print("La température est ");
  Serial.print(T);
  Serial.println(" Kelvins !");

}
