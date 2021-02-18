#include <LiquidCrystal.h>                              //Biblioteca para o display LCD
#include <EEPROM.h>                                     //Biblioteca para uso da EEPROM para armazenar e utilizar valores lidos
#define pino A1
#define pino2 A0

// --- Variáveis ---
int med, addr;
float temp=0.0, ltemp=0.0, botao=0.0;
boolean but0 = 0x00,  //Usados na leitura dos botoes da porta analogica A0
        but1 = 0x00, 
        but2 = 0x00, 
        but3 = 0x00, 
        but4 = 0x00,
        but5 = 0x00,
        but6 = 0x00,
        but7 = 0x00;

unsigned long values;

// --- Hardware do LCD ---
LiquidCrystal disp(2,  //RS no digital 2
                   3,  //RW no digital 3
                   4,  //EN no digital 4
                   5,  //D4 no digital 5
                   6,  //D5 no digital 6
                   7,  //D6 no digital 7
                   8); //D7 no digital 8
        
void setup()
{
     disp.begin(16,2);                                    //Inicializa LCD 16 x 2
     disp.setCursor(0,0);                                 //Posiciona cursor na coluna 1, linha 1
//     Serial.begin(9600);                                //incializa a saida serial (nao testado)
}
// --- Funções Auxiliares ---
void keyboardRead()
{
     if(botao <  127){
     but0 = 0x01;
     disp.setCursor(6,0);
     disp.print("Sem botao");
   }
     else if (botao > 200 && botao < 227) {
     but1 = 0x01;
     disp.setCursor(6,0);
     disp.print("Botao 1");
   }
     else if (botao > 227 && botao < 235) {
     but2 = 0x01;
     disp.setCursor(6,0);
     disp.print("Botao 2");
   }
     else if (botao > 236 && botao < 243) {
     but3 = 0x01;
     disp.setCursor(6,0);
     disp.print("Botao 3");
   }
     else if (botao > 243 && botao < 265) {
     but4 = 0x01;
     disp.setCursor(6,0);
     disp.print("Botao 4");
   }
     else if (botao > 265 && botao < 280) {
     but5 = 0x01;
     disp.setCursor(6,0);
     disp.print("Botao 5");
   }
     else if (botao > 320 && botao < 350) {
     but6 = 0x01; 
     disp.setCursor(6,0); 
     disp.print("Botao 6"); 
   }
     else if (botao > 1000 && botao < 1024) {
     but7 = 0x01;
     disp.setCursor(6,0);
     disp.print("Botao 7");
   }
}

void temper(){                                   
     disp.setCursor(0,0);
       disp.print(temp);
//       disp.print(botao);
//       Serial.println(temp);                        //Envia o valor para o serial
}

void loop()
{
  keyboardRead();
  botao=(analogRead(pino2));
  temp = (analogRead(pino)*0.4882813)-273.15;
  if (temp<=ltemp-0.5 || temp>=ltemp+0.5){
    ltemp = temp;
    temper();
 //   Serial.print("Temp: ");
  //  Serial.print(temp);
  //  Serial.print("ºC");
    disp.setCursor(1,0);
  }
    if (med % 1250 == 0){
      EEPROM.write(addr, temp);
      values=EEPROM.read(int(addr));
      disp.setCursor(0,1);
      disp.print("Temperatura ");
      disp.setCursor(12,1);
      disp.print(values);
      disp.setCursor(14,1);
      disp.print((char)223);
      disp.setCursor(15,1);
      disp.print("C");
    }
    med = med + 1;
}

