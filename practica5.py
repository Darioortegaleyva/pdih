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
