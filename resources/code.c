#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Dirección I2C puede necesitar ajuste

#define BUFFER_SIZE 5
#define BUZZER_PIN 8
#define LED_NORMAL_PIN 9    // Verde
#define LED_WARNING_PIN 10  // Amarillo
#define LED_CRITICAL_PIN 11 // Rojo

// Pines del sensor ultrasónico
#define TRIGGER_PIN 6
#define ECHO_PIN 7

// Pin del sensor de temperatura TMP86GZ
#define TEMP_SENSOR_PIN A0  

// Umbrales de distancia (cm)
#define THRESHOLD_CRITICAL 10  
#define THRESHOLD_WARNING  20  
#define THRESHOLD_CAUTION  30  

enum State {
  NORMAL,
  CAUTION,
  WARNING,
  CRITICAL
};

// Variables del sistema
State currentState = NORMAL;
int sensorBuffer[BUFFER_SIZE];
int bufferIndex = 0;
bool bufferFilled = false;

// Control del buzzer
unsigned long lastBuzzerToggle = 0;
unsigned long buzzerInterval = 0;
bool buzzerOn = false;
int buzzerIntensity = 0;

void setup() {
  Serial.begin(9600);
  
  // Inicializar pantalla LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Sistema Iniciado");

  // Configurar pines
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_NORMAL_PIN, OUTPUT);
  pinMode(LED_WARNING_PIN, OUTPUT);
  pinMode(LED_CRITICAL_PIN, OUTPUT);
  
  // Inicializar buffer
  for (int i = 0; i < BUFFER_SIZE; i++) {
    sensorBuffer[i] = 0;
  }

  delay(2000);  // Pequeña pausa para mostrar mensaje inicial
  lcd.clear();
}

void loop() {
  float distance = leerDistancia();
  sensorBuffer[bufferIndex] = distance;
  bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
  if (bufferIndex == 0) bufferFilled = true;
  
  float avgDistance = calcularPromedio();
  float temperatura = leerTemperatura(); // Obtener la temperatura

  // Determinar estado basado en la distancia
  if (avgDistance <= THRESHOLD_CRITICAL) {
    currentState = CRITICAL;
  } else if (avgDistance <= THRESHOLD_WARNING) {
    currentState = WARNING;
  } else if (avgDistance <= THRESHOLD_CAUTION) {
    currentState = CAUTION;
  } else {
    currentState = NORMAL;
  }

  // Actualizar LEDs y buzzer
  actualizarSalidas();
  controlarBuzzer();
  
  // Mostrar en la LCD sin borrar toda la pantalla
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(avgDistance);
  lcd.print(" cm  ");

  lcd.setCursor(0, 1);
  lcd.print("Est: ");
  switch (currentState) {
    case NORMAL:   lcd.print("NORM"); break;
    case CAUTION:  lcd.print("CAUTI"); break;
    case WARNING:  lcd.print("WARN"); break;
    case CRITICAL: lcd.print("CRIT"); break;
  }

  // Mostrar temperatura en la segunda línea
  lcd.setCursor(9, 1);
  lcd.print(temperatura);
  lcd.print("C ");

  // Imprimir en Serial
  Serial.print("Distancia: ");
  Serial.print(avgDistance);
  Serial.print("cm |Est:");
  imprimirEstado();
  Serial.print(" |Temp:");
  Serial.print(temperatura);
  Serial.println("C");

  delay(500);  // Reducido para mejorar la actualización de la LCD
}

float leerDistancia() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.0343 / 2;
  
  // Filtrar lecturas inválidas
  if (distance <= 0 || distance > 400) return 400;
  return distance;
}

float calcularPromedio() {
  int sum = 0;
  int count = bufferFilled ? BUFFER_SIZE : bufferIndex;
  if (count == 0) return 400;  // Valor por defecto si no hay lecturas
  for (int i = 0; i < count; i++) {
    sum += sensorBuffer[i];
  }
  return (float)sum / count;
}

// Función para leer temperatura del TMP86GZ
float leerTemperatura() {
  int valorAnalogico = analogRead(TEMP_SENSOR_PIN);
  float voltaje = valorAnalogico * (5.0 / 1023.0); // Convertir a voltaje
  float temperatura = (voltaje - 0.5) * 100.0;     // Fórmula de conversión
  return temperatura;
}

void actualizarSalidas() {
  // Apagar todos los LEDs
  digitalWrite(LED_NORMAL_PIN, LOW);
  digitalWrite(LED_WARNING_PIN, LOW);
  digitalWrite(LED_CRITICAL_PIN, LOW);

  // Configurar salidas según el estado
  switch(currentState) {
    case CRITICAL:
      digitalWrite(LED_CRITICAL_PIN, HIGH);
      buzzerInterval = 200;
      buzzerIntensity = 255;
      break;
      
    case WARNING:
      digitalWrite(LED_WARNING_PIN, HIGH);
      buzzerInterval = 500;
      buzzerIntensity = 128;
      break;
      
    case CAUTION:
      digitalWrite(LED_WARNING_PIN, HIGH);
      digitalWrite(LED_NORMAL_PIN, HIGH);
      buzzerInterval = 1000;
      buzzerIntensity = 64;
      break;
      
    default:
      digitalWrite(LED_NORMAL_PIN, HIGH);
      buzzerInterval = 0;
      buzzerIntensity = 0;
      break;
  }
}

void controlarBuzzer() {
  if (currentState == NORMAL || buzzerInterval == 0) {
    analogWrite(BUZZER_PIN, 0);
    return;
  }
  
  if (millis() - lastBuzzerToggle >= buzzerInterval) {
    lastBuzzerToggle = millis();
    buzzerOn = !buzzerOn;
    analogWrite(BUZZER_PIN, buzzerOn ? buzzerIntensity : 0);
  }
}

void imprimirEstado() {
  switch(currentState) {
    case NORMAL:
      Serial.print("NORM");
      break;
    case CAUTION:
      Serial.print("CAUT");
      break;
    case WARNING:
      Serial.print("WARN");
      break;
    case CRITICAL:
      Serial.print("CRIT");
      break;
  }
}
