#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>

#include <dht.h>
dht DHT;
#define DHT11_PIN 4
Adafruit_SSD1306 display(2);

unsigned long timing;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop() {                                      // MADE BY YARIK
  int x = DHT.humidity;                            // х придаємо значення про вологість 
  int xmap = map(x, 0, 100, 0, 50);                // значення вологості від 0 до 100 , тут ми прирівнюєм від 0 до 50 так ,як стовбець у нас вертикальний а висота дісплею макс. 64 
  display.clearDisplay();                          // очищаємо дисплей
  display.fillRect(5, 62 - xmap, 13, xmap, WHITE); // вертикальний стовбець який зростає снизу до верху і залежить від значення вологості
  display.setTextColor(BLACK);                     // задаємо тексту чорний колір
  display.setCursor(6,63 - xmap);                  // встановлюєм початок написання процента вологості
  display.setFont();                               // вертаємо стандартний шрифт
  display.setTextSize(1);                          // задаємо розмір тексту 1
  display.print(DHT.humidity, 1);                  // виводимо значення вологості з датчика
  display.drawLine(18,42,41,42,WHITE);             // вивидимо лінію яка показує 40 % вологості зліва від стовбця
  display.setTextColor(WHITE);                     // задаєм тексту білий колір
  display.setCursor(19,45);                        // встановлюєм точку написання тексту/числа/значення 
  display.print("good");                           // виводим слово "good", тобто вологість яка є нормальною
  display.setCursor(24,31);                        // встановлюєм точку написання тексту/числа/значення 
  display.print("40");                             // виводим число 40 яка є нормальною вологістю 
  display.setCursor(20,55);                        // встановлюєм точку написання тексту/числа/значення 
  display.print("Humi,%");                         // виводим значення вологості                               // 
  display.drawRoundRect(26,0,75,11,2,WHITE);       // виводим обводку для слова "Meteostation"
  display.setCursor(28,2);                         // встановлюєм точку написання тексту/числа/значення
  display.print("Meteostation");                   // виводим слово "Meteostation"
  display.setTextSize(2);                          // задаємо розмір тексту 2
  display.fillRoundRect(58,17,60,20,5,WHITE);      // виводим контейнер для слова "Temp", тобто температура
  display.setTextColor(BLACK);                     // задаємо тексту чорний колір
  display.setCursor(65,19);                        // встановлюєм точку написання тексту/числа/значення 
  display.print("Temp");                           // виводим слово "Temp"
  display.setTextColor(WHITE);                     // задаємо тексту білий колір
  display.setCursor(66,43);                        // встановлюєм точку написання тексту/числа/значення
  display.print(DHT.temperature, 0);               // виводим значення температури з датчика 
  display.drawCircle(95,45,3,WHITE);               // виводим знак цельсія біля значення тесператури
  display.setCursor(103,43);                       // встановлюєм точку написання тексту/числа/значення
  display.print("C");                              // виводим букву "С" тобто знак цельсія
  display.display();                               // виводим все це що звеху на дисплей


  if (millis() - timing > 3000) {
    timing = millis();
    // READ DATA
    Serial.print("DHT11, \t");
    int chk = DHT.read11(DHT11_PIN);
    switch (chk)
    {
      case DHTLIB_OK:
        Serial.print("OK,\t");
        break;
      case DHTLIB_ERROR_CHECKSUM:
        Serial.print("Checksum error,\t");
        break;
      case DHTLIB_ERROR_TIMEOUT:
        Serial.print("Time out error,\t");
        break;
      case DHTLIB_ERROR_CONNECT:
        Serial.print("Connect error,\t");
        break;
      case DHTLIB_ERROR_ACK_L:
        Serial.print("Ack Low error,\t");
        break;
      case DHTLIB_ERROR_ACK_H:
        Serial.print("Ack High error,\t");
        break;
      default:
        Serial.print("Unknown error,\t");
        break;
    }
    // DISPLAY DATA
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t");
    Serial.println(DHT.temperature, 1);
  }
}



