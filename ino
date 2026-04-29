#include <OneWire.h>
// Бібліотека для шини OneWire

#include <DallasTemperature.h>
// Бібліотека для температурних датчиків Dallas, наприклад DS18B20

#define ONE_WIRE_BUS 4
// Пін GPIO4, до якого підключена шина OneWire

OneWire oneWire(ONE_WIRE_BUS);
// Створюємо об'єкт OneWire на піні 4

DallasTemperature sensors(&oneWire);
// Створюємо об'єкт для роботи з датчиками температури

DeviceAddress sensorAddress;
// Масив для збереження адреси конкретного датчика


// Функція для виводу адреси датчика
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    // Адреса датчика складається з 8 байтів

    if (deviceAddress[i] < 16) Serial.print("0");
    // Якщо байт менший за 16, додаємо 0 спереду,
    // щоб адреса виглядала красиво в HEX-форматі

    Serial.print(deviceAddress[i], HEX);
    // Виводимо байт адреси у шістнадцятковому форматі
  }
}


void setup() {
  Serial.begin(115200);
  // Запускаємо Serial Monitor

  sensors.begin();
  // Запускаємо роботу з датчиками OneWire

  int deviceCount = sensors.getDeviceCount();
  // Рахуємо, скільки датчиків підключено до шини

  Serial.print("Знайдено датчиків: ");
  Serial.println(deviceCount);


  // Виводимо адреси всіх знайдених датчиків
  for (int i = 0; i < deviceCount; i++) {

    if (sensors.getAddress(sensorAddress, i)) {
      // Пробуємо отримати адресу датчика з номером i

      Serial.print("Датчик ");
      Serial.print(i);

      Serial.print(" | Адреса: ");
      printAddress(sensorAddress);
      // Друкуємо унікальну адресу датчика

      Serial.println();
    } 
    else {
      Serial.print("Не вдалося отримати адресу для датчика ");
      Serial.println(i);
    }
  }
}


void loop() {
  sensors.requestTemperatures();
  // Відправляємо команду всім датчикам:
  // “виміряйте температуру”

  int deviceCount = sensors.getDeviceCount();
  // Знову перевіряємо кількість датчиків

  for (int i = 0; i < deviceCount; i++) {

    if (sensors.getAddress(sensorAddress, i)) {
      // Отримуємо адресу датчика

      float tempC = sensors.getTempC(sensorAddress);
      // Зчитуємо температуру саме з цього датчика по його адресі

      Serial.print("Датчик ");
      Serial.print(i);

      Serial.print(" | Адреса: ");
      printAddress(sensorAddress);

      Serial.print(" | Температура: ");
      Serial.print(tempC);

      Serial.println(" °C");
    }
  }

  Serial.println("---------------------");

  delay(2000);
  // Оновлення кожні 2 секунди
}
