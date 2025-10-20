#include "clcd.h"
#include "main.h"
#include<stdlib.h>
#include<cstring>
CLCD clcd(D4, D5, D6, D7, RS, EN);
char str[17];
int digits=0;
unsigned long long count=99999999;
void setup()
{
    Serial.begin(115200);
    clcd.begin();
    Serial.print("input characters to display");
    clcd.print("DOWNCOUNTER", LINE1(3));
    //clcd.print("Hello  World", LINE1(2) );
    //clcd.print("CLCD on Arduino ", LINE2(0) );
}

void loop() {
    digits = 0;
    while(Serial.available() && sizeof(str) < 16) {
    // read the incoming byte
    str[i] = Serial.read();
    i++;
    // say what you got:
    }char str2[17];
    int AlreadyPrinted = 0;
    if(AlreadyPrinted){
    clcd.print(str2, LINE1(0));
    AlreadyPrinted = 0;
    }else{
      clcd.print(str,LINE2(0));
      AlreadyPrinted = 1;
      strcpy(str2,str);
    }
}