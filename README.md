# Informe del Trabajo de Laboratorio Final

**Autores:** Bonserio Julia, Duarte Rodrigo Ivan, Mendoza Marcelo Daniel, Scholz Veronica  
**Materia:** Lenguajes Formales y Autómatas  
**Universidad:** Universidad Nacional Arturo Jauretche  

## Resumen

Este informe detalla el desarrollo de un sistema de control simulado que automatiza varios aspectos del hogar utilizando sensores, actuadores y un autómata para controlarlos. Se presenta una descripción del diseño e implementación del sistema en un entorno simulado utilizando el simulador Proteus y un microcontrolador Arduino Uno. Los resultados obtenidos, las dificultades encontradas durante el desarrollo y las conclusiones de la implementación se exponen al final del documento.

**Palabras clave:** domótica, Arduino, Proteus

## Descripción del Proyecto

En este trabajo de laboratorio, se diseñó e implementó un sistema de automatización del hogar que incluye el control de la iluminación, una alarma de movimiento y la regulación de temperatura. Los sensores y actuadores fueron integrados utilizando el simulador Proteus y un microcontrolador Arduino Uno. Se desarrollaron diagramas de estados utilizando un autómata de Moore para controlar el comportamiento de los actuadores en función de las lecturas de los sensores.

### Componentes Utilizados

- **Arduino Uno:** Microcontrolador que gestiona los componentes del sistema.
- **Sensores:**
  - Sensor de luz (LDR)
  - Sensor de temperatura y humedad (DHT11)
  - Sensor de movimiento (PIR)
- **Actuadores:**
  - Luz LED
  - Parlante (sirena)
  - Visor LCD
  - Teclado numérico
  - Monitor serie para depuración

### Diseño y Implementación

El proyecto se desarrolló en varias fases:

1. **Implementación en Proteus:** Se diseñó el circuito con los componentes electrónicos en el simulador.
2. **Programación en Arduino IDE:** Se desarrolló el código para gestionar los sensores y actuadores de acuerdo con un autómata de Mealy.
3. **Interfaz de Usuario:** La interacción con el sistema se facilitó mediante un teclado para la activación de la alarma y un visor LCD para la visualización en tiempo real de los estados del sistema.

![imagen de proteus](https://github.com/team-bestia/TPF_lab/blob/main/arduino.png)

### Resultados

El sistema fue exitoso al automatizar tareas domésticas esenciales:

- **Iluminación:** Se activó la luz LED cuando los niveles de luz fueron inferiores a 100 lux.
- **Control de Temperatura:** El sistema gestionó la calefacción y la ventilación según las condiciones de temperatura.
- **Seguridad:** La sirena se activó ante un aumento crítico de temperatura o la detección de movimiento con la alarma activada.
- **Interfaz:** Se implementaron elementos para facilitar la interacción, como el teclado y la pantalla LCD.

## Cómo Ejecutar el Proyecto

1. **Requisitos:**  
   - Arduino IDE  
   - Simulador Proteus  
   - Componentes de hardware (si se desea implementar de manera física)
2. **Instrucciones:**
   - Conectar el Arduino Uno y los componentes según el diagrama de conexiones.
   - Cargar el código desde Arduino IDE.
   - Abrir el simulador Proteus y verificar el funcionamiento del sistema.

## Conclusiones

El proyecto permitió aplicar los conocimientos de Lenguajes Formales y Autómatas, desarrollando un sistema domótico eficiente y funcional. Se evidenció la importancia de los diagramas de estados para la estructuración del sistema y el control de los dispositivos.
