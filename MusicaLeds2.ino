
int branco = 6;
int verde = 4;
int vermelho = 5;
int cores[] = {branco.verde.vermelho};

int buzz = 9;

int botaoBranco = 8;
int botaoVerde = 2;
int botaoVermelho = 7;

int estadoBranco = HIGH;
int estadoVerde = HIGH;
int estadoVermelho = HIGH;

int buzzBranco = 250;
int buzzVerde = 340;
int buzzVermelho = 500;
int buzzes[] = {buzzBranco,buzzVerde,buzzVermelho};

int delayLeds = 200;

int level = 0;
int ultimoLevel = 0;
int musica[100];

void setup() {
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);
  pinMode(branco, OUTPUT);
  
  pinMode(botaoBranco, INPUT);
  pinMode(botaoVerde, INPUT);
  pinMode(botaoVermelho, INPUT);
  
  pinMode(buzz, OUTPUT);

}

void acendeLed(int porta) {
  digitalWrite(porta, HIGH);
  delay(delayLeds);
  digitalWrite(porta, LOW);
  delay(delayLeds);
}

void acendeLedTime(int porta, int tempo) {
  digitalWrite(porta, HIGH);
  delay(tempo);
  digitalWrite(porta, LOW);
  delay(tempo);
}

void musicaRandomica(){
  int i;
  for (i=ultimoLevel;i<level;i++){
    musica[i] = random(0,3);
  }
}

void tocaMusica(){
  int i;
  for (i=0; i < level; i++){
    int nota = musica[i];
    tone(buzz,buzzes[nota]);
    acendeLed(cores[nota]);
    noTone(buzz);
  }
}

void toca(int numeroNotas){
  ultimoLevel = level;
  level = numeroNotas;
  musicaRandomica();
  tocaMusica();
}

void pegaEstadoBotoes() {
  estadoBranco = digitalRead(botaoBranco);
  estadoVerde = digitalRead(botaoVerde);
  estadoVermelho = digitalRead(botaoVermelho);
}

boolean acertou(int teclasCorretas) {
  return (teclasCorretas == level);
}

int verificarBotoesPressionadosPeloUsuarioNoMomento(){
  while (true){
    pegaEstadoBotoes();
    if (estadoBranco == HIGH){
      tone(buzz, buzzBranco);
      acendeLed(branco);
      noTone(buzz);
      return 0;
    }
    if (estadoVermelho == HIGH){
      tone(buzz, buzzVermelho);
      acendeLed(vermelho);
      noTone(buzz);
      return 1;
    }
    if (estadoVerde == HIGH){
      tone(buzz, buzzVerde);
      acendeLed(verde);
      noTone(buzz);
      return 2;
    }
  }
}

void endGame() {
  for (int i = 0; i < 5; i++) {
      tone(buzz, buzzVerde);
    acendeLedTime(verde, 80);
      noTone(buzz);
      tone(buzz, buzzVermelho);
    acendeLedTime(vermelho, 80);
      noTone(buzz);
      tone(buzz, buzzBranco);
    acendeLedTime(branco, 80);
      noTone(buzz);
      tone(buzz, buzzVermelho);
    acendeLedTime(vermelho, 80);
      noTone(buzz);
  }
}

void loop() {
  int i = 0;
  randomSeed(analogRead(0));
  while(true){
    delay(1000);
    toca(++i);
    int teclasCorretas = 0;
    while (!acertou(teclasCorretas)) {
      int botao = verificarBotoesPressionadosPeloUsuarioNoMomento();
      if (musica[teclasCorretas] == botao){
        teclasCorretas++;
      }
      else{
        endGame();
        delay(5000);
      }
    }
    
  }

}
