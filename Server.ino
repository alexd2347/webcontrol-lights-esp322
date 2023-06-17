// Agregar librerías
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

//Credenciales WiFi
//const char* ssid = "Megacable_2.4G_33C2";
//const char* password = "j9r32F6j";
const char* ssid = "WiFi UVAQ";
const char* password = "";
//GPIO del Led
const int Focoa = 15;
const int Focob = 13;
const int Leda = 18;
const int Ledb = 19;

// Variable para guardar estado del led
String ledState;

//Crear un servidor AsyncWebServer en el puerto 80
AsyncWebServer server(80);

//Cambiar el valor del estado del led
String processor(const String& var) {
  Serial.println(var);
  if (var == "STATE") {
    if (digitalRead(Focoa) or digitalRead(Focob) or digitalRead(Leda) or digitalRead(Ledb) ) {
      ledState = "ON";
    }
    else {
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}

void setup() {
  //Iniciar monitor serial
  Serial.begin(115200);
  pinMode(Focoa, OUTPUT);
  pinMode(Focob, OUTPUT);
  pinMode(Leda, OUTPUT);
  pinMode(Ledb, OUTPUT);

  //Iniciar SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  //Conectar a red WiFi
  Serial.println("Conectando a la red WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Conectado");

  //Imprimir IP local en el Monitor Serie
  Serial.println(WiFi.localIP());

  //Seleccionando archivo index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Seleccionando archivo style.css
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  //Dirección cuando se presiona el botón ENCENDER Focoa
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Focoa, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Dirección cuando se presiona el botón ENCENDER Focoa
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Focoa, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Dirección cuando se presiona el botón ENCENDER Focob
  server.on("/onb", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Focob, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Dirección cuando se presiona el botón ENCENDER Focob
  server.on("/offb", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Focob, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Dirección cuando se presiona el botón ENCENDER Leda
  server.on("/onla", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Leda, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Dirección cuando se presiona el botón ENCENDER Leda
  server.on("/offla", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Leda, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Dirección cuando se presiona el botón ENCENDER Ledb
  server.on("/onlb", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Ledb, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  //Dirección cuando se presiona el botón ENCENDER Ledb
  server.on("/offlb", HTTP_GET, [](AsyncWebServerRequest * request) {
    digitalWrite(Ledb, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  //Iniciar servidor
  server.begin();
}

void loop() {

}
