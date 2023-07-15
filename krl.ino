#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>

#include "script_js.h"
#include "style_css.h"
#include "index_html.h"
#include "imagenes.h"

#define LED 2 

WebServer servidor(80);

const char* ssid = "KRL";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);
 
  // Iniciar sistema de archivo SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("Se ha producido un error al montar SPIFFS");
    return;
  }

  //crear archivo de datos
  File datos = SPIFFS.open("/datos.txt", FILE_WRITE);
  datos.print("ESTA ES TODA LA INFORMACION DEL ARCHIVO DATOS.TXT");
  datos.close();

  //iniciar WIFI como un Access Point
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid, password);


  servidor.on("/script.js", []() {
    servidor.send(200, "text/javascript", script_js);
  });

  servidor.on("/style.css", []() {
    servidor.send_P(200, "text/css", style_css);
  });

  servidor.on("/favicon.png", []() {
    servidor.send_P(200, "image/png", (const char*)favicon_png, favicon_png_len);
  });

  servidor.on("/logo.png", []() {
    servidor.send_P(200, "image/png", (const char*)logo_png, logo_png_len);
  });

  servidor.on("/", []() {
    servidor.send(200, "text/html", index_html);
  });

  servidor.on("/bajar_datos", []() {
    File archivo = SPIFFS.open("/datos.txt", "r");
    servidor.sendHeader("Content-Type", "text/txt");
    servidor.sendHeader("Content-Disposition", "attachment; filename=datos.txt");
    servidor.sendHeader("Connection", "close");
    servidor.streamFile(archivo, "application/octet-stream");
    archivo.close();
  });

  servidor.on("/encender_led", HTTP_GET, []() {
    digitalWrite(LED, 1);
    servidor.send(200, "text/plain", "Led encendido");
  });

  servidor.on("/apagar_led", HTTP_GET, []() {
    digitalWrite(LED, 0);
    servidor.send(200, "text/plain", "Led apagado");
  });

  servidor.begin();
}

void loop() {
  servidor.handleClient();
  delay(1);
  //hacer cualquier cosa
}


