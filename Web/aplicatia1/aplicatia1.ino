#include <WiFi.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>


const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

AsyncWebServer server(80);

const int redLedPin = 2;
bool redLedState = false;

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
    // WiFi.softAP("ESP32-AP", "12345678");
    // Serial.println("AP IP: " + WiFi.softAPIP().toString());
    return;
  }

  // Mount LittleFS
  if (!LittleFS.begin(true)) {
    Serial.println("LittleFS Mount Failed");
    return;
  }

  // Serve index.html
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    File file = LittleFS.open("/index.html", "r");
    if (!file) {
      request->send(404, "text/plain", "File not found");
      return;
    }
    String page = "";
    while(file.available()) page += char(file.read());
    file.close();
    request->send(200, "text/html", page);
  });

  // REST API: toggle LED
  server.on("/api/toggleRedLED", HTTP_GET, [](AsyncWebServerRequest *request){
    redLedState = !redLedState;
    digitalWrite(redLedPin, redLedState ? HIGH : LOW);
    request->send(200, "application/json",
                  String("{\"redLedState\":\"") + (redLedState ? "ON" : "OFF") + "\"}");
  });

  // REST API: get LED state
  server.on("/api/getRedLEDState", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/json",
                  String("{\"redLedState\":\"") + (redLedState ? "ON" : "OFF") + "\"}");
  });

  // Serve static files (HTML, CSS, JS)
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  server.begin();
}

void loop() {
  // Non-blocking, Async server handles requests
}
