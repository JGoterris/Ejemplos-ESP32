# Repositorio de Ejemplos para ESP32-S3 con PlatformIO

Este repositorio contiene una colección de ejemplos prácticos para la placa de desarrollo ESP32-S3, gestionados a través de un único proyecto de PlatformIO.

## Características

- **Múltiples Ejemplos**: Varios programas autocontenidos en un solo proyecto.
- **Gestión con Entornos**: Utiliza los entornos de PlatformIO (`[env]`) para facilitar el cambio entre diferentes programas sin necesidad de modificar el código o la estructura de carpetas.
- **Organización Limpia**: Cada ejemplo reside en su propio directorio dentro de la carpeta `examples/`.

## Ejemplos Disponibles

### 1. Estación Meteorológica (WeatherAPIExample)

- **Ubicación**: `examples/WeatherAPIExample`
- **Descripción**: Este programa se conecta a una red WiFi y realiza una consulta a la API de OpenWeatherMap para obtener datos meteorológicos de una ubicación específica. Luego, muestra la información (ciudad, temperatura, humedad, etc.) en el monitor serie.
- **Librerías**: `ArduinoJson`, `HTTPClient`.

### 2. Cliente MQTT (MqttClient)

- **Ubicación**: `examples/MqttClient`
- **Descripción**: Este ejemplo conecta el ESP32 a un broker MQTT. Se suscribe a un topic para recibir mensajes y publica una temperatura simulada en otro topic a intervalos regulares. Es ideal para probar la conectividad y la comunicación MQTT.
- **Librerías**: `PubSubClient`.

## Configuración Inicial

### 1. Crear el archivo `secrets.h`

Para que los ejemplos funcionen, necesitas proporcionar tus credenciales de WiFi y, en algunos casos, claves de API. Esto se hace creando un archivo `secrets.h` dentro de la carpeta `include/`.

1.  Navega a la carpeta `include/`.
2.  Crea un nuevo archivo llamado `secrets.h`.
3.  Copia y pega el siguiente contenido, reemplazando los valores con tus propias credenciales.

```cpp
// -- Credenciales WiFi --
#define WIFI_SSID "TU_NOMBRE_DE_WIFI"
#define WIFI_PASSWORD "TU_CONTRASEÑA_DE_WIFI"

// -- Clave de API para OpenWeatherMap --
// (Necesaria para el ejemplo WeatherStation)
#define OPENWEATHER_API_KEY "TU_API_KEY_DE_OPENWEATHERMAP"

// -- Dirección del Broker MQTT --
// (Necesaria para el ejemplo MqttClient)
#define MQTT_SERVER "DIRECCION_IP_DE_TU_BROKER"
```

**Importante**: El archivo `secrets.h` es referenciado por los ejemplos, pero no está incluido en este repositorio. Debes crearlo localmente.

### 2. Cómo cambiar entre ejemplos

Este proyecto utiliza entornos de PlatformIO para gestionar los diferentes programas. Puedes cambiar entre ellos fácilmente desde Visual Studio Code:

1.  En la barra de actividades de la izquierda, haz clic en el **icono de PlatformIO** (parece la cabeza de un insecto).
2.  Se abrirá el panel de **"PROJECT TASKS"**.
3.  Verás los diferentes entornos disponibles bajo la sección "Default":
    *   `esp32-s3-devkitc-1 (weather_api_example)`
    *   `esp32-s3-devkitc-1 (mqtt_client)`
4.  Para trabajar con un programa específico, simplemente **expande su entorno** y utiliza sus tareas:
    *   **Build**: Compila solo ese programa.
    *   **Upload**: Compila y sube ese programa a tu placa.
    *   **Monitor**: Abre el monitor serie para ver la salida de ese programa.
