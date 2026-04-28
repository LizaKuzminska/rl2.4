#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

DeviceAddress sensorAddress;

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void setup() {
  Serial.begin(115200);
  sensors.begin();

  int deviceCount = sensors.getDeviceCount();
  Serial.print("Знайдено датчиків: ");
  Serial.println(deviceCount);

  for (int i = 0; i < deviceCount; i++) {
    if (sensors.getAddress(sensorAddress, i)) {
      Serial.print("Датчик ");
      Serial.print(i);
      Serial.print(" | Адреса: ");
      printAddress(sensorAddress);
      Serial.println();
    } else {
      Serial.print("Не вдалося отримати адресу для датчика ");
      Serial.println(i);
    }
  }
}

void loop() {
  sensors.requestTemperatures();

  int deviceCount = sensors.getDeviceCount();

  for (int i = 0; i < deviceCount; i++) {
    if (sensors.getAddress(sensorAddress, i)) {
      float tempC = sensors.getTempC(sensorAddress);

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
}
