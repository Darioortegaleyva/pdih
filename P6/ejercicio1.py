import cv2

# 1. Cargamos el clasificador de caras frontal
modelo = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')

# 2. Cargamos la imagen y la pasamos a blanco y negro (OpenCV lo requiere para detectar)
img = cv2.imread('imagen_input.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# 3. Detectamos las caras
rostros = modelo.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)

# 4. Dibujamos los rectángulos
for (x, y, w, h) in rostros:
    cv2.rectangle(img, (x, y), (x+w, y+h), (0, 0, 255), 3)

# 5. Mostramos el resultado
cv2.imshow('Ejercicio 1 - Caras en Imagen', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
