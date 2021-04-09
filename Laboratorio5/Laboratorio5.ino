#include <SD.h>
#include <SPI.h>


File directorio;
String archivos[10];

uint8_t contador = 0; //guarda el numero de archivos que se encuentran 

void verArchivos(File);
void menu();

void setup() {
  Serial.begin(115200);//iniciar la comunicacion serial 
  SPI.setModule(0); //uso del modulo spi 
  Serial.print("Inicializando tarjeta SD...");
  
  if (!SD.begin(PA_3)) {
    Serial.println("Fallo al inicializar");
    return;
  }
  Serial.println("initialization done.");

  directorio = SD.open("/");
  verArchivos(directorio);

  
  
}

void loop() {
  menu();
  
}

void menu(){
  int opcion;
  while(true){ //mientras no se seleccione una opcion valida no se sale
     Serial.println("Seleccione una opcion para visualizar:");
    for(int i = 0; i<contador; i++){
      Serial.print(i+1);
      Serial.print(") ");
      Serial.println(archivos[i]);
    }
    while(! (Serial.available()>0));// esperar a que se envie algo por el serial
    String entrada = "";
    while(Serial.available()>0){
      char caracter = Serial.read();
      if(caracter !='\n') entrada.concat(caracter);
      else break; 
    }
    opcion = entrada.toInt();
    if(opcion==0){
        Serial.println("Opcion no valida");
        continue;
      }else{
        char ruta[50];
        archivos[opc
        ion-1].toCharArray(ruta,50);
        Serial.println(ruta);
        File abrir = SD.open(ruta);

       if(abrir){
        while(abrir.available())Serial.write(abrir.read());
        Serial.println();
       }
       else {
          Serial.println("opcion no valida");
          continue;
       }
        abrir.close();
      }

    
  }
 
}

void verArchivos(File directorio,){
  while(true) { //bucle sigue hasta que se de la condicion de salida 
     File entrada =  directorio.openNextFile();
     if (!entrada || contador>=10) break; // si ya no hay nada mas o se lleno el buffer de archivos

     if (!entrada.isDirectory()  && contador<10){
        archivos[contador] = entrada.name();
        contador++; 
     }
     entrada.close();
   }
}
