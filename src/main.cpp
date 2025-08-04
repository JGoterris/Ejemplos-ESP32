/*
----------------- JGoterris -----------------

Este programa realiza una consulta HTTP al servicio de OpenWeatherMap desde un ESP32
para obtener y mostrar información meteorológica actual de una ubicación específica.

Características:
- Se conecta a una red WiFi definida en el archivo "secrets.h".
- Realiza una petición HTTP GET a la API de OpenWeatherMap cada 20 segundos.
- Parsea la respuesta JSON usando ArduinoJson.
- Extrae y muestra por consola:
  - Nombre de la ciudad.
  - Temperatura en grados Celsius.
  - Descripción meteorológica.
  - Porcentaje de humedad.
  - Presión atmosférica.

Requiere:
- Librería ArduinoJson
- Librería HTTPClient
- Una clave válida de API de OpenWeatherMap
*/

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"

const String OPENWEATHER_API = "https://api.openweathermap.org/data/2.5/weather?lat=39.944167&lon=-0.103611&appid=" + String(OPENWEATHER_API_KEY);

void setup_wifi() {
  Serial.print(F("[WiFi] Conectando a "));
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println(F("\n[WiFi] Conectado con éxito"));
  Serial.print(F("[WiFi] IP asignada: "));
  Serial.println(WiFi.localIP());
}

void fetchWeather(){
    HTTPClient http;
    http.begin(OPENWEATHER_API);
    
    int httpCode = http.GET();
    if(httpCode <= 0){
        Serial.print(F("[HTTP] Error en la petición: "));
        Serial.println(http.errorToString(httpCode));
    } else {
        Serial.printf("[HTTP] Código de respuesta: %d\n", httpCode);
        if(httpCode == HTTP_CODE_OK){
            String payload = http.getString();
            
            // Parsear JSON
            // (parseamos porque la cadena json de respuesta es demasiado larga)
            JsonDocument doc;
            deserializeJson(doc, payload);
            
            // Extraer datos importantes
            String ciudad = doc["name"];
            float temperatura = doc["main"]["temp"];
            float temp_celsius = temperatura - 273.15; // Convertir de Kelvin a Celsius
            String descripcion = doc["weather"][0]["description"];
            int humedad = doc["main"]["humidity"];
            float presion = doc["main"]["pressure"];
            
            // Mostrar datos parseados
            Serial.println(F("\n======= DATOS METEOROLÓGICOS ======="));
            Serial.println("📍 Ciudad      : " + ciudad);
            Serial.print("🌡️  Temperatura : ");
            Serial.print(temp_celsius, 1);
            Serial.println(" °C");
            Serial.println("📝 Descripción : " + descripcion);
            Serial.print("💧 Humedad     : ");
            Serial.print(humedad);
            Serial.println(" %");
            Serial.print("📈 Presión     : ");
            Serial.print(presion);
            Serial.println(" hPa");
            Serial.println(F("====================================\n"));
        }
    }
    http.end();
}

void setup(){
    Serial.begin(115200);

    setup_wifi();
}

void loop(){
    fetchWeather();

    delay(20000);
}