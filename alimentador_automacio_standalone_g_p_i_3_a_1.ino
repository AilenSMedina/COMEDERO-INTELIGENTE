// Incluir la biblioteca para la pantalla LCD
#include <LiquidCrystal.h>
// Incluir la biblioteca para el servo motor
#include <Servo.h>

// Crear un objeto LCD y establecer los pines de Arduino para la LCD
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// Definir el pin para el botón de alimentación manual
int manualPin = 2;
// Estado inicial del botón de alimentación manual
int buttonState = 0;
// Definir el pin para el servo motor
int servoPin = 4;
// Definir el pin para el LED rojo
int ledVermelho = 3;
// Crear un objeto servo llamado Servo1
Servo Servo1;
// Definir el pin para el botón de horas
int horaPin = 5;
// Estado inicial del botón de horas
int estadoBotao = 0;
// Contador auxiliar
int i;
// Contador de la cantidad de presiones del botón
int qnt_press;
// Hora base inicial
int horaBase = 1;

// Contadores de tiempo
int S = 00; // Segundos
int M = 00; // Minutos
int H = horaBase; // Horas

void setup()
{
  // Configurar manualPin como entrada con resistencia pull-up incorporada
  pinMode(manualPin, INPUT_PULLUP);
  // Configurar horaPin como entrada con resistencia pull-up incorporada
  pinMode(horaPin, INPUT_PULLUP);

  // Adjuntar Servo1 al pin servoPin
  Servo1.attach(servoPin);
  // Configurar servoPin como salida
  pinMode(servoPin, OUTPUT);
  // Poner el servo motor en la posición de espera a máxima potencia
  Servo1.write(0);

  // Iniciar la pantalla LCD
  lcd.begin(16, 2);
  // Seleccionar la primera línea de la LCD
  lcd.setCursor(0, 0);
  // Imprimir mensaje en la LCD
  lcd.print("   Alimentador  ");
  // Seleccionar la segunda línea de la LCD
  lcd.setCursor(0, 1);
  // Imprimir mensaje en la LCD
  lcd.print("   Automatico  ");
  // Esperar 2 segundos
  delay(2000);
  // Limpiar la pantalla LCD
  lcd.clear();
  lcd.print("  De animales  ");
  delay(2000);
  lcd.setCursor(0, 1);
  lcd.print("Sistema listo :D");
  delay(2000);
  lcd.clear();
}

void loop()
{
  // Configurar el contador de cuenta regresiva
  lcd.setCursor(0, 0);
  lcd.print("Alimentando en :");
  lcd.setCursor(6, 1);
  lcd.print(":");
  lcd.setCursor(9, 1);
  lcd.print(":");

  // Ciclo para ajustar la hora base
  for (i = 0; i < 10; i++)
  {
    delay(100);
    estadoBotao = digitalRead(horaPin); // Leer el estado del botón de horas
    if (estadoBotao == LOW)
    {
      while (estadoBotao == LOW)
      {
        estadoBotao = digitalRead(horaPin);
      }
      horaBase++;
      H++;
    }
  }

  // Decrementar los segundos
  S--;

  // Declarar que el pin será usado como salida
  pinMode(ledVermelho, OUTPUT);

  // Ajustar los minutos y horas si los segundos llegan a 0
  if (S < 0)
  {
    M--;
    S = 59;
  }
  if (M < 0)
  {
    H--;
    M = 59;
  }
  if (H < 0) // Ajustar aquí la hora deseada
  {
    H = horaBase;
    M = 00;
    S = 00;
  }

  // Mostrar los minutos en la LCD
  if (M > 9)
  {
    lcd.setCursor(7, 1);
    lcd.print(M);
  }
  else
  {
    lcd.setCursor(7, 1);
    lcd.print("0");
    lcd.setCursor(8, 1);
    lcd.print(M);
    lcd.setCursor(9, 1);
    lcd.print(":");
  }

  // Mostrar los segundos en la LCD
  if (S > 9)
  {
    lcd.setCursor(10, 1);
    lcd.print(S);
  }
  else
  {
    lcd.setCursor(10, 1);
    lcd.print("0");
    lcd.setCursor(11, 1);
    lcd.print(S);
    lcd.setCursor(12, 1);
    lcd.print(" ");
  }

  // Mostrar las horas en la LCD
  if (H > 9)
  {
    lcd.setCursor(4, 1);
    lcd.print(H);
  }
  else
  {
    lcd.setCursor(4, 1);
    lcd.print("0");
    lcd.setCursor(5, 1);
    lcd.print(H);
    lcd.setCursor(6, 1);
    lcd.print(":");
  }

  // Si la cuenta regresiva llega a 0, alimentar
  if ((H == 0) && (M == 0) && (S == 0))
  {
    lcd.setCursor(0, 0);
    lcd.print("Tiempo Terminado");
    lcd.setCursor(0, 1);
    lcd.print("  Alimentando");
    Servo1.write(0); // Girar el servo a 0 grados para dispensar comida
    digitalWrite(ledVermelho, HIGH); // Encender el LED rojo
    delay(3000); // Ajustar la cantidad de comida a dispensar
    digitalWrite(ledVermelho, LOW); // Apagar el LED rojo
    Servo1.write(180); // Girar el servo a 180 grados para detener la dispensación de comida
    lcd.clear();
  }

  // Leer el estado del botón de alimentación manual
  buttonState = digitalRead(manualPin);

  // Si el botón de alimentación manual está presionado
  if (buttonState == LOW)
  {
    lcd.setCursor(0, 0);
    lcd.print("  Alimentacion  ");
    lcd.setCursor(0, 1);
    lcd.print("     Manual   ");
    digitalWrite(ledVermelho, HIGH); // Encender el LED rojo
    Servo1.write(90); // Girar el servo a 90 grados para dispensar comida
    delay(2000); // Ajustar la cantidad de comida a dispensar
    digitalWrite(ledVermelho, LOW); // Apagar el LED rojo
    Servo1.write(0); // Girar el servo a 0 grados para detener la dispensación de comida
    lcd.clear();
  }
}


