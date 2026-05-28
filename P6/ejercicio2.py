import cv2

modeloCara = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
camara = cv2.VideoCapture('v2.mp4') # Cambia el nombre del vídeo si es necesario

while camara.isOpened():
    ret, img = camara.read()
    if not ret: 
        break # Si se acaba el vídeo, salimos

    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    faces = modeloCara.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=4)

    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x,y), (x+w, y+h), (255, 0, 0), 3)

    cv2.imshow('Ejercicio 2 - Caras en Video', img)
    
    # Pulsar 'ESC' (código 27) para salir a la mitad
    if cv2.waitKey(1) == 27:
        break

camara.release()
cv2.destroyAllWindows()
