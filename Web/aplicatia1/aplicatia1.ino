#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

AsyncWebServer server(80);
const int redLedPin = 2;   // LED GPIO
bool redLedState = false;  // false=OFF, true=ON

void setup() {
  Serial.begin(115200);
  pinMode(redLedPin, OUTPUT);
  digitalWrite(redLedPin, LOW);

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
    page.replace("%RED_LED_STATE%", redLedState ? "ON" : "OFF");
    request->send(200, "text/html", page);
  });

  // Toggle LED
  server.on("/toggleRedLED", HTTP_GET, [](AsyncWebServerRequest *request) {
    redLedState = !redLedState;
    digitalWrite(redLedPin, redLedState ? HIGH : LOW);
    request->send(200, "text/plain", String("Red LED is ") + (redLedState ? "ON" : "OFF"));
  });

  // Get current LED state
  server.on("/getRedLEDState", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String("Red LED is ") + (redLedState ? "ON" : "OFF"));
  });

  // Serve CSS/JS files from SPIFFS
  server.serveStatic("/", SPIFFS, "/");

  server.begin();
}

void loop() {
  // Async server handles everything non-blocking
}
