#include <LiquidCrystal.h>
#include <DHT11.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en ,d4, d5, d6, d7);

DHT11 dht11(10);

const int SCLK = 9; //CLK
const int IO = 8; //DAT
const int CE = 7; // RST

ThreeWire myWire(8, 9, 7);  // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  lcd.begin(16, 2);
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  if (!Rtc.IsDateTimeValid()) {
    Rtc.SetDateTime(compiled);
  }
  if (Rtc.GetIsWriteProtected()) {
    Rtc.SetIsWriteProtected(false);
  }
  if (!Rtc.GetIsRunning()) {
    Rtc.SetIsRunning(true);
  }
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) {
    Rtc.SetDateTime(compiled);
  }
}

void loop() {
  int temperature = 0;
  int humidity = 0;
  int result = dht11.readTemperatureHumidity(temperature, humidity);

  RtcDateTime now = Rtc.GetDateTime();

  lcd.setCursor(4, 0);
  lcd.print(now.Hour());
  lcd.print(":");
  if(now.Minute() < 10) lcd.print("0");
  lcd.print(now.Minute());
  lcd.print(":");
  if(now.Second() < 10) lcd.print("0");
  lcd.print(now.Second());

  if ( result == 0) 
  {
    lcd.setCursor(0, 1);
    lcd.print("Tmp:");
    lcd.print(temperature);
    lcd.print("C  ");

    lcd.setCursor(9, 1);
    lcd.print("Hmd:");
    lcd.print(humidity);
    lcd.print("%");
  }

  delay(1000);

}
