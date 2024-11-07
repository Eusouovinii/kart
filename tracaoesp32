#include <ESP32Servo.h>
#include <BluetoothSerial.h>

static const int motorTracao = 25;
static const int posicaoPin = 26;
static const int servoPin = 4;
unsigned int velocidadePWM = 0;
unsigned int posicao = 500;
int caseNumber = 0;
int lastcaseNumber = 0;

String device_name = "ESP32-BT-Slave";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled.
#endif

Servo myServo;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  Serial.println("Upload feito com sucesso");
  SerialBT.begin(device_name);  // Nome que o ESP32 usará no Bluetooth
  Serial.println("Bluetooth iniciado. Aguardando conexão...");
  myServo.attach(servoPin);

  myServo.write(120);
  delay(15);
}

void loop() {
  if (SerialBT.connected()) {
    if (SerialBT.available() >= 3) {
      velocidadePWM = SerialBT.read();
      caseNumber = SerialBT.read();
      posicao = SerialBT.read();

      Serial.print("Recebido velocidadePWM: ");
      Serial.println(velocidadePWM);
      Serial.print("Recebido posição: ");
      Serial.println(posicao);


      // Controla o servofreio
    }

    dacWrite(motorTracao, velocidadePWM);
    dacWrite(posicaoPin, posicao);

    switch (caseNumber) {
      case 1:
        if (lastcaseNumber != 1) {
          myServo.write(0);  // Move para 0 graus
          Serial.println("Movendo servo para 0 graus.");
          lastcaseNumber = 1;
          delay(500);
        }
        break;

      case 2:
        if (lastcaseNumber != 2) {
          myServo.write(90);  // Move para 90 graus
          Serial.println("Movendo servo para 90 graus.");
          lastcaseNumber = 2;
          delay(500);
        }
        break;

      case 3:
        if (lastcaseNumber != 3) {
          myServo.write(120);  // Move para 120 graus
          Serial.println("Movendo servo para 120 graus.");
          lastcaseNumber = 3;
          delay(500);
        }
        break;

      default:
        Serial.println("Valor inválido. Digite 1, 2 ou 3.");
        break;
    }
  } else {
    Serial.println("Aguardando conexão Bluetooth...");
  }
}
