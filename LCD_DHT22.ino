
//LIBRERIAS
#include <Wire.h> // 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <BH1750.h>

//Manejo de I2C por direccionamiento
BH1750 luxometro(0x23); // Dirección para sensor de Luz

LiquidCrystal_I2C lcd(0x27,16,2);//Inicializa pantalla LCD con modulo I2C

//Declaración de variables
int SENSOR = 2; //Inicializa entero PIN D2
float temp;
int humedad, Humedad_Suelo, lux; // Iniciailiza variables tipo entero de temperatura y humedad
int pinOut_3 = 3; //inicializa variable de salida PIN D3 BOMBA DE AGUA
int pinOut_4 = 4; //Inicializa variable de salida PIN D4 Bombilla de luz
int pinOut_5 = 5; //Inicializa variable de salida PIN D5 Bomba

DHT dht (SENSOR, DHT22);
BH1750 sensor;

void setup() {
    Serial.begin(9600); //Velocidad de comunicación serial

    
    lcd.backlight();    //Inicialización luz de fondo LCD
    lcd.init();
    pinMode (pinOut_3, OUTPUT);
    pinMode (pinOut_4, OUTPUT);

    sensor.begin();
    Wire.begin();
    dht.begin();
}

void loop(){
  humedad = dht.readHumidity(); //humedad del sensor
  temp = dht.readTemperature(); //Temperatura del sensor
  Humedad_Suelo = analogRead(A0); //Humedad de suelo SENSOR 109
  lux = sensor.readLightLevel(); //Luminosidad del sensor BH1750


//DH22 Sensor de temperatura y humedad ambiente
  Serial.print("Temperatura: "); //Monitor
  Serial.print(temp);
  Serial.println("ºC");
  Serial.print("Humedad: ");//Monitor
  Serial.print(humedad);
  Serial.println("%");
  
//DH072 sensor capacitivo de humedad
  Serial.print("Humedad Suelo: ");
  Serial.println(Humedad_Suelo); //Toma de datos del sensor capacitivo
  
//BH1750 sensor de luminosidad 
  Serial.print(" Luminosidad: ");
  Serial.print(lux);
  Serial.println(" Lux ");

  
const int SECO = 590; // Valor para seco sensor (Valor 1) de 0% +-5%
const int HUMEDO = 318; // Valor para Mojado sensor (Valor) 2 de 100% +-5%


//Acople de porcentaje a sensor de humedad de suelo
int Porcentaje_Humedad_Suelo= map(Humedad_Suelo, HUMEDO, SECO, 100, 0);
  Serial.print("Porcentaje de Humedad Suelo: "); //Monitor
  Serial.println(Porcentaje_Humedad_Suelo);

  
//CONDICIONALES  
if (temp > 21 && temp < 24){              //Condicional para activar salida de bomba de agua
    digitalWrite(pinOut_3, LOW);
  }
  else {
    digitalWrite(pinOut_3, HIGH);
  }
if (lux > 200 && lux < 800){              //Condicional para activar salida de LUZ
    digitalWrite(pinOut_4, LOW);
  }
  else {
    digitalWrite(pinOut_4, HIGH);
  }
    
  if (Humedad_Suelo > 400 && Humedad_Suelo < 490){              //Condicional para activar salida de Bomba
    digitalWrite(pinOut_5, LOW);
  }
  else {
    digitalWrite(pinOut_5, HIGH);
  }
  
  // COnfiguración de pantalla LCD
  lcd.begin(16, 2); 
  lcd.setCursor(0,0); 
  //LCD impresion temperatura DHT 22
  lcd.print("T:"); 
  lcd.setCursor(2,0); 
  lcd.print(temp);
  lcd.setCursor(7,0); 
  lcd.print(" C");
  //LCD impresion de luminosidad
  lcd.setCursor(10,0);
  lcd.print("L: ");
  lcd.setCursor(12,0);
  lcd.print(lux);
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
  lcd.setCursor(15,1); 
  lcd.print("%");
  delay(200);
}
