#include <Adafruit_NeoPixel.h>

#define policeRight 2
#define policeLeft 4

#define greenRight 14
#define redRight 9
#define greenLeft 10
#define redLeft 11

#define NUMPIXELS 15
#define NUMPIXELS2 14
#define BRIDGE1 5
#define BRIDGE2 6
#define BRIDGE3 8
#define gBLUE pixelsB1.Color(0,0,255)
#define gRED pixelsB1.Color(0,255,0)
#define gGREEN pixelsB1.Color(255,0,0)
#define gOFF pixelsB1.Color(0,0,0)

Adafruit_NeoPixel pixelsB1 = Adafruit_NeoPixel(NUMPIXELS, BRIDGE1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsB2 = Adafruit_NeoPixel(NUMPIXELS, BRIDGE2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsB3 = Adafruit_NeoPixel(NUMPIXELS, BRIDGE3, NEO_GRB + NEO_KHZ800);

int bridge1[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int bridge2[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int bridge3[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

String data = "";
int aux_i_a = 0;
int aux_i_b = 0;

void setup() {
  Serial.begin(115200);

  
  pixelsB1.begin();
  pixelsB1.setBrightness(10); 
  pixelsB1.setPixelColor(0, gBLUE);
  pixelsB1.setPixelColor(0, gBLUE);
  pixelsB1.setPixelColor(11, gBLUE);
  pixelsB1.show();
  pixelsB2.begin();
  pixelsB2.setBrightness(10);
  pixelsB2.setPixelColor(0, gGREEN);
  pixelsB2.setPixelColor(0, gGREEN);  
  pixelsB2.setPixelColor(11, gGREEN);
  pixelsB2.show();
  
  pixelsB3.begin();
  pixelsB3.setBrightness(10);
  pixelsB3.setPixelColor(0, gGREEN);
  pixelsB3.setPixelColor(0, gGREEN);  
  pixelsB3.setPixelColor(11, gGREEN);
  pixelsB3.show();
}

void loop() {
  
  if (Serial.available() > 0) {
    data = Serial.readString();


    int bridgeToPrint = data.charAt(48);
    Serial.print("Bridge to print ");       // prints a label
    Serial.print(bridgeToPrint);
    Serial.print("\n");
    for(int i = 0; i< 49; i++){
      Serial.print(data.charAt(i));      
    } 
     Serial.print("\n");
    /**
    for(int i = 0; i < 15; i++)
        bridge1[i] = data.charAt(i);
        
    for(int j = 16; j < 31; j++)      
      bridge2[j-16] = data.charAt(j);
     
    for(int k = 32; k < 47; k++)
      bridge3[k-32] = data.charAt(k);
     */

     bridge1[0] = data.charAt(16);
     bridge1[1] = data.charAt(17);
     bridge1[2] = data.charAt(18);
     bridge1[3] = data.charAt(19);
     bridge1[4] = data.charAt(20);
     bridge1[5] = data.charAt(21);
     bridge1[6] = data.charAt(22);
     bridge1[7] = data.charAt(23);
     bridge1[8] = data.charAt(24);
     bridge1[9] = data.charAt(25);
     bridge1[10] = data.charAt(30);
     bridge1[11] = data.charAt(27);
     bridge1[12] = data.charAt(28);
     bridge1[13] = data.charAt(29);
     bridge1[14] = '0';

     bridge2[0] = data.charAt(11);
     bridge2[1] = data.charAt(12);
     bridge2[2] = data.charAt(13);
     bridge2[3] = data.charAt(14);
     bridge2[4] = data.charAt(10);
     bridge2[5] = data.charAt(9);
     bridge2[6] = data.charAt(8);
     bridge2[7] = data.charAt(7);
     bridge2[8] = data.charAt(6);
     bridge2[9] = data.charAt(5);
     bridge2[10] = data.charAt(4);
     bridge2[11] = data.charAt(3);
     bridge2[12] = data.charAt(2);
     bridge2[13] = data.charAt(1);
     bridge2[14] = data.charAt(0);

     bridge3[0] = data.charAt(35);
     bridge3[1] = data.charAt(34);
     bridge3[2] = data.charAt(33);
     bridge3[3] = data.charAt(32);
     bridge3[4] = data.charAt(36);
     bridge3[5] = data.charAt(37);
     bridge3[6] = data.charAt(38);
     bridge3[7] = data.charAt(39);
     bridge3[8] = data.charAt(40);
     bridge3[9] = data.charAt(41);
     bridge3[10] = data.charAt(46);
     bridge3[11] = data.charAt(43);
     bridge3[12] = data.charAt(44);
     bridge3[13] = data.charAt(45);
     bridge3[14] = '0';
    //ccccccccccccccc:ccccccccccccccc:ccccccccccccccc:0:0 
    
    //cccrarrrrraccc:aaarcrrrrrarccc:0:0
    for(int i = 0; i < 15; i++){
        if(i >=10 && i < 13){
          aux_i_a = i;
          aux_i_b = i+1;
        }
        else if(i == 13){
          aux_i_a = 13;
          aux_i_b = 10;
        }
        else{
          aux_i_a = i;
          aux_i_b = i;
        }
        //aux_i_a=i;
        //aux_i_b=i;

        if(bridge1[aux_i_b] == 99 || bridge1[aux_i_b] == 67)//49 -> 1 | 99 -> c
          pixelsB1.setPixelColor(aux_i_a, gBLUE);
        else if(bridge1[aux_i_b] == 97 || bridge1[aux_i_b] == 65 || bridge1[aux_i_b] == 48)//50 -> 2 | 97 -> a
          pixelsB1.setPixelColor(aux_i_a, gRED);
        else if(bridge1[aux_i_b] == 114 || bridge1[aux_i_b] == 82 || bridge1[aux_i_b] == 49)//51 -> 3 | 114 -> r
          pixelsB1.setPixelColor(aux_i_a, gGREEN);
        else if(bridge1[aux_i_b] == 110)//48 -> 0 | 110 -> n
          pixelsB1.setPixelColor(aux_i_a, gOFF);
    } 

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(bridgeToPrint == 49)
    {
      for(int i = 0; i < 15; i++){
          if(i >=10 && i < 13){
            aux_i_a = i;
            aux_i_b = i+1;
          }
          else if(i == 13){
            aux_i_a = 13;
            aux_i_b = 10;
          }
          else{
            aux_i_a = i;
            aux_i_b = i;
          }
          //aux_i_a=i;
          //aux_i_b=i;
  
          if(bridge3[aux_i_b] == 99 || bridge3[aux_i_b] == 67)//49 -> 1 | 99 -> c
            pixelsB1.setPixelColor(aux_i_a, gBLUE);
          else if(bridge3[aux_i_b] == 97 || bridge3[aux_i_b] == 65 || bridge3[aux_i_b] == 48)//50 -> 2 | 97 -> a
            pixelsB1.setPixelColor(aux_i_a, gRED);
          else if(bridge3[aux_i_b] == 114 || bridge3[aux_i_b] == 82 || bridge3[aux_i_b] == 49 )//51 -> 3 | 114 -> r
            pixelsB1.setPixelColor(aux_i_a, gGREEN);
          else if(bridge3[aux_i_b] == 110)//48 -> 0 | 110 -> n
            pixelsB1.setPixelColor(aux_i_a, gOFF);
      }
    } 
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(int i = 0; i < 15; i++){
      if(i >=10 && i < 14){
        aux_i_a = i;
        aux_i_b = i+1;
      }
      else if(i == 14){
        aux_i_a = 14;
        aux_i_b = 10;
      }
      else if(i < 4){
        aux_i_a = 3-i;
        aux_i_b = i;
      }
      else{
        aux_i_a = i;
        aux_i_b = i;
      }     
            
      if(bridge2[aux_i_b] == 99 || bridge2[aux_i_b] == 67)//49 -> 1 | 99 -> c
          pixelsB2.setPixelColor(aux_i_a, gBLUE);
        else if(bridge2[aux_i_b] == 97 || bridge2[aux_i_b] == 65 || bridge2[aux_i_b] == 48)//50 -> 2 | 97 -> a
          pixelsB2.setPixelColor(aux_i_a, gRED);
        else if(bridge2[aux_i_b] == 114 || bridge2[aux_i_b] == 82 || bridge2[aux_i_b] == 49)//51 -> 3 | 114 -> r
          pixelsB2.setPixelColor(aux_i_a, gGREEN);
        else if(bridge2[aux_i_b] == 110)//48 -> 0 | 110 -> n
          pixelsB2.setPixelColor(aux_i_a, gOFF);


    }    
    pixelsB2.show();
    pixelsB1.show();
    
  }
  delay(500);
}
