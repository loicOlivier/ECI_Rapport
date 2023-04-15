#include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int timer1_counter;
int frequency_ready = 0;
unsigned int frequency = 0;
int sampling_freq = 5000;
const float R = 5305;           // Valeur R des résistance du montage d'oscillateur 
const float C = 0.00000001;     // ... condensateur

 /*
  L'union est est un type dont l'espace mémoire est le même pour tous les éléments de son contenu.
  Ceci signifie dans le cas ci-dessous qu'une modification des valeurs du vecteur intV modifie également long V.
  Cette approche permet d'économiser de la mémoire, mais elle est quelque peu exagéré (overkill) dans le contexte.
 */

typedef union                  
{
  int intV[2];
  long longV;
}NotchUnion;

void setup() {
  noInterrupts();           // disable all interrupts
  //-----INIT UART-----
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  //-----END INIT UART-----
  
  //-----INIT TIMER1 (16 bits timer)-----

  // TCCR1A & TCCR1B sont des registres du timer1
  TCCR1A = 0;
  TCCR1B = 0;

  timer1_counter = 65536-16000000/sampling_freq;
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS10);    // 1 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  //-----END INIT TIMER1-----
  
  interrupts();             // enable all interrupts
}


// Le type "inline" propose au compiler de copier la fonction partout où il en a besoin en mémoire
// plutôt que de faire un branchement lors de l'appel de la fonction. Ceci peut améliorer la performance du code,
// mais au détriment de nécessiter davantage de mémoire, il est donc préférable d'utiliser de specifier pour
// des fonctions courtes.
inline int NotchAtDC(const int & x_n)
{
  static NotchUnion SigWithDCmantisse = {.longV = 0}; // la synthaxe est particulière puisqu'il s'agit d'un type UNION
  int corrected_signal = x_n - SigWithDCmantisse.intV[0]; // je ne comprend pas l'utilité du UNION comme le intV[1] est jamais utilisé
  SigWithDCmantisse.longV = corrected_signal + SigWithDCmantisse.longV;
  return corrected_signal;
}

void loop() { // run over and over
    if(frequency_ready == 1)
    {
      static char frequency_array[10];
      static char condensateur_array[10];
      unsigned int frequency_buffer = frequency;
      float condo_value = 1000000.0/(4 * M_PI * M_PI * pow(frequency_buffer, 2) * R * R * C);
      frequency_ready = 0;      
      Serial.write("\033cValeur du condensateur estimée: ");           // \033c sert à nettoyer l'écran du terminal avant d'imprimer le message
      Serial.write(dtostrf(condo_value, 1, 10, condensateur_array));   //dtostrf est une fonction permettant de convertir un float en un string
      Serial.write("e-6 F\r\n"); 
    }
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  static unsigned char zero_cross_cnt = 0; //interception du 0 (pour compter le nombre de périodes)
  static int sample_cnt = 0;
  static int filteredSampleOld = 0;
  int filteredSample;
  TCNT1 = timer1_counter;   // preload timer  
  filteredSample = NotchAtDC(analogRead(A0));  // prendre la valeur actuel sur la pin A0 et enlever le DC
  sample_cnt++;                                // incrémenter le nombre de sample
  if((filteredSample < 0 && filteredSampleOld > 0) || (filteredSample > 0 && filteredSampleOld < 0)) // Un changement de signe implique que le 0 a été traversé (période)
  {//Zero crossed
    if(++zero_cross_cnt == 128)
    {//Complete period
      frequency = 320000/sample_cnt;    //On connait le temps entre chaque sample (5000 Hz) et on sait qu'il y a eu 128 périodes 
      zero_cross_cnt = 0;
      sample_cnt = 0;
      frequency_ready = 1;
    }
  }
  filteredSampleOld = filteredSample;
}
