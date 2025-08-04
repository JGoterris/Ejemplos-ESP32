#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "secrets.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.print("Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Conectado con éxito");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.println("====================================");
  Serial.print("MENSAJE RECIBIDO en topic: ");
  Serial.println(topic);
  Serial.print("Contenido: ");
  
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  Serial.print("Mensaje completo: ");
  Serial.println(messageTemp);
  Serial.println("====================================");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando conectar al broker MQTT...");
    
    // Genera un ID único usando MAC
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("\nConectado al broker MQTT!");
      
      if(client.subscribe("home/messages")) {
        Serial.println("Suscrito a home/messages");
      } else {
        Serial.println("Error al suscribirse a home/messages");
      }
      
    } else {
      Serial.print("falló, rc=");
      Serial.print(client.state());
      Serial.println(" intentando de nuevo en 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando ESP32 MQTT Client...");

  setup_wifi();

  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
  
  // Asegurar conexión inicial
  reconnect();
}

void loop() {
  if (!client.connected()) {
    Serial.println("Conexión MQTT perdida, reconectando...");
    reconnect();
  }
  
  // CRÍTICO: Mantener la conexión MQTT activa
  client.loop();

  // Publicar temperatura cada 20 segundos
  // (no se hace con delay porque no podemos bloquear o no recibiremos mensajes)
  static unsigned long lastMsg = 0;
  unsigned long now = millis();
  
  if (now - lastMsg > 20000) {
    lastMsg = now;
    
    // Generar temperatura aleatoria entre 20.0 y 30.0
    float temp = random(200, 300) / 10.0;
    
    // Convertir a String y publicar
    String mensaje = String(temp, 1); // 1 decimal
    
    if(client.publish("home/room1/temperature", mensaje.c_str())) {
      Serial.print("✓ Temperatura enviada: ");
      Serial.println(mensaje);
    } else {
      Serial.println("✗ Error enviando temperatura");
    }
  }
  
  // Pequeño delay para no saturar el loop
  delay(100);
}