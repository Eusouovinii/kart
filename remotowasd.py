import serial
import time
import keyboard  # Certifique-se de instalar a biblioteca keyboard com 'pip install keyboard'sssw

ser = serial.Serial('COM10', 115200)
numero1 = 0
numero2 = 1
numero3 = 600  # Valor base para numero3

while True:
    try:
        # Verifica as teclas pressionadas e atualiza os valores de numero1, numero2 e numero3
        if keyboard.is_pressed('w'):
            numero1 = 120
        else:
            numero1 = 0

        if keyboard.is_pressed('s'):
            numero2 = 1
        else:
            numero2 = 3

        if keyboard.is_pressed('d'):
            numero3 = min(850, numero3 + 50)  # Limita numero3 a 255 para evitar overflow
            time.sleep(0.1)  # Pequena pausa para evitar múltiplas detecções rápidas
        if keyboard.is_pressed('a'):
            numero3 = max(350, numero3 - 50)  # Limita numero3 a 0 para evitar valores negativos
            time.sleep(0.1)  # Pequena pausa para evitar múltiplas detecções rápidas


        # Enviar os dados como bytes
        ser.write(bytes([numero1, numero2, (int(numero3/4))]))  # Enviando os 3 números como bytes
        time.sleep(0.05)

        print(f"Números enviados: {numero1}, {numero2}, {numero3}")

    except ValueError:
        print("Por favor, insira um valor válido.")
    except KeyboardInterrupt:
        print("Programa interrompido pelo usuário.")
        break

ser.close()
