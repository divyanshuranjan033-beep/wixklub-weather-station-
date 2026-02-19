#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);

void setup() {
  Ethernet.begin(mac); // Starts Ethernet with a dynamic IP
  server.begin();
  dht.begin();
}

void loop() {
  EthernetClient client = server.available();
  if (client) {
    float t = dht.readTemperature();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Refresh: 5"); // Page updates every 5 seconds
    client.println();
    client.print("<h1>Room Temperature</h1>");
    client.print("Temperature: ");
    client.print(t);
    client.print(" *C");
    delay(1);
    client.stop();
  }
}
