/**
   Versión 1 del juego 'Simon Dice' (Simon Says).
   El armado consta de:
   x4 leds con sus correspondientes resistencias de 220 ohms conectados a los pines del 6 al 9.
   x4 pulsadores con sus correspondientes resistencias de 100 ohms conectados a los pines del 2 al 5.
   x1 buzzer pasivo conectado al pin 11.

   Una posible versión 2 podría incluir:
   - Sonidos al presionar los pulsadores y reproducir la secuencia.
   - Algún tipo de display para mostrar el nivel alcanzado.

   El esquema completo de conexiones junto con el resto de la información puede encontrarse en:
   https://thenerdyapprentice.blogspot.com/

    The Nerdy Apprentice* --> Si te gustó este proyecto visita el blog y deja un comentario, gracias!
*/

// Definimos las constantes de los botones, leds y buzzer
const byte PB_1 = 5;
const byte PB_2 = 4;
const byte PB_3 = 3;
const byte PB_4 = 2;
const byte Led_1 = 6;
const byte Led_2 = 7;
const byte Led_3 = 8;
const byte Led_4 = 9;
const byte Buzz = 11;

const int CantidadNiveles = 32; // Definimos la cantidad máxima de niveles
int Secuencia[CantidadNiveles]; // Array donde se guarda la secuencia
int SecuenciaU[CantidadNiveles]; // Array donde se guarda la secuencia del usuario
const int Delay_S = 600; // Delay de prendido y apagado de los leds durante la secuencia
int Nivel = 0; // Variable que guardará el nivel durante el juego

void setup() {
  Serial.begin(9600); // Iniciamos el puerto Serie

  // Definimos las entradas y salidas...
  for (int i = 6; i <= 9; i++) { // de los Leds
    pinMode(i, OUTPUT);
  }
  for (int i = 2; i <= 5; i++) { // de los pulsadores
    pinMode(i, INPUT);
  }
  pinMode(Buzz, OUTPUT); // del buzzer

  Nivel = 0;
  ApagarLeds(); // Llamamos a la función que apaga los leds
  GenerarSecuencia(); // llamamos a la función que genera la secuencia aleatoria para los niveles
  Flash(); // Llamamos a la función que genera la secuencia de Leds de inicio
}

void loop() {

  Serial.print("Nivel:");
  Serial.println(Nivel);
  MostrarSecuencia(); // Función que muestra la secuencia generada aleatoriamente
  LeerEntrada(); // Función que lee el input del jugador
  
}

void LeerEntrada() {
  bool flag = true; // Flag que nos permitirá controlar el input del usuario

  for (int i = 0; i <= Nivel; i++) {

    flag = true;

    // Durante el WHILE leemos que pulsador se presionó, encendemos el led correspondiente y comparamos el input con la secuencia mostrada.
    while (flag == true) {
      if (digitalRead(PB_1) == HIGH) {
        digitalWrite(Led_1, HIGH);
        while (digitalRead(PB_1) == HIGH); // Utilizamos el While para detener la ejecución mientras se mantenga pulsado, sirve para evitar los rebotes del botón.
        digitalWrite(Led_1, LOW);
        SecuenciaU[i] = 6; // Hacemos coincidir el led con el pulsador presionado, asi podremos comprobar si es correcto o no.
        flag = false;
        delay(Delay_S);
        Serial.print("Botón Presionado:");
        Serial.println(SecuenciaU[i]);
        Serial.print("Secuencia:");
        Serial.println(Secuencia[i]);
        if (SecuenciaU[i] != Secuencia[i]) { // Si el input del jugador no coincide con la secuencia mostrada llamamos a la función SecuenciaError();
          //Serial.println(SecuenciaU[i]);
          //Serial.println(Secuencia[i]);
          SecuenciaError();
          return;
        }

      }

      if (digitalRead(PB_2) == HIGH) {
        digitalWrite(Led_2, HIGH);
        while (digitalRead(PB_2) == HIGH);
        digitalWrite(Led_2, LOW);
        SecuenciaU[i] = 7;
        flag = false;
        delay(Delay_S);
        Serial.print("Botón Presionado:");
        Serial.println(SecuenciaU[i]);
        Serial.print("Secuencia:");
        Serial.println(Secuencia[i]);
        if (SecuenciaU[i] != Secuencia[i]) {
          //Serial.println(SecuenciaU[i]);
          //Serial.println(Secuencia[i]);
          SecuenciaError();
          return;
        }

      }

      if (digitalRead(PB_3) == HIGH) {
        digitalWrite(Led_3, HIGH);
        while (digitalRead(PB_3) == HIGH);
        digitalWrite(Led_3, LOW);
        SecuenciaU[i] = 8;
        flag = false;
        delay(Delay_S);
        Serial.print("Botón Presionado:");
        Serial.println(SecuenciaU[i]);
        Serial.print("Secuencia:");
        Serial.println(Secuencia[i]);
        if (SecuenciaU[i] != Secuencia[i]) {
          //Serial.println(SecuenciaU[i]);
          //Serial.println(Secuencia[i]);
          SecuenciaError();
          return;
        }

      }

      if (digitalRead(PB_4) == HIGH) {
        digitalWrite(Led_4, HIGH);
        while (digitalRead(PB_4) == HIGH);
        digitalWrite(Led_4, LOW);
        SecuenciaU[i] = 9;
        flag = false;
        delay(Delay_S);
        Serial.print("Botón Presionado:");
        Serial.println(SecuenciaU[i]);
        Serial.print("Secuencia:");
        Serial.println(Secuencia[i]);
        if (SecuenciaU[i] != Secuencia[i]) {
          //Serial.println(SecuenciaU[i]);
          //Serial.println(Secuencia[i]);
          SecuenciaError();
          return;
        }

      }

    } // Fin del While

  } // Fin del For

  //delay(100);

  // Si coincide el input del usuario con la secuencia mostrada llamamos a la función SecuenciaCorrecta()
  SecuenciaCorrecta();
}

