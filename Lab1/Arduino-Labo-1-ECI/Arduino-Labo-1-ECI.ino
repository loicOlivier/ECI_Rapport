


// Modes d'utilisations
// Définir le mode désiré uniquement et commenter l'autre

#define SCOPE
//#define SQUARE_WAVE

// Mode additionnel pour faire l'acquisition sur Matlab
//#define MATLAB_ACQUISITION



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
  Serial.println(data, BIN); //Affichage de data dans le moniteur de communication série
  delay(100); //Délai de 100ms ajouté pour échantillonner à une fréquence de 10 Hz
  #endif
  
  //3)
  #ifdef SQUARE_WAVE
  freq = 1000
  int i = 0;
  bool status_pin;
  digitalWrite(4,HIGH);
  digitalWrite(3,HIGH);
  while (1){
    if (i % 3){
      if status_pin
      digitalWrite(3, LOW);
      status_pin = ~status_pin
      i = 0;
    }
    digitalWrite(4, HIGH);
    delayMicroseconds(freq / (1000 * 2));
    digitalWrite(4,LOW);
    delayMicroseconds(freq / (1000 * 2));
    i++
  }

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

  #ifdef MATLAB_ACQUISITION

  int mask1 = 0b0011111111;
  int mask2 = 0b1111111100;
  LSB = (data & mask1);
  MSB = (data & mask2) >> 2;

  Serial.write(0x01);       
  Serial.write(LSB);
  Serial.write(MSB);
  Serial.write(0xFE);
  
  
  /*
  String Bin_data = bitSet< 10 >( data ).to_string(); // data en string binaire 10 bits
  String LSB_data[8];
  String MSB_data[8];
  for (int i = 2; i < 10; i++){
    LSB_data[i-2] = Bin_data[i]; 
  }
  for (int i = 0; i < 8; i++){
    MSB_data[i] = Bin_data[i]; 
  }
  
  Serial.write(0x01);       // Comment faire pour que la valeur soit reconnue comme du hexa?
  Serial.write(LSB_data);
  Serial.write(MSB_data);
  Serial.write(0xFE); 
  */             
  #endif
  }
