#include <DHT.h>
#include <DHT_U.h> 

#include <OneWire.h>

#include <Keypad.h>
#include <LiquidCrystal.h> 
#define pir A4

//LUZ
const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ
int V;
int ilum;

//SENSOR DTH
int SENSOR = A5;
int TEMPERATURA;
int HUMEDAD;

//PIR
int pir_sensor;

//KEYPAD
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {8,7,6,5}; 
byte colPins[COLS] = {4,3,2}; 

int P;

//OBJETOS
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(11, 0, A1, A2, 10, 9); //lcd(RS, E, D4, D5, D6, D7)
DHT dht(SENSOR, DHT11);	

//PINS
int pinLed = 12;
const int LDRPin = A0;
const int PIRPin = A4;

int pinSpeaker = 13;
int frecuencia = 220; 
int contador; 
float m = 1.059; // multiplicador de frecuencias

void setup() {

  //INICIALIZO
  Serial.begin(115200);
  //Serial.begin(9600);	
  dht.begin(); 
  lcd.begin(16, 2); //   void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
  lcd.print("       TPF      "); 
  pinMode(pinLed, OUTPUT);
  pinMode(pir, INPUT); // pone el PIN DEL SENSOR COMO ENTRADA
}

void loop() {
  
  //SENSOR DHT
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  //luz
  V = analogRead(LDRPin);
  //PIR
  pir_sensor = digitalRead(pir);
  
  if(pir_sensor==HIGH) {
    Serial.print("movimiento");
  }


  //KEYPAD
  char key = keypad.getKey();
  delay(1000);

  //ilum = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //usar si LDR entre GND y A3 
  ilum = ((long)V*A*10)/((long)B*Rc*(1024-V));    //usar si LDR entre A0 y Vcc (como en el esquema anterior)
  Serial.println(ilum);
  delay(100);
  
//  if (TEMPERATURA || HUMEDAD){
  Serial.print("Temperatura: ");
  Serial.print(TEMPERATURA);
  Serial.print("oC");

  Serial.print(" Humedad: ");
  Serial.print(HUMEDAD);
  Serial.println("%");
  delay(500);
  //} 
  

  // lcd.setCursor(0, 1);
  
  // if(TEMPERATURA == 50) {
  //   lcd.print("    INCENDIO    ");
  // } 
  // if(TEMPERATURA > 25) {
  //   //lcd.setCursor(0, 1);
  //   lcd.print("   VENTILADOR   ");
  // } else {
  //     if (TEMPERATURA < 18 ) {
  //       //lcd.setCursor(0, 1);
  //       lcd.print(" CALEFACCION ON ");
  //       //lcd.clear();
  //     } else {
  //       lcd.print("     NORMAL     ");
  //     } 
  // }

  if(key){
    switch (key) {
      case '1':
        lcd.setCursor(0, 1); //fila del LCD  
        lcd.print("> 1");        
        break;
      
      case '2':
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("> 2");        
        break;

      case '3':
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("> 3");        
        break;

      case '4':
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("> 4");        
        break;

      case '5':
        lcd.setCursor(0, 0); // segunda fila del LCD  
        lcd.print("> 5");        
        break;

      case '6':
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("> 6");        
        break;

      case '7':
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("> 7");        
        break;

      case '8':
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("> 8");        
        break;

      case '9':
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("> 9");        
        break;

      case '*':
        lcd.setCursor(0, 0); // segunda fila del LCD  
        lcd.print("tecla:*");        
        analogWrite(pinLed, 255); //ENCIENDE
        tone(pinSpeaker,frecuencia); 
        delay(500); // centisegundos
        noTone(pinSpeaker);
        break;

      case '#':
        lcd.setCursor(0, 1);
        lcd.print("tecla:#"); 
        analogWrite(pinLed, 0); //APAGA
        break;
    }
  };

  //Sonido
    //for(contador=0,frecuencia=220;contador<12;contador++) {
    //  frecuencia *= m; 
    //  tone(pinSpeaker,frecuencia); 
    //  delay(500); // centisegundos
    //  noTone(pinSpeaker);
    //  delay(100);
  //}


}
