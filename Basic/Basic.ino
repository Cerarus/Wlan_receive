#include             <ESP8266WiFi.h>
#include <WiFiUdp.h>
const int             ledPin                 = 0;
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
// ---------------------------------------------------------------------------
void setup() {

char                pass[]                = "DOQWYYCC:91";
char                ssid[]                = "SmartNet";
int                 status;

Serial.begin(9600);
pinMode(ledPin, OUTPUT);

Serial.print("Tryin connect to ");
Serial.println(ssid);

// attempt to connect to Wifi network:
status = WiFi.begin(ssid, pass);

status = WiFi.waitForConnectResult();
if (status != WL_CONNECTED) {
    Serial.println("Connection Failed");
    while (true) {}
    }

Serial.println("Connected.");
Serial.print("MAC: ");
Serial.println(WiFi.macAddress());
Serial.print("IP:  ");
Serial.println(WiFi.localIP());
Serial.print("Subnet");
Serial.println(WiFi.subnetMask());
Serial.print("Gateway");
Serial.println(WiFi.gatewayIP());
Serial.print("DNS: ");
Serial.println(WiFi.dnsIP());
Serial.print("Channel");
Serial.println(WiFi.channel());
Serial.print("Status");
Serial.println(WiFi.status());

 Udp.begin(localUdpPort);
 Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);


} // setup

// ---------------------------------------------------------------------------
void loop() {

int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\nPacketlength: %d\n", incomingPacket, len);
    String line = String(incomingPacket);
    if(line.equals("on"))
      digitalWrite(ledPin, HIGH);
     else
      digitalWrite(ledPin, LOW);
  }
}
