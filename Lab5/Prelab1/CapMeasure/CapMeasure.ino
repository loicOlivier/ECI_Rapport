 #include <SoftwareSerial.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int timer1_counter;
int frequency_ready = 0;
unsigned int frequency = 0;
int sampling_freq = 5000;
const float R = 5100.0;
const float C = 0.00000001;

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
  TCCR1A = 0;
  TCCR1B = 0;

  timer1_counter = 65536-16000000/sampling_freq;
  
  TCNT1 = timer1_counter;   // preload timer
  TCCR1B |= (1 << CS10);    // 1 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  //-----END INIT TIMER1-----
  
  interrupts();             // enable all interrupts
}

inline int NotchAtDC(const int & x_n)
{
  static NotchUnion SigWithDCmantisse = {.longV = 0};
  int corrected_signal = x_n - SigWithDCmantisse.intV[0];
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
      Serial.write("\033cValeur du condensateur estimée: ");
      Serial.write(dtostrf(condo_value, 1, 10, condensateur_array));
      Serial.write("e-6 F\r\n");
    }
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  static unsigned char zero_cross_cnt = 0;
  static int sample_cnt = 0;
  static int filteredSampleOld = 0;
  int filteredSample;
  TCNT1 = timer1_counter;   // preload timer  
  filteredSample = NotchAtDC(analogRead(A0));
  sample_cnt++;
  if((filteredSample < 0 && filteredSampleOld > 0) || (filteredSample > 0 && filteredSampleOld < 0))
  {//Zero crossed
    if(++zero_cross_cnt == 128)
    {//Complete period
      frequency = 320000/sample_cnt;
      zero_cross_cnt = 0;
      sample_cnt = 0;
      frequency_ready = 1;
    }
  }
  filteredSampleOld = filteredSample;
}
