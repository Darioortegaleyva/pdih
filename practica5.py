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
