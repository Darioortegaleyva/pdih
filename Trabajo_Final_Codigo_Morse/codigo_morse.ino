// --- Configuración de Pines ---
const int pinLed = 13;
const int pinBuzzer = 8;
const int pinBoton = 2;

// --- Tiempos ---
const int umbralPunto = 250;
const int tiempoFinLetra = 1000;

// --- Diccionario Completo (A-Z y 0-9) ---
const int TOTAL_CARACTERES = 36;
char letras[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};
String morse[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
  "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
  "-----", ".---", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."
};

String bufferMorse = "";
unsigned long tiempoInicio = 0;
bool pulsando = false;
unsigned long ultimoCambio = 0;

void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinBoton, INPUT); 
  Serial.begin(9600);
  Serial.println(">>> SISTEMA MORSE PDIH LISTO <<<");
  Serial.println("Escribe una palabra en el PC para que Arduino la emita...");
}

// ================= FUNCIONES DE EMISIÓN (Arduino -> Clase) =================

void emitirSimbolo(int duracion) {
  digitalWrite(pinLed, HIGH);
  tone(pinBuzzer, 1000);
  delay(duracion);
  digitalWrite(pinLed, LOW);
  noTone(pinBuzzer);
  delay(200); // Espacio entre puntos/rayas
}

void emitirPalabra(String palabra) {
  palabra.toUpperCase();
  Serial.print("Emitiendo acertijo... ");
  
  for (int i = 0; i < palabra.length(); i++) {
    char c = palabra[i];
    for (int j = 0; j < TOTAL_CARACTERES; j++) {
      if (c == letras[j]) {
        String codigo = morse[j];
        for (int k = 0; k < codigo.length(); k++) {
          if (codigo[k] == '.') emitirSimbolo(200);
          else emitirSimbolo(600);
        }
        delay(600); // Espacio entre letras
        break;
      }
    }
  }
  Serial.println("¡Hecho! ¿Alguien sabe que era?");
}

// ================= BUCLE PRINCIPAL =================

void loop() {
  // --- PARTE 1: Escuchar el PC (Modo Acertijo) ---
  if (Serial.available() > 0) {
    String entrada = Serial.readStringUntil('\n');
    entrada.trim();
    if (entrada.length() > 0) {
      emitirPalabra(entrada);
    }
  }

  // --- PARTE 2: Escuchar el Botón (Modo Práctica) ---
  int estado = digitalRead(pinBoton);

  if (estado == HIGH && !pulsando) {
    pulsando = true;
    tiempoInicio = millis();
    digitalWrite(pinLed, HIGH);
    tone(pinBuzzer, 1000);
  }

  if (estado == LOW && pulsando) {
    pulsando = false;
    digitalWrite(pinLed, LOW);
    noTone(pinBuzzer);
    
    unsigned long duracion = millis() - tiempoInicio;
    if (duracion > 50) {
      bufferMorse += (duracion < umbralPunto) ? "." : "-";
      Serial.print(bufferMorse.substring(bufferMorse.length()-1));
    }
    ultimoCambio = millis();
  }

  // Detectar fin de letra del usuario
  if (estado == LOW && bufferMorse != "" && (millis() - ultimoCambio > tiempoFinLetra)) {
    for (int i = 0; i < TOTAL_CARACTERES; i++) {
      if (bufferMorse == morse[i]) {
        Serial.print(" -> ");
        Serial.println(letras[i]);
        break;
      }
    }
    bufferMorse = "";
  }
}
