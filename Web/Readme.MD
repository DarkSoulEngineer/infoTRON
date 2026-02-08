# ESP32 Async Web Server with ESP32FS

This project demonstrates how to set up an **ESP32 web server** using **AsyncWebServer** and serve web content stored in **SPIFFS** using the **ESP32FS tool**. It allows you to host HTML, CSS, JS, and other files directly from the ESP32.

## Installation

### 1. Install Required Libraries

#### Using ZIP:

1. Go to `Sketch -> Include Library -> Add .ZIP Library`
2. Download and install: [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)

#### Using Library Manager:

1. Go to `Sketch -> Include Library -> Manage Libraries`
2. Search for `Async` and install the relevant packages (`ESPAsyncWebServer`, `ESPAsyncTCP`)

---

### 2. Install ESP32FS Tool

1. Download the latest release: [ESP32FS.zip](https://github.com/me-no-dev/arduino-esp32fs-plugin/releases)
2. Move the ZIP file to Documents/Arduino/tools and unzip it here.

``` bash
WEB/
│
├─ data/               # All web content goes here
│   ├─ index.html
│   ├─ style.css
│   └─ script.js
│
├─ src/
│   └─ main.ino        # Arduino sketch
│
└─ README.md
```

Usage :
1. Place your HTML/CSS/JS files in the data/ folder.
2. In Arduino IDE, select the correct ESP32 board and COM port.
3. Use Tools -> ESP32 Sketch Data Upload to upload the data/ folder to SPIFFS.
4. Upload the sketch to ESP32.
5. Open Serial Monitor to see the IP address of your ESP32.
6. Access your web server in a browser using the ESP32 IP address.