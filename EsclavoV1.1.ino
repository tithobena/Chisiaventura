//hola chisitos son

//La espada va al display 1
//Arco va al display 2
//El bife de chirizo va al display 3
//La Lana va al display 4
//El Escudo va al display 5

//String Cereal = "";
bool manuel; //este el del boton sabes xddd, si esta presionao
unsigned long manuelito; //es el del tiempo esmuy util
int accionesDisponibleHermano = 1;
bool empiezalobueno = true;
int cantidadDeLanas = 3;
int pepe = -1;
int vidaDelMalditoYHorribleWarden = 200;
int Sucri = 20; //es la vida por si revisan este codigo, gord@s
bool DiplaSelct(int eseeseldisplayqueestaseleccionado)//<-- hermanochi creo que ese explica solo
{
  return pepe == eseeseldisplayqueestaseleccionado + 1? true : false;
}
void setup()
{
  Serial.begin(9600);
  manuelito = millis();
  pinMode(12, INPUT);
}

void loop() 
{
  manuel = digitalRead(12) == HIGH; //es el boton sabes, si esta presionao
  //saca esta basura
  if (Serial.available() > 0)
  {
    
    pepe = Serial.read();
    Serial.println(String("granpepe") + pepe);
  }
  //hasta aca :V
  if (accionesDisponibleHermano != 0)
{
  if (DiplaSelct(1) && manuel)
  {
    vidaDelMalditoYHorribleWarden -= 25;
    accionesDisponibleHermano--;
    //Cereal = "";
    Serial.println(String("W") + vidaDelMalditoYHorribleWarden);
  }
  if (DiplaSelct(2) && manuel)
  {
    vidaDelMalditoYHorribleWarden -= QuickEventJuanitoTech()? 50 : 0;
    //Cereal = "";
    accionesDisponibleHermano--;
    Serial.println("W" + vidaDelMalditoYHorribleWarden);
    //use la misma mrd xd
  }
  if (DiplaSelct(3) && manuel)
  {
    Sucri += 3;
    accionesDisponibleHermano--;
    //Cereal = "";
    Serial.println(String("Vida:") + Sucri);
  }
  if (DiplaSelct(4) && manuel)
  {
    if (cantidadDeLanas > 0){
    accionesDisponibleHermano = 2;
    cantidadDeLanas--;
    //Cereal = "";
    Serial.println("AC:" + String(accionesDisponibleHermano));
    }else
    {
      Serial.println("nlana");
      //Cereal = "";
    }
  }
}else 
{
    if (empiezalobueno)
    {
    empiezalobueno = false;
    Sucri -= QuickEventJuanitoTech()? 0 : 6; //re tryhard xddddd
    Serial.println(String("Vida: ") + Sucri);
    accionesDisponibleHermano = 1;
    empiezalobueno = true;
    }
  }

}

bool QuickEventJuanitoTech()
{
  delay(500);
  manuelito = millis();
  unsigned long ttts = millis();
  float granChisitos = random(150, 250);
  int jaimito = -1;
  //ereal = "";
  while (jaimito == -1){
  unsigned long manuelito2 = millis() - ttts;
  manuelito2 = map(manuelito2, 0, 1000, 0, 400) / 4;
  Serial.println(String(manuelito2) + "<->" + String(granChisitos));
  if (manuel)
  {
    if (manuelito2 > granChisitos - 25 && manuelito2 < granChisitos + 25)
    {
      jaimito = 1; 
    }else{
      jaimito = 0;
    }
    //Cereal = "";
  }
  if (manuelito2 > 312)
  {
    jaimito = 0;
  }
  }
  return jaimito == 1? true : false;
}