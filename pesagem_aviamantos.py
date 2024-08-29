import serial
import time
import pandas as pd

# Configuração da porta serial
ser = serial.Serial('COM5', 9600)  
time.sleep(2)

# Inicializar DataFrame para armazenar os dados
df = pd.DataFrame(columns=['Peso', 'Data/Hora'])

while True:
    if ser.in_waiting > 0:
        peso = ser.readline().decode('utf-8').strip()
        if peso:  # Verifica se o peso foi lido corretamente
            print(f"Peso lido: {peso} g")
            timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
            df = df.append({'Peso': float(peso), 'Data/Hora': timestamp}, ignore_index=True)
            df.to_excel('pesagem.xlsx', index=False)  # Salva os dados no Excel
    time.sleep(1)