#include <LiquidCrystal_I2C.h>
#include <DHT.h> 

#define DHTPIN 2
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

byte termometr[8] = {
  0b00100,
  0b00110,
  0b00100,
  0b00110,
  0b00100,
  0b01110,
  0b01110,
  0b00000
};

byte kropla[8] = {
  0b00100,
  0b00100,
  0b01110,
  0b01110,
  0b10111,
  0b10111,
  0b01110,
  0b00000
};

byte stopnie[8] = {
  0b00010,
  0b00101,
  0b00010,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

int fPin = 3;
int lPin = 10;

int powtorki1 = 10;
int powtorki2 = 3;

void setup() {
  lcd.begin();
  lcd.print("Czekaj...");

  lcd.createChar(0, termometr);
  lcd.createChar(1, kropla);
  lcd.createChar(2, stopnie);

  dht.begin();

  for(int i = fPin; i <= lPin; i++) pinMode(i, OUTPUT);
}



void loop() {
  for(int i = 0; i < powtorki1; i++){
    float temp = dht.readTemperature();
    float wilg = dht.readHumidity();

    if (isnan(temp) || isnan(wilg)) {
      lcd.clear();
      lcd.home();
      lcd.print("Blad odczytu");
      delay(2000);
      return;
    }
    delay(2000);

    lcd.clear();
    lcd.home();
    lcd.write((byte)0);
    lcd.print(" ");
    lcd.print(temp);
    lcd.print(" ");
    lcd.write((byte)2);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.write((byte)1);
    lcd.print(" ");
    lcd.print(wilg);
    lcd.print("  %");

    float mode = wilg;

    if(mode > 20) digitalWrite(3, HIGH);
    else digitalWrite(3, LOW);
    if(mode > 30) digitalWrite(4, HIGH);
    else digitalWrite(4, LOW);
    if(mode > 40) digitalWrite(5, HIGH);
    else digitalWrite(5, LOW);
    if(mode > 50) digitalWrite(6, HIGH);
    else digitalWrite(6, LOW);
    if(mode > 60) digitalWrite(7, HIGH);
    else digitalWrite(7, LOW);
    if(mode > 70) digitalWrite(8, HIGH);
    else digitalWrite(8, LOW);
    if(mode > 80) digitalWrite(9, HIGH);
    else digitalWrite(9, LOW);
    if(mode > 90) digitalWrite(10, HIGH);
    else digitalWrite(10, LOW);



  }

    for(int i = fPin; i <= lPin; i++)digitalWrite(i, LOW);
    lcd.clear();

  for(int i = 0; i < powtorki2; i++){

    for(int j = -1; j < 16; j++){
      lcd.setCursor(j, 0);
      lcd.print(" PERZOT");
      delay(200);
    }

    for(int k = 16; k > -1; k--){
      lcd.setCursor(k, 1);
      lcd.print("KODUJE ");
      delay(200);
    }

    for(int i = fPin; i <= lPin; i++){
      digitalWrite(i, HIGH);
      delay(200);
    }
    
    for(int i = lPin; i >= fPin; i--){
      digitalWrite(i, LOW);
      delay(200);
    }

    lcd.clear();
  }
}
