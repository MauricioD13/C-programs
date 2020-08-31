// InternetDeLasCosas.cl
// Script que obtiene la temperatura desde un sensor LM35 
// y la envia a un servidor web
//
// Escrito por @joniuz

#include <SPI.h>
#include <Ethernet.h>

// Mac unica de cada EthernetShield (deben cambiarla)
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x4E, 0xD7 };

// Descomentar esta linea si se desea un IP fijo
//IPAddress ip(172,17,17,200);

// Descomentar esta linea para asignar un DNS fijo
//IPAddress myDns(172,17,17,1);

// Inicializa la instancia client
EthernetClient client;

// Direccion del servidor
char server[] = "www.iot.cl";

// Variable de tiempo de la ultima conexion en milisegundos
unsigned long ultimaConexion = 0;          
// Estado de la ultima conexion
boolean ultimoEstado = false;
// Intervalo en milisegundos entre conexiones
const unsigned long intervaloConexion = 10000;   

// Datos del sensor
float tempC; // Temperatura en celsius
int LM35 = 0; // Pin A0 del Arduino

void setup() {
  // Inicializa puerto serial
  Serial.begin(9600);
  Serial.println("#### Internetdelascosas.cl ####");
  Serial.println("Sensor de temperatura LM35/ web");
  // Espera 1 segundo para que se inicie la tarjeta Ethernet
  delay(1000);
  // Si deseas usar un ip fijo y un DNS fijo descomentar esta linea y comentar la linea 39
  // Ethernet.begin(mac, ip, myDns);
  // Inicializa la tarjeta ethernet mediante DHCP
  Ethernet.begin(mac);
  // Imprime la direccion IP de la tarjeta
  Serial.print("Direccion IP: ");
  Serial.println(Ethernet.localIP());
}
// Loop principal
void loop() {
  // Lee la temperatura desde el sensor
  tempC = analogRead(LM35);
  // Convierte el valor leido a temperatura
  tempC = (5.0 * tempC * 100.0)/1024.0; 
  
  // Si hay datos que llegan por la conexion los envia a la puerta serial
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // Si no hay conexion de red y se conecto correctamente la ultima vez
  // detiene el cliente Ehternet
  if (!client.connected() && ultimoEstado) {
    Serial.println();
    Serial.println("Desconectando...");
    client.stop();
  }

  // Si no esta conectado y han pasado X segundos (intervaloConexion) 
  // despues de la ultima conexion envia datos al servidor
  if(!client.connected() && (millis() - ultimaConexion > intervaloConexion)) {
    httpRequest();
  }
  // Actualiza la variable ultimoEstado 
  ultimoEstado = client.connected();
}
// Fin del loop principal

// Realiza la conexion http al servidor
void httpRequest() {
  // Se conecta al servidor en el puerto 80 (web)
  if (client.connect(server, 80)) {
    // Envia el dato al puerto serial 
    Serial.print("Sensor LM35: "); 
    Serial.print(tempC); 
    Serial.println(" grados Celsius");
    // Envia el requerimiento al servidor via GET
    Serial.println("Iniciando conexion...");
    client.print("GET /sensorarduino.php?id=joniuz&nombre=temperatura&valor=");
    client.print(tempC);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: Arduino-Ethernet");
    client.println("Connection: close");
    client.println();

    // Actualiza el tiempo en milisegundos de la ultima conexion
    ultimaConexion = millis();
  } 
  else {
    // Si la conexion fallo se desconecta
    Serial.println("Error al conectarse al servidor");
    Serial.println("Desconectando...");
    client.stop();
  }
}
