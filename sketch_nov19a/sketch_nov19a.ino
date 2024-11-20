#include <Servo.h>

#define TRIG 9
#define ECHO 10
#define RED 5
#define YELLOW 6
#define GREEN 7

Servo myServo;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  myServo.attach(3); // Pin del servomotor
  myServo.write(90); // Posición inicial
  Serial.begin(9600);
}

void loop() {
  // Medición de distancia
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long duration = pulseIn(ECHO, HIGH);
  int distance = duration * 0.034 / 2;

  // Enviar la distancia al navegador
  Serial.print("D:"); // Etiqueta para identificar datos de distancia
  Serial.println(distance);

  // Procesar comandos seriales
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    // Control de LEDs
    if (command == "R") {
      digitalWrite(RED, HIGH);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, LOW);
    } else if (command == "Y") {
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, HIGH);
      digitalWrite(GREEN, LOW);
    } else if (command == "G") {
      digitalWrite(RED, LOW);
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, HIGH);
    }

    // Control del servomotor
    if (command.startsWith("S:")) {
      int angle = command.substring(2).toInt();
      if (angle >= 0 && angle <= 180) {
        myServo.write(angle);
      }
    }
  }

  delay(10); // Actualización cada 500ms
}
