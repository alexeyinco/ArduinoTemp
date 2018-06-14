#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };                                       

EthernetClient client;
char server[] = "TestWebServer01"; // имя сервера с домена
int buff=0;
const int led=5;

void setup()
{
  Ethernet.begin(mac);
  sensors.begin();
  pinMode( led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop()
 {
  
  sensors.requestTemperatures();
  
    if (client.connect(server, 80)) 
{

    client.print( "GET /add_data.php?");
    client.print("temperature=");
    client.print( sensors.getTempCByIndex(0) );
    client.print("&");
    client.print("&");
    client.print("temperature1=");
    client.print( sensors.getTempCByIndex(1) );
    client.println( " HTTP/1.1");
    client.print( "Host: " );
    client.println(server);
    client.println( "Connection: close" );
    client.println();
    client.println();
   
    delay(200);
    
      while (client.available())
 {
      char c = client.read();
        if ( c=='1')
        {
        buff=1;
        }
        if ( c=='0')
        {
         buff=0;
        }
      } 
      client.stop();
      client.flush();
      delay(100); 
  }
  else 
  {
   client.stop();
   delay(1000);
   client.connect(server, 80);
  }

  if ( buff==1)
        {
        digitalWrite (led1, HIGH);
        }
        else
        {
          digitalWrite(led1, LOW);
        }
  delay(500);
}

