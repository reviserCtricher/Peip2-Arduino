
void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Bonjour -Pret pour les commandes AT");
  Serial3.begin(9600);
  delay(500);
  }


void loop() {
  while (Serial3.available()) {
    Serial.print(char(Serial3.read())); }
  while (Serial.available()) {
    Serial3.write(char(Serial.read())); }

}
