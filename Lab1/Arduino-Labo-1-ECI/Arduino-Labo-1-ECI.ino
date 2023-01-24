// Modes d'utilisations
// Définir le mode désiré uniquement et commenter l'autre

#define SCOPE
//#define SQUARE_WAVE

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
  #ifdef SCOPE
  int data = analogRead(A0); //Lecture analogique et conversion numérique de la tension lue sur A0
  Serial.println(data); //Affichage de data dans le moniteur de communication série
  delay(100); //Délai de 100ms ajouté pour échantillonner à une fréquence de 10 Hz
  #endif
  
  //3)
  #ifdef SQUARE_WAVE

  // Acquisition (scope)
  int data = analogRead(A0); //Lecture analogique et conversion numérique de la tension lue sur A0
  Serial.println(data); //Affichage de data dans le moniteur de communication série

  // Génération d'une onde carré à 1kz
  /* Remarque: La fréquence réelle mesurée sera inférieure à 1kz en raison 
   * des autres fonctions (digitalWrite, Serial.print, etc.) qui prennet
   * une courte durée à être effectué.
  */ 
  digitalWrite(3, HIGH); //Mise à un haut logique (5V) de la pin 3
  delay(0.5); //Délai ajouté pour imposer une fréquence de 1kHz à la boucle
  digitalWrite(3, LOW); //Mise à un bas logique (0V) de la pin 3
  delay(0.5); //Délai ajouté pour imposer une fréquence de 1kHz à la boucle
  #endif

  /* 
   *  Idée de solution pour tendre vers une valeur réelle de 1kz:
   *  delay(0.5) -> delay(0.4xx) et ajouter les autres fonction 
   *  entre afin d'obtenir presque 1 kz
   */
  //6)
  }
