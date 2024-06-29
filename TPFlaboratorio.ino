#include <DHT.h>
#include <DHT_U.h> 

#include <OneWire.h>

#include <Keypad.h>
#include <LiquidCrystal.h> 

//SENSOR DTH
int SENSOR = A5;
int TEMPERATURA;
int HUMEDAD;

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

//OBJETOS
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(11, 0, A1, A2, 10, 9); //lcd(RS, E, D4, D5, D6, D7)
DHT dht(SENSOR, DHT11);	

//PINS
int pinLed = 12;
const int LDRPin = A0;

int pinSpeaker = 13;
int frecuencia = 220; 
int contador; 
float m = 1.059; // multiplicador de frecuencias



void setup() {

  //INICIALIZO
  //Serial.begin(115200);
  Serial.begin(9600);	
  dht.begin(); 
  lcd.begin(16, 2); //   void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
  lcd.print("TPF"); 
  pinMode(pinLed, OUTPUT);
}

void loop() {
  //SENSOR DHT
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  
//  if (TEMPERATURA || HUMEDAD){
  Serial.print("Temperatura: ");
  Serial.print(TEMPERATURA);
  Serial.print("oC");

  Serial.print(" Humedad: ");
  Serial.print(HUMEDAD);
  Serial.println("%");
  delay(500);
  //} 
  
  if(TEMPERATURA == 50) {
    //lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("    Incendio    ");
  } 
  if(TEMPERATURA > 25) {
    lcd.setCursor(0, 1);
    lcd.print("   Ventilador   ");
  } else if(TEMPERATURA < 18) {
    lcd.setCursor(0, 1);
    lcd.print(" CALEFACCION ON ");
  }

  //KEYPAD
  char key = keypad.getKey();
  if(key){
    switch (key) {
      case '1':
        lcd.setCursor(8, 0); //fila del LCD  
        lcd.print("> 1");        
        break;
      
      case '2':
        lcd.setCursor(8, 0); // segunda fila del LCD  
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
        lcd.setCursor(0, 1); // segunda fila del LCD  
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
        lcd.setCursor(0, 1); // segunda fila del LCD  
        lcd.print("tecla:*");        
        analogWrite(pinLed, 255); //ENCIENDE
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
