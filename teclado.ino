int portas[] = {2,3,4,5,6};

 //329.63/ 
float doh = 1915;
float re = 1700;
float mi = 1519;
float fa = 1432;
float sol = 1275;

float notas[] = {doh,re,mi,fa,sol};

int tamanho = 5;

int estados[5];

int buzz = 9;

void setup() {
  int i;
  for (i = 0; i < tamanho; i++){
   pinMode(portas[i],INPUT); 
  }
  pinMode(buzz, OUTPUT);
}

void pegaEstadoBotoes() {
  int i;
  for (i = 0; i < tamanho; i++){
    estados[i] = digitalRead(portas[i]);
  }
}

void playTone(float nota, int duration) {
  for (long i = 0; i < duration * 1000L; i += nota * 2) {
    digitalWrite(buzz, HIGH);
    delayMicroseconds(nota);
    digitalWrite(buzz, LOW);
    delayMicroseconds(nota);
  }
}


void playNote(int duration) {
  // play the tone corresponding to the note name
  for (int i = 0; i < tamanho; i++) {
    if (estados[i] == HIGH) {
      playTone(notas[i], duration);
    }
  }
}

int verificarBotoesPressionadosPeloUsuarioNoMomento(){
  pegaEstadoBotoes();
  playNote(1);
}

void loop() {
    verificarBotoesPressionadosPeloUsuarioNoMomento();
  }
