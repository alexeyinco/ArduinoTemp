/*
Ethernet Web Server
Управление светодиодом при нажатии кнопки on/off (вводе разных URL адресов) в браузере

Адрес включения светодиода:
IP-АДРЕС - тот IP, полученный при запуске примера DhcpAdressPrinter // файл - примеры - ethernet - dhcpadress printer

http://IP-АДРЕС/$1

Для того, чтобы выключить:
http://IP-АДРЕС/$2

*/

#include <SPI.h>             // библиотека для работы с SPI
#include <Ethernet.h>        // библиотека для работы с Ethernet 
boolean newInfo = 0;        // переменная для новой информации
// MAC адрес вашего Ethernet-модуля, если его у вас нет, введите любой
// или оставьте тот, что в примере
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDA, 0x02 };     

//указываем IP адрес
//будьте внимательны! IP адрес указывается тот, который вы получили запустив пример DhcpAdressPrinter
IPAddress ip(192,168,1,9);    // пример IP, вводим свой

//инифиализация библиотеки Ethernet server library
EthernetServer server(80);

void setup()
{
  pinMode(8, OUTPUT);                               //инициализируем 8 пин как выход для светодиода                  
  //запускаем сервер с указанными ранее MAC и вашим IP
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
}

void loop()
{
  // принимаем данные, посылаемые клиентом
  EthernetClient client = server.available();
  if(client){                                       //если запрос оканчивается пустой строкой
  boolean currentLineIsBlank = true;                //ставим метку об окончании запроса (дословно: текущая линия чиста)
  while (client.connected()) {                      //пока есть соединение с клиентом
    if (client.available()) {                       //если клиент активен
      char c = client.read();                       //считываем посылаемую информацию в переменную "с"
                                                  
      if(newInfo && c == ' '){                      //если переменная новой информации = 1 и "с", в которой записан запрос, равен пустой строке
        newInfo = 0;                                //то обнуляем переменную поступления новой информации
      }
      
      if(c == '$'){                                 //если переменная "с", несущая отправленный нам запрос, содержит символ $ 
                                                    //(все новые запросы) - "$" подразумевает разделение получаемой информации (символов)
        newInfo = 1;                                //то пришла новая информация, ставим метку новой информации в 1
      }
      
      /************************************************************************************************
      Примечание:
      Символ $ используется как обычный символ, который разделяет 1 от 2
      На практике применяют символ &, который разделяет новые переменные от последующих
      Это использьуется, например, в GET-запросах, которые выглядят подобным образом:
      client.print("GET /controlbar/wp-content/data.php?uid=" + ID + "&type=" + type + "&value=" + value);
      как видите, знак & разделяет значение переменной - ID и переменную type     
      ***************************************************************************************************/
      
                                                     //Проверяем содержание URL - присутствует $1 или $2
      if(newInfo == 1){                              //если есть новая информация
          Serial.println(c);
          if(c == '1'){                              //и "с" содержит 1
          Serial.println("ON");
          digitalWrite(8, HIGH);                    //то зажигаем светодиод
          }
          
          if(c == '2'){                              //если "с" содержит 2
          Serial.println("OFF");
          digitalWrite(8, LOW);                     //гасим светодиод
          }    
      } 
      
      if (c == '\n') {                              //если "с" равен символу новой строки
        currentLineIsBlank = true;                  //то начинаем новую строку
      } 
      else if (c != '\r') {                         //иначе, если "с" не равен символу возврата курсора на начало строки
        currentLineIsBlank = false;                 //то получаем символ на текущей строке
      }
      
          //допилить до температуры
    
      if (c == '\n' && currentLineIsBlank) {        //выводим HTML страницу
        client.println("HTTP/1.1 200 OK");          //заголовочная информация
        client.println("Content-Type: text/html");
        client.println("Connection: close");  
        client.println("Refresh: 30");              //автоматическое обновление каждые 30 сек
        client.println();
        client.println("<!DOCTYPE HTML>");          //HTML тип документа
        client.println("<html>");                   //открытие тега HTML 
        client.print("<title>Web Server</title>");                  //название страницы
        client.print("<H1>Web Server ArduinoTemp</H1>");                        //заголовок на странице
        client.print("<a href=\"/$1\"><button>On</button></a>");       //кнопка включить
        client.print("<a href=\"/$2\"><button>Off</button></a>");      //кнопка выключить
        client.println("<br />");       
        client.println("</html>");                  //закрываем тег HTML
        break;                                      //выход
      }
    
    }
    
  }
  delay(1);                                          //время на получение новых данных
  client.stop();                                     //закрываем соеднение 
}
}
