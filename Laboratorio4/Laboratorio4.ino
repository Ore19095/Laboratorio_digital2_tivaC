
/*
  Angel Orellana
  Laboratorio 4
*/

#define delayTime 10 //tiempo de delay 
// puertos virtuales xd

//variables para el control de boton de inicio de semaforo
int botonAntirrebote[] = {1,1}; // posicion 0, valor anterior posicion 1 valor actual.
int botonEstable[] = {1,1}; // posicion 0 valor anterior, posicion 1 valor actual
unsigned long timePUSH2 = 0;
int botonAntirrebote2[] = {1,1}; // posicion 0, valor anterior posicion 1 valor actual.
int botonEstable2[] = {1,1}; // posicion 0 valor anterior, posicion 1 valor actual
unsigned long timePUSH1 = 0;

int start = 0; // si es 0 no esta la carrera iniciada y si es 1 la carrera inicio
//variables para el control del boton del valor del J1
#define J1  PD_0
int portJ1[] = { PB_5, PB_0, PB_1, PE_4, PE_5, PB_4, PA_5 , PA_6, PA_7  };
int J1Antirrebote[] = {1,1}; // posicion 0, anterior, posicion 1 actual
int J1Estable[] = {1,1}; // igual que arriba
unsigned long timeJ1 = 0;
int valorJ1 = 9;
// variables para el control del boton del valor del J1
#define J2 PD_1
int portJ2[] = {PD_2, PD_3, PE_1, PE_2, PE_3, PB_2, PE_0, PA_4, PA_3 };
int J2Antirrebote[] = {1,1}; //posicion 0 valor anterior, posicion 1 actual
int J2Estable[] = {1,1}; //igual que arriba
unsigned long timeJ2 = 0;
int valorJ2 = 2;

void semaforo();
void carreraJ1(int);
void carreraJ2(int);
void carrera();

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(PUSH2, INPUT_PULLUP); //sw2 como pull up.
  pinMode(PUSH1, INPUT_PULLUP); //sw2 como pull up.
  pinMode(J1, INPUT_PULLUP); //sw2 como pull up.
  pinMode(J2, INPUT_PULLUP); //sw2 como pull up.
  
  for(int i = 0; i<9 ; i++){
    pinMode(portJ1[i], OUTPUT);
    pinMode(portJ2[i], OUTPUT);
  }
}

void loop() {
    //se leen los valores de los botones
    botonAntirrebote[0] = botonAntirrebote[1];
    botonAntirrebote[1] = digitalRead(PUSH2);
    botonAntirrebote2[0] = botonAntirrebote2[1];
    botonAntirrebote2[1] = digitalRead(PUSH1);
   
    // se actualiza el tiempo de espera si existe un cambio en el valor
    if(botonAntirrebote[0] != botonAntirrebote[1]) timePUSH2 = millis();
    if(botonAntirrebote2[0] != botonAntirrebote2[1]) timePUSH1 = millis();
    
    // si se mantiente estable por un tiempo mayor a delay time se actualizan los valores en estado estable 
    if(millis() - timePUSH2 > delayTime){
        botonEstable[0] = botonEstable[1];
        botonEstable[1] = botonAntirrebote[1];
      }
    if(millis() - timePUSH1 > delayTime){
        botonEstable2[0] = botonEstable2[1];
        botonEstable2[1] = botonAntirrebote2[1];
      }

    if( ( (botonEstable[1] != botonEstable[0]) && botonEstable[1] == 1) || ( (botonEstable2[1] != botonEstable2[0]) && botonEstable2[1] == 1) ){
      semaforo();
      valorJ1 = valorJ2 = 0;



      
      while(valorJ1<8 && valorJ2<8){
           carrera();
      }
    }


    //digital Write(portJ1[0], 1);
} 


void semaforo(){
  digitalWrite(GREEN_LED,LOW);
  digitalWrite(RED_LED,HIGH); //rojo
  delay(500);
  digitalWrite(GREEN_LED,HIGH); //amrillo
  delay(500);
  digitalWrite(RED_LED,LOW); // verde
  delay(500);
}


void carreraJ1(int valor){
   
   for(int i = 0; i < 9; i++) digitalWrite(portJ1[i], i==valor);
   
}


void carreraJ2(int valores){
   
   for(int i = 0; i < 9; i++) digitalWrite(portJ2[i], i==valores);
   
}


void carrera(){
   J1Antirrebote[0] = J1Antirrebote[1];
    J1Antirrebote[1] = digitalRead(J1);
    J2Antirrebote[0] = J2Antirrebote[1];
    J2Antirrebote[1] = digitalRead(J2);

    if(J1Antirrebote[0] != J1Antirrebote[1]) timeJ1 = millis();
    if(J2Antirrebote[0] != J2Antirrebote[1]) timeJ2 = millis();


    if(millis() - timeJ1 > delayTime){
      J1Estable[0] = J1Estable[1];
      J1Estable[1]= J1Antirrebote[1];
    }
    if(millis() - timeJ2 > delayTime){
      J2Estable[0] = J2Estable[1];
      J2Estable[1]= J2Antirrebote[1];
    }

    if(( J1Estable[1] != J1Estable[0]) &&  J1Estable[1]==1){
             valorJ1++;
      
    }

    if(( J2Estable[1] != J2Estable[0]) &&  J2Estable[1]==1){
           valorJ2++;
    }
    
    carreraJ1(valorJ1);
    carreraJ2(valorJ2);
}
