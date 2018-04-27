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
  pixelsB1.setBrightness(50); 
  pixelsB1.setPixelColor(0, gBLUE);
  pixelsB1.setPixelColor(0, gBLUE);
  pixelsB1.setPixelColor(11, gBLUE);
  pixelsB1.show();
  pixelsB2.begin();
  pixelsB2.setBrightness(50);
  pixelsB2.setPixelColor(0, gGREEN);
  pixelsB2.setPixelColor(0, gGREEN);  
  pixelsB2.setPixelColor(11, gGREEN);
  pixelsB2.show();
  
  pixelsB3.begin();
  pixelsB3.setBrightness(50);
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
    for(int i = 0; i< 40; i++)
      Serial.print(data.charAt(i));
    Serial.print("\n");
    /**
    for(int i = 0; i < 15; i++)
        bridge1[i] = data.charAt(i);
        
    for(int j = 16; j < 31; j++)      
      bridge2[j-16] = data.charAt(j);
     
    for(int k = 32; k < 47; k++)
      bridge3[k-32] = data.charAt(k);
      
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
        else if(bridge1[aux_i_b] == 97 || bridge1[aux_i_b] == 65)//50 -> 2 | 97 -> a
          pixelsB1.setPixelColor(aux_i_a, gRED);
        else if(bridge1[aux_i_b] == 114 || bridge1[aux_i_b] == 82 )//51 -> 3 | 114 -> r
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
          else if(bridge3[aux_i_b] == 97 || bridge3[aux_i_b] == 65)//50 -> 2 | 97 -> a
            pixelsB1.setPixelColor(aux_i_a, gRED);
          else if(bridge3[aux_i_b] == 114 || bridge3[aux_i_b] == 82 )//51 -> 3 | 114 -> r
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
        else if(bridge2[aux_i_b] == 97 || bridge2[aux_i_b] == 65)//50 -> 2 | 97 -> a
          pixelsB2.setPixelColor(aux_i_a, gRED);
        else if(bridge2[aux_i_b] == 114 || bridge2[aux_i_b] == 82)//51 -> 3 | 114 -> r
          pixelsB2.setPixelColor(aux_i_a, gGREEN);
        else if(bridge2[aux_i_b] == 110)//48 -> 0 | 110 -> n
          pixelsB2.setPixelColor(aux_i_a, gOFF);


    } */   
    pixelsB2.show();
    pixelsB1.show();
    
  }
  delay(500);
}
