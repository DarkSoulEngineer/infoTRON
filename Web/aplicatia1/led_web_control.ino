#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "CHANGE_SSID";
const char* password = "CHANGE_PASSWORD";

AsyncWebServer server(80);
const int ledPin = 2;   // LED GPIO
bool ledState = false;  // false=OFF, true=ON

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

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
    // WiFi.softAP("ESP32-AP");
    // Serial.println("AP IP: " + WiFi.softAPIP().toString());
  }

  // Mount SPIFFS
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
    page.replace("%LED_STATE%", ledState ? "ON" : "OFF");
    request->send(200, "text/html", page);
  });

  // Toggle LED
  server.on("/toggleLED", HTTP_GET, [](AsyncWebServerRequest *request) {
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
    request->send(200, "text/plain", String("LED is ") + (ledState ? "ON" : "OFF"));
  });

  // Get current LED state
  server.on("/getLEDState", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String("LED is ") + (ledState ? "ON" : "OFF"));
  });

  // Serve CSS/JS files from SPIFFS
  server.serveStatic("/", SPIFFS, "/");

  server.begin();
}

void loop() {
  // Async server handles everything non-blocking
}
