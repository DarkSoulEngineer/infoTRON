#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

// Wi-Fi credentials
const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

AsyncWebServer server(80);

// RGB LED pins
const int redLedPin = 19;
const int greenLedPin = 18;
const int blueLedPin = 5;

// Track current color
String colorCode = "#000000";

// Apply current hex color to the LED pins
bool applyColor(String hex) {
  long number = strtol(hex.substring(1).c_str(), nullptr, 16);
  int r = (number >> 16) & 0xFF;
  int g = (number >> 8) & 0xFF;
  int b = number & 0xFF;

  analogWrite(redLedPin, r);
  analogWrite(greenLedPin, g);
  analogWrite(blueLedPin, b);
  colorCode = hex;

  printf("Applied color: R=%d, G=%d, B=%d\n", r, g, b);

  return true;
}

void setup() {
  Serial.begin(115200);
  applyColor(colorCode); // start with LEDs off

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
    Serial.println("Failed to connect to WiFi, starting AP mode...");
    WiFi.softAP("ESP32-AP", "12345678");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
  }

  // Mount SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  // Serve main page and static assets
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.serveStatic("/", SPIFFS, "/");

  server.on("/setColor", HTTP_GET, [](AsyncWebServerRequest *request) {
    if (!request->hasParam("value")) {
      request->send(400, "text/plain", "Missing 'value' query parameter");
      return;
    }

    String value = request->getParam("value")->value();
    applyColor(value);
    
    request->send(200, "text/plain", colorCode);
  });

  // Endpoint to fetch the current color
  server.on("/getColor", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", colorCode);
  });

  server.begin();
}

void loop() {
  // Async server handles requests, no blocking code needed
}
