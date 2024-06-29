#define pir A4
 
void setup()
{
  pinMode(pir, INPUT); // pone el PIN DEL SENSOR COMO ENTRADA
  Serial.begin(9600); 
}

void loop()
{ 
  int pir_sensor=digitalRead(pir);
  
  if(pir_sensor==HIGH)
  {
    Serial.println("detección de movimiento");
  }

  delay(1000);
}
