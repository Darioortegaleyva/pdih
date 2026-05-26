import numpy as np
import matplotlib.pyplot as plt
from scipy.io import wavfile

frecuencia_n, datos_n = wavfile.read("nombre.wav")
frecuencia_a, datos_a = wavfile.read("apellido.wav")


plt.figure(figsize=(10, 4))
plt.plot(datos_n, color="blue")
plt.title("Forma de onda: Nombre")
plt.xlabel("Muestras")
plt.ylabel("Amplitud")
plt.grid(True)
plt.show()  


plt.figure(figsize=(10, 4))
plt.plot(datos_a, color="green")
plt.title("Forma de onda: Apellido")
plt.xlabel("Muestras")
plt.ylabel("Amplitud")
plt.grid(True)
plt.show()

# 3. Obtener la información de las cabeceras
print("=== INFORMACIÓN DE LAS CABECERAS ===")

print(f"--- Fichero: nombre.wav ---")
print(f"Frecuencia de muestreo (Sample Rate): {frecuencia_n} Hz")
print(f"Número total de muestras: {datos_n.shape[0]}")
print(f"Tipo de datos (Resolución): {datos_n.dtype}")
if len(datos_n.shape) == 1:
    print("Canales: 1 (Mono)")
else:
    print(f"Canales: {datos_n.shape[1]} (Estéreo)")

print("-" * 30)


print(f"--- Fichero: apellido.wav ---")
print(f"Frecuencia de muestreo (Sample Rate): {frecuencia_a} Hz")
print(f"Número total de muestras: {datos_a.shape[0]}")
print(f"Tipo de datos (Resolución): {datos_a.dtype}")
if len(datos_a.shape) == 1:
    print("Canales: 1 (Mono)")
else:
    print(f"Canales: {datos_a.shape[1]} (Estéreo)")
    
    
# 4. Unir ambos sonidos en uno nuevo
if frecuencia_n == frecuencia_a:
    datos_basico = np.concatenate((datos_n, datos_a))
    frecuencia_basico = frecuencia_n
    print("\n[OK] Sonidos unidos correctamente.")
else:
    print("\n[ALERTA] Los archivos tienen frecuencias de muestreo distintas. Se usará la del nombre.")
    datos_basico = np.concatenate((datos_n, datos_a))
    frecuencia_basico = frecuencia_n
    


# 5: Dibujar la forma de onda combinada y reproducir
print("\n=== EJERCICIO 5: DIBUJAR Y REPRODUCIR EL RESULTADO ===")


plt.figure(figsize=(10, 4))
plt.plot(datos_basico, color="purple")
plt.title("Forma de onda: Nombre y Apellido Unidos")
plt.xlabel("Muestras")
plt.ylabel("Amplitud")
plt.grid(True)
print("Mostrando gráfica del sonido unido... (Ciérrala para escuchar el audio)")
plt.show()  


import os

print("Reproduciendo el sonido combinado por los altavoces...")

wavfile.write("temp_combinado.wav", frecuencia_basico, datos_basico)


os.system("aplay temp_combinado.wav")


if os.path.exists("temp_combinado.wav"):
    os.remove("temp_combinado.wav")



# 6: Almacenar el sonido resultante de forma definitiva

print("\n=== EJERCICIO 6: ALMACENAR EL ARCHIVO ===")

# Guardamos el archivo final con el nombre exacto que exige la práctica
wavfile.write("basico.wav", frecuencia_basico, datos_basico)
print("[OK] ¡Archivo 'basico.wav' creado y guardado con éxito!")




# Ejercicio 7: Pasar un filtro de frecuencia (10.000 Hz - 20.000 Hz)

print("\n=== EJERCICIO 7: APLICANDO FILTRO DE FRECUENCIA ===")
from scipy.signal import butter, lfilter

def filtro_banda_eliminada(lowcut, highcut, fs, order=5):

    nyq = 0.5 * fs
    low = lowcut / nyq
    high = highcut / nyq
    # Si la frecuencia de audio es menor que el corte superior (20kHz), 
    # ajustamos el límite para que el filtro no falle
    if high >= 1.0:
        high = 0.99
    # 'bandstop' indica que queremos eliminar el rango intermedio
    b, a = butter(order, [low, high], btype='bandstop')
    return b, a

# Configuramos el filtro entre 10.000 y 20.000 Hz
b, a = filtro_banda_eliminada(10000, 20000, frecuencia_basico, order=5)


if len(datos_basico.shape) == 2:  
    datos_filtrado = np.zeros_like(datos_basico)
    datos_filtrado[:, 0] = lfilter(b, a, datos_basico[:, 0])
    datos_filtrado[:, 1] = lfilter(b, a, datos_basico[:, 1])
else:  
    datos_filtrado = lfilter(b, a, datos_basico)


datos_filtrado = datos_filtrado.astype(datos_basico.dtype)


wavfile.write("filtrado.wav", frecuencia_basico, datos_filtrado)
print("[OK] Archivo 'filtrado.wav' generado correctamente sin frecuencias altas.")



#8: Aplicar efecto de eco y darle la vuelta al sonido

print("\n=== EJERCICIO 8: EFECTO DE ECO Y REVERSA ===")


retraso_segundos = 0.3
muestras_retraso = int(frecuencia_basico * retraso_segundos)


datos_eco = np.zeros(len(datos_basico) + muestras_retraso, dtype=np.float32)


datos_eco[:len(datos_basico)] += datos_basico


datos_eco[muestras_retraso:] += datos_basico * 0.4


datos_eco = datos_eco.astype(datos_basico.dtype)


wavfile.write("eco.wav", frecuencia_basico, datos_eco)
print("[OK] Archivo 'eco.wav' generado con éxito.")



datos_alreves = datos_basico[::-1]


wavfile.write("alreves.wav", frecuencia_basico, datos_alreves)
print("[OK] Archivo 'alreves.wav' generado con éxito.")

print("\n¡Práctica completada al 100%! Revisa tu carpeta para ver todos los .wav creados.")



# COMPROBACIÓN EJERCICIOS 7 Y 8

print("\n=== COMPROBACIÓN DE REQUISITOS AMPLIADOS ===")


print("\n[Escuchando] Sonido FILTRADO (debería sonar más apagado o sin agudos)...")
os.system("aplay filtrado.wav")


_, datos_f = wavfile.read("filtrado.wav")


print("\n[Escuchando] Sonido con ECO (debería sonar la repetición)...")
os.system("aplay eco.wav")

_, datos_e = wavfile.read("eco.wav")


print("\n[Escuchando] Sonido AL REVÉS (¡tu nombre invertido!)...")
os.system("aplay alreves.wav")

_, datos_r = wavfile.read("alreves.wav")



print("\nMostrando gráficas de los efectos... (Ciérralas para terminar)")

fig, (ax1, ax2, ax3) = plt.subplots(3, 1, figsize=(10, 10))


ax1.plot(datos_f, color="orange")
ax1.set_title("Forma de onda: Señal Filtrada (10kHz - 20kHz)")
ax1.grid(True)


ax2.plot(datos_e, color="brown")
ax2.set_title("Forma de onda: Señal con Eco (0.3s delay)")
ax2.grid(True)


ax3.plot(datos_r, color="red")
ax3.set_title("Forma de onda: Señal Invertida (Al revés)")
ax3.grid(True)

plt.tight_layout()
plt.show()

print("\n¡Todo listo y comprobado!")
