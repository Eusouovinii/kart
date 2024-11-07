#define setpointPin A0  // Potenciômetro de setpoint
#define feedbackPin A1  // Potenciômetro de feedback
#define rpwmPin 9       // Pino RPWM (direção 1)
#define lpwmPin 10      // Pino LPWM (direção 2)

// Constantes de banda morta e compensação
int deadzonePWM = 100;         // Valor mínimo de PWM para garantir torque
int minError = 30;             // Erro mínimo para aplicar controle
float compensationFactor = 2;  // Fator de compensação para a direção mais lenta

void setup() {
  Serial.begin(9600);

  // Configura os pinos como saída
  pinMode(rpwmPin, OUTPUT);
  pinMode(lpwmPin, OUTPUT);
}

void loop() {
  int setpoint = analogRead(setpointPin);                // Posição desejada
  int setpointMapeado = map(setpoint, 0, 675, 0, 1023);  // Mapeia para a faixa de 0 a 1023
  delay(15);

  int feedback = analogRead(feedbackPin);  // Posição atual do motor
  int error = setpointMapeado - feedback;  // Diferença entre a posição desejada e a atual

  int motorSpeed = map(abs(error), 0, 1023, deadzonePWM, 255);  // Converte o erro para PWM, sempre maior que a banda morta

  // Controle da direção
  if (abs(error) < minError) {
    // Se o erro for muito pequeno, para o motor
    analogWrite(rpwmPin, 0);
    analogWrite(lpwmPin, 0);
  } else {
    if (error > 0) {
      // Compensa para a direção mais lenta
      analogWrite(rpwmPin, motorSpeed);
      analogWrite(lpwmPin, 0);
    } else {
      // Aplica a compensação para a direção mais lenta
      int compensatedSpeed = motorSpeed * compensationFactor;  // Aplica fator de compensação
      if (compensatedSpeed > 255) compensatedSpeed = 255;      // Limita o valor máximo a 255
      analogWrite(rpwmPin, 0);
      analogWrite(lpwmPin, compensatedSpeed);
    }
  }


  // Debug via serial
  Serial.print("Setpoint: ");
  Serial.print(setpointMapeado);
  Serial.print("\tFeedback: ");
  Serial.print(feedback);
  Serial.print("\tErro: ");
  Serial.print(error);
  Serial.print("\tMotor Speed: ");
  Serial.println(motorSpeed);
}
