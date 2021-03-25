#include <SD.h>
#include <SPI.h>


File directorio;
String archivos[10];

uint8_t contador = 0; //guarda el numero de archivos que se encuentran 

void verArchivos(File);


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

  
}



void verArchivos(File directorio){
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
