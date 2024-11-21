#include <WiFi.h>
#include <DHT.h>

// Configuración del WiFi
const char* ssid = "manuel";
const char* password = "00000000";

// Configuración del sensor DHT11
#define DHTPIN 4          // Pin GPIO donde está conectado el DHT11
#define DHTTYPE DHT11     // Tipo de DHT
DHT dht(DHTPIN, DHTTYPE);

// Configuración del sensor MQ-135
#define MQ135PIN 34       // Pin analógico donde está conectado el MQ-135

// Servidor Web en el puerto 80
WiFiServer server(80);

const int ledPin = 2; // GPIO 2

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  // Iniciar DHT
  dht.begin();

  // Conectar al Wi-Fi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conexión WiFi establecida.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
  digitalWrite(ledPin, HIGH);

  // Iniciar el servidor
  server.begin();
}

void loop() {
  // Medir temperatura y humedad
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();

  // Leer la calidad del aire desde el MQ-135
  int calidadAire = analogRead(MQ135PIN);

  // Verificar si los datos del DHT son válidos
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error al leer del sensor DHT11");
    return;
  }

  // Aceptar conexiones de clientes
  WiFiClient client = server.available();
  
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // Crear página HTML con JavaScript para actualizar datos
    /*String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><title>Document</title></head><body>";
    html += "<h1>Mediciones de Ambiente</h1>";
    html += "<p><strong>Temperatura:</strong> <span id='temp'>" + String(temperatura) + " °C</span></p>";
    html += "<p><strong>Humedad:</strong> <span id='humidity'>" + String(humedad) + " %</span></p>";
    html += "<p><strong>Calidad del Aire (MQ-135):</strong> <span id='airQuality'>" + String(calidadAire) + "</span></p>";
    html += "<script>";
    html += "setInterval(async function() {";
    html += "  let response = await fetch('/data');";
    html += "  let data = await response.json();";
    html += "  document.getElementById('temp').innerText = data.temperatura + ' °C';";
    html += "  document.getElementById('humidity').innerText = data.humedad + ' %';";
    html += "  document.getElementById('airQuality').innerText = data.calidadAire;";
    html += "}, 2000);"; // Actualizar cada 2 segundos
    html += "</script>";
    html += "</body></html>";*/

    String html = "<!DOCTYPE html>";
