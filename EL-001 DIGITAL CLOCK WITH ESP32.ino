
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <time.h>

const char* ssid = "WI-FI";
const char* password = "WI-FI PASSWORD";

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();
  lcd.print("Conectando WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  lcd.clear();
  lcd.print("Ajustando hora");

  // Monterrey: UTC-6
  configTime(-6 * 3600, 0,
             "pool.ntp.org",
             "time.nist.gov");

  struct tm t;
  if (!getLocalTime(&t, 20000)) {
    lcd.clear();
    lcd.print("Error de hora");
    return;
  }

  lcd.clear();
}

void loop() {
  struct tm t;

  if (getLocalTime(&t)) {
    char hora[17];
    char fecha[17];

    strftime(hora, sizeof(hora), "%H:%M:%S", &t);
    strftime(fecha, sizeof(fecha), "%d/%m/%Y", &t);

    lcd.setCursor(0, 0);
    lcd.print("Hora: ");
    lcd.print(hora);
    lcd.print("  ");

    lcd.setCursor(0, 1);
    lcd.print("Fecha: ");
    lcd.print(fecha);
    lcd.print("  ");
  }

  delay(500);
}
