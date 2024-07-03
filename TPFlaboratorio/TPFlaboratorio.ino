#include <DHT.h>
#include <DHT_U.h> 
//#include <OneWire.h>
#include <Keypad.h>
#include <LiquidCrystal.h> 

#define PIN_PIR A4

//SENSOR LUZ (ILUMINACION)
const int PIN_LDR = A0;
int ILUMINACION;
const long A = 1000;     //Resistencia en oscuridad en KΩ
const int B = 15;        //Resistencia a la luz (10 Lux) en KΩ
const int Rc = 10;       //Resistencia calibracion en KΩ
int V;

//SENSOR DTH (TEMPERATURA)
int PIN_DHT = A5;
int TEMPERATURA;
int HUMEDAD;
DHT dht(PIN_DHT, DHT11);	// dht(PIN, TYPE) - OBJETO

//SENSOR PIR (MOVIMIENTO)
int pir_sensor;

//ACTUADOR LUZ
int PIN_LED = 12;

//ACTUADOR AUDIO
int PIN_AUDIO = 13;
int frecuencia = 220; 
int contador; 
float m = 1.059; // multiplicador de frecuencias

//ACTUADOR DISPLAY LCD
LiquidCrystal lcd(11, 0, A1, A2, 10, 9); //lcd(RS, E, D4, D5, D6, D7) - OBJETO

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
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //OBJETO

void setup() {
  //INICIALIZO
  Serial.begin(115200); //9600
  Serial.println("Inicializando...");
  lcd.begin(16, 2); //   void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);
  Serial.println("LCD listo.");
  lcd.print("    LFYA TPF    "); 
  dht.begin(); 
  Serial.println("DHT listo.");
  pinMode(PIN_LED, OUTPUT); // PIN DEL SENSOR LED COMO SALIDA
  Serial.println("LED listo.");
  pinMode(PIN_PIR, INPUT); // PIN DEL SENSOR PIR COMO ENTRADA
  Serial.println("PIR listo.");
}

void loop() {
  //ILUMINACION
  V = analogRead(PIN_LDR);
  delay(1000);
  //ILUMINACION = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //usar si LDR entre GND y A3 
  ILUMINACION = ((long)V*A*10)/((long)B*Rc*(1024-V));    //usar si LDR entre A0 y Vcc (como en el esquema anterior)
  Serial.print("ILUMINACION: ");
  Serial.print(ILUMINACION);
  Serial.print(" V: ");
  Serial.println(V);
  
  //PIR
  pir_sensor = digitalRead(PIN_PIR);
  
  if(pir_sensor == HIGH) {
    Serial.print("movimiento");
  }

  //KEYPAD
  char key = keypad.getKey();
  delay(100);

  //SENSOR DHT
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  Serial.print("Temperatura ");
  Serial.print(TEMPERATURA);
  Serial.print("oC - Humedad ");
  Serial.print(HUMEDAD);
  Serial.println("%");
  delay(500);

  lcd.setCursor(0, 1);
  if (TEMPERATURA == 50) {
    lcd.print("    INCENDIO    ");
  } else if (TEMPERATURA > 25) {
    lcd.print("   VENTILADOR   ");
  } else if (TEMPERATURA < 18) {
    lcd.print(" CALEFACCION ON ");
  } else {
    lcd.print("     NORMAL     ");
  }

  if(key){
    switch (key) {
      case '1':
          Serial.println("> 1");
        break;
      
      case '2':
        Serial.println("> 2");

        break;

      case '3':
        Serial.println("> 3");

        break;

      case '4':
        Serial.println("> 4");

        break;

      case '5':
        Serial.println("> 5");

        break;

      case '6':
        Serial.println("> 6");

        break;

      case '7':
        Serial.println("> 7");

        break;

      case '8':
        Serial.println("> 8");

        break;

      case '9':
        Serial.println("> 9");

        break;

      case '*':
        tone(PIN_AUDIO,frecuencia); 
        delay(500);
        noTone(PIN_AUDIO);
        break;

      case '#':
        analogWrite(PIN_LED, 255); //ENCIENDE
        delay(500);
        analogWrite(PIN_LED, 0); //APAGA
        break;
    }
  };

  //Sonido
    //for(contador=0,frecuencia=220;contador<12;contador++) {
    //  frecuencia *= m; 
    //  tone(PIN_AUDIO,frecuencia); 
    //  delay(500); // centisegundos
    //  noTone(PIN_AUDIO);
    //  delay(100);
  //}


}
