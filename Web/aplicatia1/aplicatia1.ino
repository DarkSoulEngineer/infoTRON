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

  /*
    * server.on() defines the route handlers for the web server. We have:
    * "/" to serve the main HTML page (index.html)
    * [](AsyncWebServerRequest *request) { ... } is a lambda function
        that handles the incoming HTTP request and sends the appropriate response.
  */

  /*
    * File file = LittleFS.open("/index.html", "r");
        opens the index.html file from the LittleFS filesystem in read mode.
    * If the file cannot be opened, we send a 404 response.
    * If the file is opened successfully, we read its contents into a String variable and send
        it as an HTTP response with a 200 status code and "text/html" content type.
  */

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

  /*
    * server.on("/api/toggleRedLED", HTTP_GET, [](AsyncWebServerRequest *request) { ... });
        defines a route for toggling the red LED state. When this endpoint is accessed via a GET request,
        it toggles the redLedState variable, updates the physical LED state using digitalWrite(), and sends
        a JSON response indicating the new state of the LED.
    * server.on("/api/getRedLEDState", HTTP_GET, [](AsyncWebServerRequest *request) { ... });
        defines a route for retrieving the current state of the red LED. When accessed, it sends a JSON response
        with the current state (ON or OFF) of the red LED.
  */

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

  /*
    * server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
        is a convenient way to serve static files from the LittleFS filesystem.
        It serves files from the root directory ("/") and sets "index.html"
        as the default file to serve when the root URL is accessed.
  */

  /*
    * server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");
          este o metodă convenabilă de a servi fișiere statice din sistemul de fișiere LittleFS.
          Servește fișiere din directorul rădăcină ("/") și setează "index.html"
          ca fișier implicit atunci când se accesează URL-ul rădăcină.
  */


  // Serve static files (HTML, CSS, JS)
  server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html");

  server.begin();
}

void loop() {
  // Non-blocking, Async server handles requests
}
