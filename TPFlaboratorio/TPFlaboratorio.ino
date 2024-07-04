#include <DHT.h>
#include <DHT_U.h> 
//#include <OneWire.h>
#include <Keypad.h>
#include <LiquidCrystal.h> 

#include <math.h> 

#define PIN_PIR A4

//FUNCION HASH: f(x) = (ax+b) % n
//f(1234) = 3707
int SECRETO = 3707;
bool validarClave(int code) {
  Serial.print("validarClave, fx = ");
  int a = 3;
  int b = 5;
  int n = 10000;
  int fx = (a*code + b) % n;
  Serial.println(fx);
  return fx == SECRETO;
}
bool ACTIVE = false;

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
bool ALARMA;

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
  Serial.println("(*) para ingresar clave | finaliza con (#)");

}

void loop() {
  //ILUMINACION
  V = analogRead(PIN_LDR);
  delay(100);
  //ILUMINACION = ((long)(1024-V)*A*10)/((long)B*Rc*V);  //usar si LDR entre GND y A3 
  ILUMINACION = ((long)V*A*10)/((long)B*Rc*(1024-V));    //usar si LDR entre A0 y Vcc (como en el esquema anterior)
  
  //PIR
  pir_sensor = digitalRead(PIN_PIR);
  if(pir_sensor==HIGH) { //si se detecta movimiento
    
    if(ACTIVE==1) { // si la Alarma de incendio esta activada, suena la sirena. y desactiva la alarma
      Serial.println("movimiento con alarma ");
	  
      //Sonido
      for(contador=0,frecuencia=2000;contador<3;contador++) {
        tone(PIN_AUDIO,frecuencia); 
        delay(600); // centisegundos
        noTone(PIN_AUDIO);
        delay(10);
      }
      ACTIVE=!ACTIVE;
    }
    else{
      Serial.println("movimiento sin alarma");
    }
  }

  //KEYPAD
  char key = keypad.getKey();
  char number;
  String code = "";
  delay(1000);
  if(key == '*'){
    lcd.setCursor(0, 0);
    lcd.print("INGRESE CLAVE"); 
    lcd.setCursor(0, 1);

    Serial.println("*** INGRESE CLAVE ***");
    do {
      number = keypad.getKey();
      Serial.print(number);
      if(number!= NO_KEY && number !='#') {
        code += number;
      }
    } while (number != '#'); // != '#');
    Serial.println(""); 
    Serial.print("El codigo ingresado es: ");
    Serial.println(code);

    if (validarClave(code.toInt())){
      ACTIVE = true;
      Serial.println("Clave OK. Alarma activada");
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    LFYA TPF    "); 
  };

  //SENSOR DHT
  TEMPERATURA = dht.readTemperature();
  HUMEDAD = dht.readHumidity();
  Serial.print("Temperatura ");
  Serial.print(TEMPERATURA);
  Serial.print("oC - Humedad ");
  Serial.print(HUMEDAD);
  Serial.println("%");
  delay(100);

  lcd.setCursor(0, 1);
  if (TEMPERATURA == 50) {
    lcd.print(" INCENDIO. ALARMA  ");
    ACTIVE=true;                     //activar Alarma de incendio
  } else if (TEMPERATURA > 25) {
    lcd.print("   VENTILADOR   ");
  } else if (TEMPERATURA < 18) {
    lcd.print(" CALEFACCION ON ");
  } else {
    lcd.print("     NORMAL     ");
  }

}