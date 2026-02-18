#include <WiFiS3.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ---------- WiFi Credentials ---------- */
const char* ssid = "Redmi Note 13 5G";
const char* password = "PwSAv61Ff";

/* ---------- Web Server ---------- */
WiFiServer server(80);

/* ---------- OLED ---------- */
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ---------- Sensors ---------- */
#define TDS_PIN A0
#define TURBIDITY_PIN A1
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

/* ---------- Averaged Values ---------- */
float avgTDS = 0;
float avgNTU = 0;
float avgTemp = 0;

/* ---------- Helper Functions ---------- */
float readTDS() {
  int raw = analogRead(TDS_PIN);
  float voltage = raw * (5.0 / 1023.0);

  float tds = (133.42 * voltage * voltage * voltage
               - 255.86 * voltage * voltage
               + 857.39 * voltage) * 0.5;

  if (tds < 0) tds = 0;
  return tds;
}

float readTurbidity() {
  int raw = analogRead(TURBIDITY_PIN);
  float voltage = raw * (5.0 / 1023.0);

  // Reversed calibration: higher voltage = clearer water
  float ntu = 2050 - (
                -1120.4 * voltage * voltage
                + 5742.3 * voltage
                - 4352.9
              );

  if (ntu < 0) ntu = 0;
  if (ntu > 2050) ntu = 2050;

  return ntu;
}

float readTemperature() {
  tempSensor.requestTemperatures();
  return tempSensor.getTempCByIndex(0);
}

/* ---------- Setup ---------- */
void setup() {
  Serial.begin(9600);

  /* OLED init */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  /* Temperature sensor */
  tempSensor.begin();

  /* WiFi */
  WiFi.begin(ssid, password);
  display.setCursor(0, 0);
  display.println("Connecting WiFi...");
  display.display();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  server.begin();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("WiFi Connected");
  display.println(WiFi.localIP());
  display.display();
}

/* ---------- Main Loop ---------- */
void loop() {

  float tdsSum = 0;
  float ntuSum = 0;
  float tempSum = 0;

  for (int i = 0; i < 3; i++) {
    tdsSum += readTDS();
    ntuSum += readTurbidity();
    tempSum += readTemperature();
    delay(3000);
  }

  avgTDS = tdsSum / 3.0;
  avgNTU = ntuSum / 3.0;
  avgTemp = tempSum / 3.0;

  /* ---------- OLED Display ---------- */
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Water Quality");
  display.println("----------------");

  display.print("TDS: ");
  display.print(avgTDS, 1);
  display.println(" ppm");

  display.print("Turb: ");
  display.print(avgNTU, 1);
  display.println(" NTU");

  display.print("Temp: ");
  display.print(avgTemp, 1);
  display.println(" C");

  display.display();

  /* ---------- Website Handling ---------- */
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    if (request.indexOf("/data") >= 0) {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: application/json");
      client.println("Access-Control-Allow-Origin: *");
      client.println("Connection: close");
      client.println();
      client.print("{\"tds\":");
      client.print(avgTDS, 1);
      client.print(",\"turbidity\":");
      client.print(avgNTU, 1);
      client.print(",\"temperature\":");
      client.print(avgTemp, 1);
      client.print("}");
    } 
    else {
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("Connection: close");
      client.println();
      client.println("<h1>Arduino Water Quality Monitor</h1>");
      client.println("<p>Use /data endpoint</p>");
    }

    client.stop();
  }
}