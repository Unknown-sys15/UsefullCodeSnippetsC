//int temp_histereza = 2;
//int hum_histereza = 2;
unsigned int OnOffRegTick =0;
void OnOffRegulator(){
     if ((timerValue - OnOffRegTick) < 781*2)return;                            //200ms
     OnOffRegTick  = timerValue;
     if ((zelena_temp+(temp_histereza/2)) < temp_value)                         //vklop klime
        {
             Test_led=1;
        }
     else if ((zelena_temp-(temp_histereza/2)) > temp_value)                    //izklop klime
     {
          Test_led=0;
     }
     //handlanje vlaznosti 
     /*
     if ((zelena_vlaznost+(hum_histereza/2)) < humidity_value)       //vklop klime
        {
             Izhod=1;
        }
     else if ((zelena_vlaznost-(hum_histereza/2)) > humidity_value)  //izklop klime
     {
          Izhod=0;
     } */
}
unsigned int OnOffRegTick1 =0;
void OnOffRegulator1(){
     if ((timerValue - OnOffRegTick1) < 781*2)return;
     OnOffRegTick1  = timerValue;
     if ((zelena_vlaznost+(hum_histereza/2)) < humidity_value)                  //vklop razvlazevalnika
        {
             Izhod=1;
        }
     else if ((zelena_vlaznost-(hum_histereza/2)) > humidity_value)             //izklop razvlazevalnika
     {
          Izhod=0;
     }
}