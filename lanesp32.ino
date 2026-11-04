#include <WiFi.h>
#include "esp_wifi.h"

const char* ssid = "RED_ESP32_AULA";
const char* password = "Aula12345";

// Para no escribir continuamente en el monitor
unsigned long ultimoInforme = 0;
const unsigned long intervalo = 5000;   // cada 5 segundos

void mostrarConectados() {

  wifi_sta_list_t lista;

  // Obtener lista de estaciones conectadas al AP
  esp_wifi_ap_get_sta_list(&lista);

  Serial.println();
  Serial.println("================================");
  Serial.println(" DISPOSITIVOS CONECTADOS");
  Serial.println("================================");

  Serial.print("Total conectados: ");
  Serial.println(lista.num);

  if (lista.num == 0) {
    Serial.println("No hay dispositivos conectados.");
  }

  for (int i = 0; i < lista.num; i++) {

    Serial.print("Dispositivo ");
    Serial.print(i + 1);
    Serial.print(" | MAC: ");

    for (int j = 0; j < 6; j++) {

      if (lista.sta[i].mac[j] < 16) {
        Serial.print("0");
      }

      Serial.print(lista.sta[i].mac[j], HEX);

      if (j < 5) {
        Serial.print(":");
      }
    }

    Serial.println();
  }

  Serial.println("================================");
}


void setup() {

  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("Creando punto de acceso...");

  // Crear la red Wi-Fi
  WiFi.mode(WIFI_AP);

  bool resultado = WiFi.softAP(ssid, password);

  if (resultado) {

    Serial.println("Punto de acceso creado correctamente.");

    Serial.print("Red Wi-Fi: ");
    Serial.println(ssid);

    Serial.print("IP de la ESP32: ");
    Serial.println(WiFi.softAPIP());

    Serial.print("MAC del punto de acceso: ");
    Serial.println(WiFi.softAPmacAddress());

  } else {

    Serial.println("ERROR: no se ha podido crear el punto de acceso.");
  }
}


void loop() {

  // Mostrar los dispositivos conectados cada 5 segundos
  if (millis() - ultimoInforme >= intervalo) {

    ultimoInforme = millis();

    mostrarConectados();
  }
}