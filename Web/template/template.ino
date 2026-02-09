#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 60) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("WiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println();
    Serial.println("Failed to connect to WiFi");
    // Optionally fallback to AP mode
    // WiFi.softAP("ESP32-AP", "12345678");
    // Serial.println("AP IP: " + WiFi.softAPIP().toString());
  }

  // Mount SPIFFS (Filesystem)
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Serve index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    File file = SPIFFS.open("/index.html", "r");
    if (!file) {
      request->send(404, "text/plain", "File not found");
      return;
    }
    String page = "";
    while(file.available()) page += char(file.read());
    file.close();
    request->send(200, "text/html", page);
  });

  // Serve CSS/JS files from SPIFFS
  server.serveStatic("/", SPIFFS, "/");

  server.begin();
}

void loop() {
  // Async server handles everything non-blocking
}
