#define RXp2 16
#define TXp2 17

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
}

void loop() {
  Serial2.write("Slave0 0\n");  // enviar el comando a través del puerto serial
  delay(1000);
}