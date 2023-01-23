void setup() {
  // put your setup code here, to run once:
  //2)
  Serial.begin(115200); //Configuration de la communication sérielle à une fréquence de 115200 bits/seconde
  pinMode(A0, INPUT); //Configuration de la pin A0 comme entrée
  //3)
  pinMode(3, OUTPUT); //Configuration de la pin 3 comme sortie
}

void loop() {
  // put your main code here, to run repeatedly:
  //2)
  int data = analogRead(A0); //Lecture analogique et conversion numérique de la tension lue sur A0
  Serial.println(data); //Affichage de data dans le moniteur de communication série
  delay(100); //Délai ajouté pour échantillonner à une fréquence de 10 Hz

  //3)
  digitalWrite(3, HIGH); //Mise à un haut logique (5V) de la pin 3
  delay(0.5); //Délai ajouté pour imposer une fréquence de 1kHz à la boucle
  digitalWrite(3, LOW); //Mise à un bas logique (0V) de la pin 3
  delay(0.5); //Délai ajouté pour imposer une fréquence de 1kHz à la boucle

  //6)
  }
