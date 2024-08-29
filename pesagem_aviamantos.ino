#include "HX711.h"

// Definir pinos para DT e SCK do HX711
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

HX711 scale;

float calibration_factor = 3500; // Valor para calibrar a balança
float weight;
float previous_weight = 0;
float threshold = 2.0; // Limite para mudança de peso

void setup() {
  Serial.begin(9600);
  
  // Limpar o Serial Monitor
  for(int i = 0; i < 10; i++) {
    Serial.println();
  }
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare(); // Zera a balança
}

void loop() {
  weight = scale.get_units(10); // Lê o peso atual

  // Arredonda o peso para  inteiro
  long rounded_weight = round(weight);
  
  // Verifica se o peso mudou 
  if (abs(rounded_weight - previous_weight) > threshold) {
    Serial.println(rounded_weight);
    previous_weight = rounded_weight;
  }
  
  delay(1000); // Aguarda 1 segundo 
}