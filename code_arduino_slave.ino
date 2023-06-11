//codigo para esclavo 1
#include <Wire.h>

#define LED_PIN 11  // Cambiar el número del pin según el pin que esté conectado el LED

int estado = 0;

void setup() {
  Wire.begin(1);
  Wire.onReceive(llegaDato);
  Wire.onRequest(enviaDato); // Función para enviar datos al maestro
  pinMode(LED_PIN, OUTPUT); // Configurar el pin del LED como salida
}

void loop() {
  // No es necesario agregar código aquí, se maneja todo en las funciones llegaDato y enviaDato
}

void llegaDato(){
  if(Wire.available()==1){ // si hay un byte disponible
    estado = Wire.read();
  }
  digitalWrite(LED_PIN, estado); //activamos/desactivamos la salida depende del maestro
}

void enviaDato(){
  Wire.write(estado); // Envía el estado del LED al maestro
}