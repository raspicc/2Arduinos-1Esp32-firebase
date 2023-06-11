#include "Arduino.h"
#include "Vrekrer_scpi_parser.h"
#include <Wire.h>

SCPI_Parser my_instrument;

const int ledPin = 11;
void setup()
{
  Wire.begin();
  my_instrument.RegisterCommand("*IDN?", &Identify);
  my_instrument.RegisterCommand(F("Slave#"), &WriteDigital_Output);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  my_instrument.ProcessInput(Serial, "\n");
}

void Identify(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.println(F("Hcal ,Arduino Master Instrument ,#00,v1.0.0"));
}

void WriteDigital_Output(SCPI_C commands, SCPI_P parameters, Stream& interface) {

  String header = String(commands.Last());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(),"%*[SLAVE]%u", &suffix);

  String first_parameter = String(parameters.First());
  first_parameter.toUpperCase();
  if (suffix == 0) { // si se trabaja con el Slave0
    if (first_parameter == "1") {
      digitalWrite(ledPin, HIGH); // emtonces enciende
    }
    if (first_parameter == "0") {
      digitalWrite(ledPin, LOW);
    }
  }
  if (suffix == 1) { // si se trabaja con el Slave1
    if (first_parameter == "1") {
        int estado = 1;
        int estado1;
        // transmite al esclavo 1
        Wire.beginTransmission(1);
        Wire.write(estado);
        Wire.endTransmission();

        
        // Solicita información al esclavo 1
        Wire.requestFrom(1, 1);
        while(Wire.available()){
          estado1 = Wire.read();
        }

        delay(1000);
        estado = 0;
        // transmite al esclavo 1
        Wire.beginTransmission(1);
        Wire.write(estado);
        Wire.endTransmission();

        // Solicita información al esclavo 1
        Wire.requestFrom(1, 1);
        while(Wire.available()){
          estado1 = Wire.read();
        }
    }
  }
}