void SecuenciaError() {
  Serial.println("Secuencia Incorrecta");
  Game_Over(); // Llamamos a la función que genera la melodía.
  Nivel = 0; // Reiniciamos el nivel.

  // Hacemos un delay largo y llamamos nuevamente a la función Flash() indicando que el juego vuelve a empezar.
  delay(800);
  Flash();

  GenerarSecuencia(); // Generamos otra secuencia.
}

void SecuenciaCorrecta() {
  Nivel++; // Aumentamos de nivel
  Serial.println("Secuencia Correcta");
}


void MostrarSecuencia() { // Muestra la secuencia usando como variable Nivel (que vamos aumentando a medida que el usuario va ganando)
  for (int x = 0; x <= Nivel; x++) {
    //Serial.println(Nivel);
    digitalWrite(Secuencia[x], HIGH);
    delay(Delay_S);
    digitalWrite(Secuencia[x], LOW);
    delay(Delay_S);
  }

  //delay(100); // Pequeño delay después de mostrar la secuencia para evitar errores.

}

void GenerarSecuencia() { // Función que genera la secuencia
  randomSeed(analogRead(0)); // Iniciamos la semilla random que servirá para generar aleatoriamente la secuencia, utilizamos el pin A0 que no está conectado a nada.
  for (int x = 0; x <= CantidadNiveles; x++) { // Llenamos el array con números entre 6 y 9 (correspondientes a los leds)
    Secuencia[x] = random(6, 10);
  }

}

void ApagarLeds() {
  for (int i = 6; i <= 10; i++) {
    digitalWrite(i, LOW);
    delay(100);
  }
}

void Flash() {
  for (int i = 6; i <= 9; i++) {
    digitalWrite(i, HIGH);
    delay(100);
  }

  for (int i = 6; i <= 9; i++) {
    digitalWrite(i, LOW);
    delay(100);
  }

  for (int i = 6; i <= 9; i++) {
    digitalWrite(i, HIGH);
    delay(100);
  }

  for (int i = 6; i <= 9; i++) {
    digitalWrite(i, LOW);
    delay(100);
  }

  delay(1500);
}

void Game_Over() {

  Flash_E(); // Llamamos a la función que hace parpadear los leds, que junto a la melodía indica que le usuario perdió.

  int melodia[] = {
    262, 196, 196, 220, 196, 0, 247, 262
  };

  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };

  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(Buzz, melodia[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(Buzz);
  }

}

void Flash_E() {
  digitalWrite(Led_1, HIGH);
  digitalWrite(Led_2, HIGH);
  digitalWrite(Led_3, HIGH);
  digitalWrite(Led_4, HIGH);

  delay(300);
  digitalWrite(Led_1, LOW);
  digitalWrite(Led_2, LOW);
  digitalWrite(Led_3, LOW);
  digitalWrite(Led_4, LOW);
  delay(300);
  digitalWrite(Led_1, HIGH);
  digitalWrite(Led_2, HIGH);
  digitalWrite(Led_3, HIGH);
  digitalWrite(Led_4, HIGH);

  delay(300);
  digitalWrite(Led_1, LOW);
  digitalWrite(Led_2, LOW);
  digitalWrite(Led_3, LOW);
  digitalWrite(Led_4, LOW);
  delay(100);

}
