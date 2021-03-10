#include<stdio.h>

int main(void)

{
  int iVar1;
  char __stream[2000];
  FILE *__stream_00;
  size_t sVar2;
  char numero;
  int i;
  FILE *imagen;
  FILE *flag;
  size_t leidos;
  char seis [30];
  
  iVar1 =  0;//access("imagen.png",0);

  iVar1 = 0;//access("flag.txt",0);
  if (iVar1 == 0) {
    __stream_00 = fopen("./flag.txt","r");
    sVar2 = fread(seis,0x1e,1,__stream_00);
    if (0 == 0) {
      strcat(__stream, seis[0]);
      strcat(__stream, seis[1]);
      strcat(__stream, seis[2]);
      strcat(__stream, seis[3] + 5);
      strcat(__stream, seis[4] + 6);
      strcat(__stream, seis[5] + 7);
      i = 6;
      while (i < 0xc) {
        strcat(__stream, (char)(seis[i] + '\n'));
        i = i + 1;
      }
      numero = '\x10';
      i = 0xc;
      while (i < 0x10) {
        strcat(__stream, (char)((seis[i] - (char)i) + -3));
        i = i + 1;
      }
      while (numero < '\x18') {
        if ((numero & 1U) == 0) {
          strcat(__stream, (int)seis[(int)numero] + (int)numero);
        }
        else {
          strcat(__stream, (int)seis[(int)numero]);
        }
        numero = numero + '\x01';
      }
      while (numero < '\x1e') {
        strcat(__stream, (int)seis[(int)numero]);
        numero = numero + '\x01';
      }
      int a = print(__stream);
      fclose(__stream_00);
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    puts("Pues esto no hace nada.");
                    /* WARNING: Subroutine does not return */

  }
  puts("No se encuentra el archivo flag.txt...deberias crearlo :D");
                    /* WARNING: Subroutine does not return */

}