html += "<html lang='en'>";
html += "<head>";
html += "    <meta charset='UTF-8'>";
html += "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
html += "    <title>IoT - Monitor de Ambiente</title>";
html += "    <style>";
html += "        body {";
html += "            font-family: Arial, sans-serif;";
html += "            text-align: center;";
html += "            margin-top: 50px;";
html += "            background: #f4f4f4;";
html += "        }";
html += "        h1 {";
html += "            color: #333;";
html += "        }";
html += "        .result {";
html += "            font-size: 1.2em;";
html += "            color: #007bff;";
html += "            margin: 20px 0;";
html += "        }";
html += "        #recomendaciones {";
html += "            display: none;";
html += "            margin-top: 30px;";
html += "            text-align: center;";
html += "            max-width: 600px;";
html += "            margin: 0 auto;";
html += "            background-color: #fff;";
html += "            padding: 20px;";
html += "            border-radius: 10px;";
html += "            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);";
html += "        }";
html += "        button {";
html += "            padding: 10px 20px;";
html += "            font-size: 1em;";
html += "            cursor: pointer;";
html += "            background-color: #007bff;";
html += "            color: #fff;";
html += "            border: none;";
html += "            border-radius: 5px;";
html += "            margin: 5px;";
html += "        }";
html += "        button:hover {";
html += "            background-color: #0056b3;";
html += "        }";
html += "        #textoRecomendaciones{";
html += "            text-align: left;";
html += "        }";
html += "        #textoRecomendaciones strong{";
html += "            display: block;";
html += "            margin-TOP: 15px;";
html += "        }";
html += "    </style>";
html += "</head>";
html += "<body>";
html += "    <h1>Monitor de Ambiente IoT</h1>";
html += "    <div class='result'>";
html += "        <p>Temperatura: <span id='temp'>" + String(temperatura) + "</span> °C</p>";
html += "        <p>Humedad: <span id='humidity'>" + String(humedad) + "</span> %</p>";
html += "        <p>Calidad del Aire: <span id='airQuality'>" + String(calidadAire) + "</span></p>";
html += "    </div>";
html += "    <button id='mostrarRecomendaciones'>Obtener Recomendaciones</button>";
html += "    <button id='detenerLectura'>Detener Audio</button>";
html += "    <div id='recomendaciones'>";
html += "        <h2>Recomendaciones</h2>";
html += "        <p id='textoRecomendaciones'></p>";
html += "    </div>";
html += "    <script>";
html += "        const speechSynthesisUtterance = new SpeechSynthesisUtterance();";
html += "        async function mostrarRecomendaciones() {";
html += "            document.getElementById('textoRecomendaciones').innerHTML = '<strong>Cargando...</strong>';";
html += "            document.getElementById('recomendaciones').style.display = 'block';";
html += "                const temp = parseInt(document.getElementById('temp').textContent);";
html += "                const humedad = parseInt(document.getElementById('humidity').textContent);";
html += "                const calidad = parseInt(document.getElementById('airQuality').textContent);";
html += "                let calidadTxt = '';";
html += "                if (calidad <= 300) {";
html += "                    calidadTxt = 'Buena, sin tanto CO2';";
html += "                } else if (calidad > 300 && calidad <= 1000) {";
html += "                    calidadTxt = 'Regular, con moderado CO2';";
html += "                } else if (calidad > 1000) {";
html += "                    calidadTxt = 'Mala, con bastante CO2';";
html += "                }";
html += "                const prompt = `";
html += "                    Condiciones actuales:";
html += "                    - Temperatura: ${temp}°C";
html += "                    - Humedad: ${humedad}%";
html += "                    - Calidad del aire: ${calidadTxt}";
html += "                    Proporciona recomendaciones para mejorar el ambiente y consejos prácticos para las personas en este entorno.";
html += "                `;";
html += "                try {";
html += "                    const res = await fetch('https://api-gemini-drab.vercel.app/api/gemini', {";
html += "                        method: 'POST',";
html += "                        headers: {";
html += "                            'Content-Type': 'application/json',";
html += "                        },";
html += "                        body: JSON.stringify({ prompt }),";
html += "                    });";
html += "                    const data = await res.json();";
html += "                    if (data) {";
html += "                        console.log(data);";
html += "                    } else {";
html += "                        console.log('Error en la respuesta');";
html += "                    }";
html += "                } catch (error) {";
html += "                    console.error('Error en la solicitud:', error);";
html += "                }";
html += "                document.getElementById('textoRecomendaciones').innerText = data;";
html += "                leerTexto();";
html += "        }";
html += "        function leerTexto() {";
html += "            const texto = document.getElementById('textoRecomendaciones').innerText;";
html += "            if (speechSynthesis.speaking) {";
html += "                speechSynthesis.cancel();";
html += "            }";
html += "            speechSynthesisUtterance.text = texto;";
html += "            speechSynthesis.speak(speechSynthesisUtterance);";
html += "        }";
html += "        function detenerLectura() {";
html += "            if (speechSynthesis.speaking) {";
html += "                speechSynthesis.cancel();";
html += "            }";
html += "        }";
html += "        let $mostrarRecomendaciones = document.getElementById('mostrarRecomendaciones');";
html += "        let $detenerLectura = document.getElementById('detenerLectura');";
html += "        $mostrarRecomendaciones.addEventListener('click', () => mostrarRecomendaciones());";
html += "        $detenerLectura.addEventListener('click', () => detenerLectura());";
html += "    </script>";
html += "</body>";
html += "</html>;"

    
    // Enviar respuesta HTTP al cliente
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.print(html);
    client.println();
    
    delay(1);
  }

  // Crear una respuesta JSON con los datos si la solicitud es a "/data"
  WiFiClient clientData = server.available();
  if (clientData) {
    String requestData = clientData.readStringUntil('\r');
    clientData.flush();

    if (requestData.indexOf("GET /data") >= 0) {
      String jsonData = "{";
      jsonData += "\"temperatura\":" + String(temperatura) + ",";
      jsonData += "\"humedad\":" + String(humedad) + ",";
      jsonData += "\"calidadAire\":" + String(calidadAire);
      jsonData += "}";

      clientData.println("HTTP/1.1 200 OK");
      clientData.println("Content-Type: application/json");
      clientData.println();
      clientData.print(jsonData);
      clientData.println();
    }

    delay(1);
  }

  // Esperar un poco antes de hacer otra medición
  delay(2000);
}
