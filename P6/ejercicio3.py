import cv2
 
# Cargamos el modelo específico para gatos
modeloGato = cv2.CascadeClassifier('haarcascade_frontalcatface_extended.xml') 
 
# Cargamos la foto de los gatos que acabamos de copiar
img = cv2.imread('foto_gatos.jpg')
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# Buscamos los gatos
gatos = modeloGato.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=5)

# Dibujamos los rectángulos (en amarillo)
for (x, y, w, h) in gatos:
    cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 255), 3)
  
# Mostramos el resultado
cv2.imshow('Ejercicio 3 - Gatos', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
