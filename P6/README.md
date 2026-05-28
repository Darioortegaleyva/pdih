# Práctica 6: Reconocimiento de Imágenes con OpenCV

**Autores:** Inés Prados y Darío Ortega  
**Asignatura:** Periféricos y Dispositivos de Interfaz Humana (PDIH)

---

## 1. Introducción
El objetivo principal de esta práctica es comprender el funcionamiento de las técnicas de visión artificial y reconocimiento de imágenes. Hemos utilizado la librería **OpenCV** en Python junto con clasificadores en cascada basados en características de Haar (*Haar Cascades*) para detectar rostros humanos, cuerpos y caras de animales tanto en imágenes estáticas como en flujos de vídeo.

---

## 2. Desarrollo de la Práctica

### Ejercicio 1: Detección de caras en imágenes estáticas
Se ha implementado un script (`ejercicio1.py`) que lee una imagen, la convierte a escala de grises (requisito de OpenCV para optimizar el procesamiento) y utiliza el modelo `haarcascade_frontalface_default.xml` para encuadrar los rostros detectados.

**Resultado:**
![Ejercicio 1 - Caras](img/foto1.jpeg)

---

### Ejercicio 2: Detección de caras en vídeo
En el script `ejercicio2.py` hemos aplicado la misma lógica del ejercicio anterior, pero iterando sobre cada fotograma de un archivo de vídeo (`v2.mp4`) para lograr una detección en tiempo real. 

**Resultados y Análisis:**
En la primera captura observamos una detección perfecta de ambos sujetos:
![Ejercicio 2 - Detección Correcta](img/foto2.jpeg)

*Curiosidad (Falsos Positivos):* En esta segunda captura documentamos un **falso positivo** detectado por la IA. Esto es un comportamiento normal y esperado en los modelos Haar Cascade, ya que el algoritmo puede confundir ciertas agrupaciones de píxeles, sombras o geometrías del fondo con los patrones matemáticos de un rostro humano.
![Ejercicio 2 - Falso Positivo](img/foto3.jpeg)

---

### Ejercicio 3: Detección de gatos
Para este ejercicio (`ejercicio3.py`) se ha sustituido el modelo facial humano por el clasificador `haarcascade_frontalcatface_extended.xml`. Se ha aplicado sobre una imagen estática con gatos, dibujando los recuadros delimitadores correspondientes.

**Resultado:**
![Ejercicio 3 - Gatos](img/foto4.jpeg)

---

### Ejercicio 4: Detección simultánea de cuerpos y caras
El script final (`ejercicio4.py`) supone el mayor reto, ya que carga dos modelos de IA en memoria simultáneamente (`frontalface` y `fullbody`) y procesa el mismo fotograma de vídeo dos veces para encontrar ambas entidades.

**Resultados y Análisis:**
A continuación se muestran tres capturas del funcionamiento del vídeo:

1. En esta captura se aprecian algunos **falsos positivos** al intentar encuadrar los cuerpos, demostrando de nuevo el margen de error del modelo ante siluetas imprecisas:
![Ejercicio 4 - Falsos Positivos](img/foto5.jpeg)

2. Detección normal en curso durante el vídeo:
![Ejercicio 4 - Detección Normal](img/foto6.jpeg)

3. *Curiosidad (Detección de caricaturas):* Un comportamiento muy interesante del modelo ocurre en esta captura. El algoritmo detecta el logotipo del canal de YouTube (Model Pranksters) como si fuera una cara real. Aunque es un dibujo, sus proporciones geométricas (dos ojos y una boca dentro de un contorno circular) cumplen matemáticamente con los requisitos del modelo Haar Cascade para clasificarlo como rostro.
![Ejercicio 4 - Detección del Logo](img/foto7.jpeg)

---
