#include "NXTIoT_dev.h"

NXTIoT_dev  mysigfox;

/*Variables Globales para utilizar
el botón de la tarjeta*/
  const int boton=6;
  const int sensorPin = A0;

void setup() 
{
  Serial.begin(9600); //Comunicación serial con la tarjeta
  pinMode(boton, INPUT); 
}

void leer_temperatura()
{
  int sensorVal=analogRead(sensorPin); //Variable local que almacena el dato del sensor.
  float voltaje=(sensorVal/1024.0)*5; //Variable local para definir el voltaje.
  Serial.print("Voltaje: ");         //toda función 'Serial.print' imprime en monitor serie.
  Serial.println(voltaje);          //Imprime la variable voltaje.
  Serial.print("Grados Cº: ");
  float temp=((voltaje)*100);     //Calcula la temperatura a partir del voltaje.
  Serial.println(temp);          //Imprime la variable temperatura.

//Envía el mensaje a Sigfox:
  mysigfox.initpayload();
  mysigfox.addfloat(temp);
  mysigfox.sendmessage();
}

//Función 'principal'. Blucle infinito.
void loop() 
{
  if (digitalRead(boton)==LOW) //Espera a que se cumpla la condición (Botón presionado).
  {
    leer_temperatura();       //Accede a la función anterior
    delay(1000);
  } 
}
