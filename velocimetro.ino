#include <Wire.h>
#include <LiquidTWI.h>

    struct Sensor{
        int trig;
        int echo;
    };
    
    float dist_obj(int trig,int echo)
    {
      float dista=0;
      //ao enviar o pulso eh necessario passagem de corrente, o pino fica em modo de saida para isso
      pinMode(trig,OUTPUT);
      digitalWrite(trig,LOW);
      delayMicroseconds(2);
      digitalWrite(trig,HIGH);
      delayMicroseconds(10);
      digitalWrite(trig,LOW);
      //pulso enviado, volta a modo de entrada para ler o resultado
      pinMode(trig,INPUT);
      pinMode(echo,INPUT);
      dista=pulseIn(echo,HIGH,37000);
      //espera o fim do pulso de retorno que eh HIGH e que serah LOW.
      //Se passar de 37000uS, ele retorna como zero, pois passou dos 3m de precisao do sonar, e quase nos 38ms limites do pulso.
      //multiplica por 1/29[cm/us] e divide por 2 o tempo, pois este contem a ida e volta da onda.
      //------>o periodo recomendado eh de 50ms, foi utilizado 37ms, serah necessario colocar uma pausa?
      dista=(dista/29)/2;          
      return dista;                 
    };

    
    float medir(struct Sensor a){
       float b = dist_obj(a.trig,a.echo); 
      return b;
    };
#define ESPACO 15
#define PERTO  30
Sensor ultra[2]={{22,24},{26,28}};
LiquidTWI lcd(0);
int dist[2], sensorAtivo=1;
float tempo;
bool emCurso=false;


void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}



void loop() {
  // put your main code here, to run repeatedly:
  dist[0] = 0;
for(int i =0; i<10; i++){
    dist[0] += medir(ultra[0]);
}
  dist[0] /=10.0;

dist[1] = 0;
for(int i =0; i<10; i++){
    dist[1] += medir(ultra[1]);
}
  dist[1] /=10.0;

switch(sensorAtivo){
case 1:
if(dist[1]<PERTO){
    sensorAtivo = 2;
    if(emCurso){
        // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
        lcd.setCursor(0, 1);
        // print the number of seconds since reset:   
        lcd.clear();
        lcd.print(3.6*ESPACO*1.0/(((millis() - tempo))/1000));
        lcd.setBacklight(HIGH);
        delay(3000);
        emCurso = false; 
    }else{
      lcd.begin(16, 2);
      // Print a message to the LCD.
      tempo = millis();
      emCurso = true;
    }
}
  
break;
case 2:

if(dist[0]<PERTO){
    sensorAtivo = 1;
    if(emCurso){
        // set the cursor to column 0, line 1
        // (note: line 1 is the second row, since counting begins with 0):
        lcd.setCursor(0, 1);
        // print the number of seconds since reset:   
        lcd.clear();
        lcd.print(3.6*ESPACO*1.0/(((millis() - tempo))/1000));
        lcd.setBacklight(HIGH);
        delay(3000);
        emCurso = false; 
    }else{
      lcd.begin(16, 2);
      // Print a message to the LCD.
      tempo = millis();
      emCurso = true;
    }
}

break;
} 






}
