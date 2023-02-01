//Modes d'utilisations: Définir le mode désiré uniquement et commenter les autres:
// --------------------------------------------------------------------------------

//#define SCOPE
//#define SQUARE_WAVE
#define MATLAB_ACQUISITION

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
  if (x % 3 == 0) {
    x = 0;
    if (y) {
      digitalWrite(3, HIGH);
      y = -y + 1;
  } else {
      digitalWrite(3, LOW);
      y = -y + 1;}
  }
    x = x + 1;
    delay(1);
  #endif

  //6)

  #ifdef MATLAB_ACQUISITION

  int data = analogRead(A0);
  
  int mask1 = 0b0011111111;
  int mask2 = 0b1100000000;
  byte LSB = (data & mask1);
  byte MSB = (data & mask2) >> 8;
  byte intro = 0x01;
  byte outro = 0xFE;

  Serial.write(intro);       
  Serial.write(LSB);
  Serial.write(MSB);
  Serial.write(outro);
               
  #endif
  }
