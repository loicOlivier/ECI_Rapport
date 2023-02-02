//Modes d'utilisations: Définir le mode désiré uniquement et commenter les autres:
// --------------------------------------------------------------------------------

//#define SCOPE //Définition de la macro pour la question 2
//#define SQUARE_WAVE //Définition de la macro pour la question 3
//#define MATLAB_ACQUISITION //Définition de la macro pour la question 6

// --------------------------------------------------------------------------------


int x = 0;
int y = 0;


void setup() {
  // put your setup code here, to run once:
  //2)
  Serial.begin(115200); //Configuration de la communication sérielle à une fréquence de 115200 bits/seconde
  pinMode(A0, INPUT); //Configuration de la pin A0 comme entrée
  //3)
  pinMode(3, OUTPUT);//Configuration de la pin 3 comme sortie
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
  int data = analogRead(A0); //Lecture analogique et conversion numérique de la tension lue sur A0
  Serial.println(data); //Affichage de data dans le moniteur de communication série
  if (x % 3 == 0) { //Condition pour générer l'onde carrée
    x = 0;
    if (y) {
      digitalWrite(3, HIGH);
      y = -y + 1;
  } else {
      digitalWrite(3, LOW);
      y = -y + 1;}
  }
    x = x + 1;
    delay(1); //Délai de 1 ms ajouté pour échantilloner à une fréquence d'environ 136 Hz
  #endif

  //6)

  #ifdef MATLAB_ACQUISITION

  int data = analogRead(A0); //Lecture analogique et conversion numérique de la tension lue sur A0
  
  int mask1 = 0b0011111111; //Création d'un masque
  int mask2 = 0b1100000000; //Création d'un masque
  byte LSB = (data & mask1); //Comparaison AND binaire pour générer le message des 8 bits LSB
  byte MSB = (data & mask2) >> 8; //Comparaison AND binaire pour générer le message des 2 bits MSB
  byte intro = 0x01; //Message de début de message
  byte outro = 0xFE; //Message de fin de message
  Serial.write(intro);       //Communication série sur Matlab
  Serial.write(LSB);
  Serial.write(MSB);
  Serial.write(outro);
               
  #endif
  }
