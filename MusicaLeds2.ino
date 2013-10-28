
int branco = 13;
int verde = 6;
int vermelho = 9;

int botaoBranco = 2;
int botaoVerde = 0;
int botaoVermelho = 1;

int estadoBranco = HIGH;
int estadoVerde = HIGH;
int estadoVermelho = HIGH;

int delayLeds = 200;

int level = 0;
int ultimoLevel = 0;
int musica[100];

void setup() {                
  pinMode(vermelho, OUTPUT);
  pinMode(verde, OUTPUT);   
  pinMode(branco, OUTPUT); 
  
  /*pinMode(botaoBranco, INPUT);
  pinMode(botaoVerde, INPUT);
  pinMode(botaoVermelho, INPUT); 
  */
}

void acendeLed(int porta) {
  digitalWrite(porta, HIGH);
  delay(delayLeds);
  digitalWrite(porta, LOW);
  delay(delayLeds);
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
    if (nota == 0) acendeLed(branco);
    else if (nota == 1) acendeLed(vermelho);
    else if (nota == 2) acendeLed(verde);
  }
}

void toca(int numeroNotas){
  ultimoLevel = level;
  level = numeroNotas;
  musicaRandomica();
  tocaMusica();
}

void pegaEstadoBotoes() {
  estadoBranco = analogRead(botaoBranco);
  estadoVerde = analogRead(botaoVerde);
  estadoVermelho = analogRead(botaoVermelho);
}

boolean acertou(int teclasCorretas) {
  return (teclasCorretas == level);  
}

int verificarBotoesPressionadosPeloUsuarioNoMomento(){
  while (true){
    pegaEstadoBotoes();
    if (estadoBranco > 500){
      acendeLed(branco);
      return 0;    
    }
    if (estadoVermelho > 500){
      acendeLed(vermelho);
      return 1;
    }
    if (estadoVerde > 500){
      acendeLed(verde);
      return 2;
    }
  }
}

void loop() {
  int i = 0;
  while(true){
    toca(++i);
    int teclasCorretas = 0;
    while (!acertou(teclasCorretas)) {
      int botao = verificarBotoesPressionadosPeloUsuarioNoMomento();
      if (musica[teclasCorretas] == botao){
        teclasCorretas++;
      }
      else{
        acendeLed(verde);
        acendeLed(verde);
        acendeLed(verde);
        while(true);
      }
    }
  }

}
