#include <Wire.h> // 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27,16,2);//Inicializa pantalla LCD con modulo I2C

int SENSOR = 2; //Inicializa entero PIN D2
float temp;
int humedad, Humedad_Suelo; // Iniciailiza variables tipo entero de temperatura y humedad
int pinOut = 3; //inicializa variable de salida PIN D3

DHT dht (SENSOR, DHT22);

void setup() {
    lcd.backlight();
    lcd.init();
    pinMode (pinOut, OUTPUT);
    
    Serial.begin(9600);
    dht.begin();
}

void loop(){
  humedad = dht.readHumidity(); //humedad del sensor
  temp = dht.readTemperature(); //Temperatura del sensor
  Humedad_Suelo = analogRead(A0); //Humedad de suelo SENSOR 109
 
  Serial.print("Temperatura: "); //Monitor
  Serial.print(temp);
  Serial.println("ºC");
  Serial.print("Humedad: ");//Monitor
  Serial.print(humedad);
  Serial.println("%");
//DH072 sensor capacitivo de humedad
  Serial.print("Humedad Suelo: ");
  Serial.println(Humedad_Suelo); //Toma de datos del sensor capacitivo
  
const int SECO = 582; // value for seco sensor Valor 1 de 0% +-5%
const int HUMEDO = 318; // value for Mojado sensor Valor 2 de 100% +-5%
  
int Porcentaje_Humedad_Suelo= map(Humedad_Suelo, HUMEDO, SECO, 100, 0);
  Serial.print("Porcentaje de Humedad Suelo: "); //Monitor
  Serial.println(Porcentaje_Humedad_Suelo);
  
if (temp >= 26){              //Condicional para activar salida
    digitalWrite(pinOut, HIGH);
  }
  else {
    digitalWrite(pinOut, LOW);
  }
  // COnfiguración de pantalla LCD
  lcd.begin(16, 2); 
  lcd.setCursor(0,0); 
  //LCD impresion temperatura DHT 22
  lcd.print("T:"); 
  lcd.setCursor(2,0); 
  lcd.print(temp);
  lcd.setCursor(7,0); 
  lcd.print("C");
  //LCD impresion humedad DHT22
  lcd.setCursor(0,1); 
  lcd.print("HAm:"); 
  lcd.setCursor(4,1); 
  lcd.print(humedad);
  lcd.setCursor(6,1); 
  lcd.print("%");
  // Humedad suelo 
  lcd.setCursor(8,1); 
  lcd.print("HSu:"); 
  lcd.setCursor(12,1); 
  lcd.print(Porcentaje_Humedad_Suelo);
  lcd.setCursor(14,1); 
  lcd.print("%");
  delay(400);
}
