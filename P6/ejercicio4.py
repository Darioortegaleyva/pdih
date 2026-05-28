import cv2

# Cargamos ambos modelos (Recuerda descargar el de fullbody)
modeloCara = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
modeloCuerpo = cv2.CascadeClassifier('haarcascade_fullbody.xml')

camara = cv2.VideoCapture('v4.mp4') # Vídeo donde salga gente de cuerpo entero

while camara.isOpened():
    ret, img = camara.read()
    if not ret: 
        break
        
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 1. Detectar y dibujar cuerpos (en verde)
    cuerpos = modeloCuerpo.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=3)
    for (x, y, w, h) in cuerpos:
        cv2.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), 3)

    # 2. Detectar y dibujar caras (en azul)
    caras = modeloCara.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=4)
    for (x, y, w, h) in caras:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 3)

    cv2.imshow('Ejercicio 4 - Cuerpos y Caras', img)
    if cv2.waitKey(1) == 27:
        break

camara.release()
cv2.destroyAllWindows()
