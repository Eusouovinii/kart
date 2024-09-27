#define feedbackPin A1     // Potenciômetro de feedback (posição real do motor)
#define rpwmPin 9          // Pino RPWM (direção 1)
#define lpwmPin 10         // Pino LPWM (direção 2)
#define renPin 5           // Pino para habilitar R_EN
#define lenPin 6           // Pino para habilitar L_EN

const int targetAngle = 512; // Ângulo desejado (ajuste conforme necessário)
const float Kp = 1.0;        // Ganho proporcional (ajuste conforme necessário)

void setup() {
  Serial.begin(9600);
  
  // Configura os pinos como saída
  pinMode(rpwmPin, OUTPUT);
  pinMode(lpwmPin, OUTPUT);
  pinMode(renPin, OUTPUT);
  pinMode(lenPin, OUTPUT);

  // Habilita ambos os lados
  digitalWrite(renPin, HIGH);  
  digitalWrite(lenPin, HIGH);
}

void loop() {
  int feedback = analogRead(feedbackPin); // Posição atual do motor
  int error = targetAngle - feedback;     // Diferença entre a posição desejada e a atual
  
  int motorSpeed = abs(error) * Kp;       // Aplicar ganho proporcional ao erro

  // Limitar a velocidade máxima a 255 (PWM máximo)
  if (motorSpeed > 255) {
    motorSpeed = 255;
  }

  if (error > 0) {
    // Gira o motor para uma direção
    analogWrite(rpwmPin, motorSpeed);
    analogWrite(lpwmPin, 0);
  } else if (error < 0) {
    // Gira o motor na direção oposta
    analogWrite(rpwmPin, 0);
    analogWrite(lpwmPin, motorSpeed);
  } else {
    // Para o motor
    analogWrite(rpwmPin, 0);
    analogWrite(lpwmPin, 0);
  }

  // Exibe os valores no serial monitor para depuração
  Serial.print("Target Angle: ");
  Serial.print(targetAngle);
  Serial.print("\tFeedback: ");
  Serial.print(feedback);
  Serial.print("\tError: ");
  Serial.println(error);
  
  delay(15);
}
