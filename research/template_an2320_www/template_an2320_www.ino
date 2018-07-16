#include <Wire.h>
#include <EtherCard.h>

static byte mymac[] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };
static byte myip[] = { 192, 168, 1, 177 };
byte Ethernet::buffer[700];
float humidity = 0.00;
float temperature = 0.00;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);

  if (!ether.begin(sizeof Ethernet::buffer, mymac, 10))
    Serial.println("No se ha podido acceder a la controlador Ethernet");
  else
    Serial.println("Controlador Ethernet inicializado");

  if (!ether.staticSetup(myip))
    Serial.println("No se pudo establecer la dirección IP");
  Serial.println();

  //  Serial.println("Setting up DHCP");
  //  if (!ether.dhcpSetup()){
  //    Serial.println( "DHCP failed");
  //  }

  delay(100);

  Serial.println("done");

  ether.printIp("My IP: ", ether.myip);

}
void loop() {

  readSensor();

  if (ether.packetLoop(ether.packetReceive())) {
    printPage(humidity, temperature);
  }
}
void readSensor() {
  readAM2320();
}
void readAM2320() {
  // AM2320
  int ans = Wire.requestFrom(0x5c, 6); // request 6 bytes

  Wire.beginTransmission(0x5c);     // address(0x5c)
  Wire.write(0x03); //Arduino read senser
  Wire.write(0x00); //address of Humidity
  Wire.write(0x04); //The number of address
  //(Humidity1,Humidity2,Temperature1,Temperature2)
  Wire.endTransmission();//
  delay(100);

  int H1, H2, T1, T2 = 0;
  while (Wire.available() != 0) {
    for (int i = 1; i <  ans + 1; i++) {
      int code = Wire.read();
      switch (i) {
        case 5:
          T1 = code;
          break;
        case 6:
          T2 = code;
          break;
        case 3:
          H1 = code;
          break;
        case 4:
          H2 = code;
          break;
        default:
          break;
      }
    }
  }
  humidity = (H1 * 256 + H2) / 10.0;
  temperature = (T1 * 256 + T2) / 10.0;

  if (humidity == 0)readAM2320();
}
void printPage(float humidity, float temperature) {
  char strTemp[6];
  char strHum[6];

  Serial.print(" response Temp : ");

  dtostrf(temperature, 3, 2, strTemp);
  dtostrf(humidity, 3, 2, strHum);

  Serial.print("temperature : ");
  Serial.print(strTemp);
  Serial.print("'C  humidity : ");
  Serial.print(strHum);
  Serial.println("% ");

  BufferFiller bfill = ether.tcpOffset();
  bfill.emit_p(PSTR(
                 "HTTP/1.0 200 OK\r\n"
                 "Content-Type: text/html\r\n"
                 "Pragma: no-cache\r\n\r\n"
               ));

  bfill.emit_p(PSTR(
                 "<html><head><title>Web Control</title></head><body>"
                 "<body bgcolor=""#ccccff"">"
                 "<font size=""6"">"
                 "<center>"
                 "Temperature... : "
                 "<b> $S &deg;C </b>"
                 "Humidity... : "
                 "<b> $S %</b>"
                 "</body></html>"
               ),
               strTemp, strHum);
  ether.httpServerReply(bfill.position());
  delay(100);

}

