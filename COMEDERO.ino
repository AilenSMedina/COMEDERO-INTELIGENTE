#include <Servo.h>

const int buttonPin = 2;   // Pin digital 2 para el botón
const int sensorPin = 3;   // Pin digital 3 para el pin de señal del sensor de ultrasonido
const int servoPin = 9;    // Pin digital 9 para el servo

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  myServo.attach(servoPin);
  myServo.write(0); // Posición inicial del servo
}

void loop() {
  int buttonState = digitalRead(buttonPin);
  long duration, distance;

  // Enviar pulso de inicio al sensor de ultrasonido
  pinMode(sensorPin, OUTPUT);
  digitalWrite(sensorPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorPin, LOW);

  // Cambiar el pin a modo de entrada para leer el tiempo de eco
  pinMode(sensorPin, INPUT);
  duration = pulseIn(sensorPin, HIGH);

  // Calcular la distancia en centímetros
  distance = (duration / 2) / 29.1;

  // Filtrar valores incorrectos
  if (distance > 0 && distance < 400) { // Suponiendo que el sensor tiene un rango máximo de 400 cm
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Si el botón está presionado o un objeto está a menos de 20 cm
    if (buttonState == HIGH || distance < 20) {
      Serial.println("Dispensando Comida");
      myServo.write(90); // Girar servo para dispensar comida
      delay(1000);       // Esperar 1 segundo
      myServo.write(0);  // Volver a la posición inicial
      delay(5000);       // Esperar 5 segundos antes de verificar nuevamente
    }
  } else {
    Serial.println("error de calculo de dsitancia");
  }

  delay(1000); // Esperar 1 segundo antes de la siguiente lectura
}
