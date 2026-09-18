#include <Arduino.h>
//hola chisitos son

//La espada va al display 1
//Arco va al display 2
//El bife de chirizo va al display 3
//La Lana va al display 4
//El Escudo va al display 5

String Cereal = "";
unsigned long manuelito;
int accionesDisponibleHermano = 1;
bool empiezalobueno = true;
int vidaDelMalditoYHorribleWarden = 200;
int Sucri = 20; //es la vida por si revisan este codigo, gorda
bool DiplaSelct(int eseeseldisplayqueestaseleccionado)//<-- hermanochi creo que ese explica solo
{
  // <-- ponelo ato
  return false;
}
void setup()
{
  Serial.begin(9600);
  manuelito = millis();
  pinMode(13, INPUT);
}

void loop() 
{
  //saca esta basura
  if (Serial.available() > 0)
  {
    Cereal = Serial.readStringUntil('\n');
    Cereal.trim();
  }
  //hasta aca :V
  if (accionesDisponibleHermano != 0)
{
  if (DiplaSelct(1) || Cereal == "espada")
  {
    vidaDelMalditoYHorribleWarden -= 25;
    accionesDisponibleHermano--;
    Cereal = "";
  }
  if (DiplaSelct(2) || Cereal == "arcu")
  {
    vidaDelMalditoYHorribleWarden -= QuickEventJuanitoTech()? 50 : 0;
    Cereal = "";
    accionesDisponibleHermano--;
    //use la misma mrd xd
  }
  if (DiplaSelct(3) || Cereal == "cereal")
  {
    Sucri += 3;
    accionesDisponibleHermano--;
    Cereal = "";
  }
  if (DiplaSelct(4) || Cereal == "meee")
  {
    accionesDisponibleHermano = 2;
    Cereal = "";
  }
}else
  {
    if (empiezalobueno)
    {
    empiezalobueno = false;
    Sucri -= QuickEventJuanitoTech()? 0 : 6; //re tryhard xddddd
    accionesDisponibleHermano = 1;
    empiezalobueno = true;
    }
  }
}

bool QuickEventJuanitoTech()
{
  delay(100);
  manuelito = millis();
  unsigned long ttts = millis();
  manuelito = map(manuelito, 0, 1000, 0, 400) / 2;
  float granChisitos = random(150, 250);
  int jaimito = -1;
  Cereal = "";
  while (jaimito == -1){
  unsigned long manuelito2 = millis() - ttts;
  // mas cosa pa debugear :V
    if (Serial.available() > 0)
  {
    Cereal = Serial.readStringUntil('\n');
    Cereal.trim();
  }
  //sacalo hasta aca
  manuelito2 = map(manuelito2, 0, 1000, 0, 400) / 2;
  if ((digitalRead(13) == LOW && DiplaSelct(5)) || Cereal == "0")
  {
    if (manuelito2 > granChisitos - 15 && manuelito2 < granChisitos + 15)
    {
      jaimito = 1; 
    }else{
      jaimito = 0;
    }
    Cereal = "";
  }
  if (manuelito2 > 312)
  {
    jaimito = 0;
  }
  }
  return jaimito == 1? true : false;
}
