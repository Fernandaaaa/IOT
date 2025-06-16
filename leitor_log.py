import serial
import time

PORTA_SERIAL = 'COM7' 
BAUD_RATE = 9600

print("Iniciando monitoramento do Dispenser...")
print(f"Tentando conectar na porta {PORTA_SERIAL} a {BAUD_RATE} bps...")

try:
    arduino = serial.Serial(port=PORTA_SERIAL, baudrate=BAUD_RATE, timeout=2)
    time.sleep(2)
    print("Conexão estabelecida. Ouvindo os logs...")
    print("-" * 40)

    while True:
        linha_de_log = arduino.readline()
        if linha_de_log:
            log_limpo = linha_de_log.decode('utf-8').strip()
            print(f"Arduino diz: {log_limpo}")

except serial.SerialException as e:
    print(f"\nERRO: Não foi possível abrir a porta serial '{PORTA_SERIAL}'.")
    print("Verifique os seguintes pontos:")
    print("1. O Arduino está conectado ao USB?")
    print("2. A porta serial no script está correta?")
    print("3. O Monitor Serial da Arduino IDE está fechado?")
    print(f"Detalhe do erro: {e}")

except KeyboardInterrupt:
    print("\n\nMonitoramento interrompido. Fechando conexão.")

finally:
    if 'arduino' in locals() and arduino.is_open:
        arduino.close()
        print("Conexão serial fechada.")