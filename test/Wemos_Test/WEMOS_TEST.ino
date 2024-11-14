#include <WiFi.h>
#include <WebServer.h>

// Enter your Wi-Fi credentials here
const char* ssid = "asd";      // Your Wi-Fi network name
const char* password = "123";  // Your Wi-Fi password

WebServer server(80); // Use port 80 for the web server

// Web page content
String webpage = "<html><body><h1>Wemos D1 R32 Web Server</h1><p>Hello, this is a simple web server!</p></body></html>";

// Function to connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nWi-Fi connection successful!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Web server handling
void handleRoot() {
  server.send(200, "text/html", webpage); // Send HTML content with 200 OK status code
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  server.on("/", handleRoot); // Direct root page requests to handleRoot function
  server.begin(); // Start the web server
  Serial.println("Web server is active!");
}

void loop() {
  server.handleClient(); // Listen and handle incoming requests
}
