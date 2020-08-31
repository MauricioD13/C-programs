#define DEBUG true

void setup() {
  // put your setup code here, to run once:
  delay(500);
  Serial.begin(115200);
  Serial3.begin(115200);
  sendData("AT\n",1000,DEBUG);
}

void loop() {
  // put your main code here, to run repeatedly:

}
