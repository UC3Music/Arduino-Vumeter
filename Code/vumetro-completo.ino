///////////////////////////////////////////////////
//////////////VÚMETRO PARA ARDUINO/////////////////
///////////////////////////////////////////////////
////////////Armando Astudillo Olalla///////////////
/////////////Asociación UC3Music-e/////////////////
////////Universidad Carlos III de Madrid///////////
///////////////////////////////////////////////////


int led[10] = {3,4,5,6,7,8,9,10,11,12}; //ASIGNAR PINES A LOS LEDs
int entrada = 0;                        //ENTRADA DE AUDIO
int audio, i, val, alto, logalto;
int a = 1;                              //IGUAL A 'O' PARA LINEAL Ó '1' PARA LOGARÍTMICO
int c = 1;                              //SEGUIR LA TABLA LINEAL AL FINAL DEL CODIGO
int d = 2;                              //SEGUIR LA TABLA LINEAL AL FINAL DEL CODIGO
int m =2;                               //SEGUIR LA TABLA LOGARÍTMICA AL FINAL DEL CODIGO




void setup() 
{
  for (i = 0; i < 10; i++)  
  pinMode(led[i], OUTPUT);
  pinMode(entrada, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  val = analogRead(entrada);               //LEE SEÑAL ENTRADA AUDIO
  
  
  
 if (a==0)
 {
    audio = (val*d)/c ;                    //TRANSFORMA LA ENTRADA SEGÚN DEPENDENCIA LINEAL
    
    if (val>alto)                          //COMPROBACIÓN DE MEDIDAS DEL VAL
    {
      alto = val;
      Serial.print("VAL-max: ");           //VALOR GUIA PARA ELECCIÓN DE PARÁMETROS
      Serial.println(alto);
    }
  }

  if (a!=0)
  {
    
    val = pow(val, m);                       //TRANSFORMA SEÑAL EN CURVA ASCENDENTE
    audio = log(val);                        //TRANSFORMA SEÑAL SALIDA EN LOGARITMO NEPERIANO
     
    if (val > logalto)                       //COMPROBACIÓN DE MEDIDAS DEL VAL
     {
       logalto = val;
       Serial.print("LogVAL-max: ");
       Serial.println(logalto);              //VALOR GUIO PARA ELECCIÓN DE PARÁMETROS
       
     }
   }
   
   //COMIENZO DE SELECCION DE LEDs
   
  if (audio <= 1)                              // SI EL VOLUMEN ES '0' PONE A OFF TODOS LOS LEDs
   {
    for(i = 0; i < 10; i++)
     {
       digitalWrite(led[i], LOW);
     }
   }
  
  else
    {
     for (i = 0; i < audio; i++)                // ENCIENDE LOS LEDs SEGÚN EL VOLUMEN
      {
       digitalWrite(led[i], HIGH);
      }
    
     for(i = i; i < 10; i++)                    // APAGA LOS LEDs SEGUN EL VOLUMEN
      {
        digitalWrite(led[i], LOW);
      }
    }  
}



/*
///////////////////////////////////////////////////////////////////////////////////
//////////////////////TABLAS////DE////ELECCIÓN/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

------------------------------LINEAL------------------------------------------------
------------------------------------------------------------------------------------
----A--------------C------------D--------M------VAL_MX---------------------VOLUMEN--
----0--------------1------------2--------X-------19_25------------------------BAJO--
----0--------------5------------1--------X-------50_60--------------------B_NORMAL--
----0--------------7------------1--------X-------65_80----------------------NORMAL--
----0--------------8------------1--------X------73_140--------------------A_NORMAL--
----0-------------15------------1--------X------210_XX------------------------ALTO--
------------------------------------------------------------------------------------

---------------------------LOGARITMICO----------------------------------------------
------------------------------------------------------------------------------------
----A--------------C------------D--------M------LOGVAL_MX------------------VOLUMEN--
----1--------------X------------X--------5---------40.000---------------------BAJO--
----1--------------X------------X--------2---------40.000--------------ALTO_NORMAL--
------------------------------------------------------------------------------------
*/





















