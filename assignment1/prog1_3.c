#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <elf.h>


//a function designed to reverse the bits in an unsigned int
//function taken from stack overflow link: https://stackoverflow.com/questions/9144800/c-reverse-bits-in-unsigned-integer

unsigned int reverse(unsigned int x)
{
    x = ((x >> 1) & 0x55555555u) | ((x & 0x55555555u) << 1);
    x = ((x >> 2) & 0x33333333u) | ((x & 0x33333333u) << 2);
    x = ((x >> 4) & 0x0f0f0f0fu) | ((x & 0x0f0f0f0fu) << 4);
    x = ((x >> 8) & 0x00ff00ffu) | ((x & 0x00ff00ffu) << 8);
    x = ((x >> 16) & 0xffffu) | ((x & 0xffffu) << 16);
    return x;
}

char* atoHexStr(char* arr, int len)
{
    char* ret = malloc(len * 3);

    for(int i = 0; i < len; i++)
    {
        sprintf(ret + (i*3), "%02X ", arr[i] & 0xFF);
    }
    ret[len * 3 - 1] = 0;

    return ret;
}


unsigned int crc32(char *buffer, int n) {

  int i, j;
  unsigned int bits, reg, poly;

  poly = 0x04C11DB7;  
  reg = 0xFFFFFFFF;
  
  for(i = 0; i < n; i++) {
    
    bits = buffer[i];
    bits = reverse(bits);
    
    //number of bits in a char = 8
    for(j = 0; j < 8; j++) {
      
      //check if most significant bit is a 1
      if((int)(reg ^ bits) < 0) {
      
        reg = reg << 1;
        reg = reg ^ poly;
      }
      else {
        reg = reg << 1;
      }
      //shift off the most significant bit
      bits = bits << 1;
    }
  }
  
  //return the reverse of the flipped bits in register
  return reverse(~reg); 
}


int main(int argc, char *argv[]) {

  printf("Assignment #1-3, Armando Perez, armandoperez0001@gmail.com\n");

  Elf64_Ehdr elf;
  int len = 0;
  char *buff;
  int i = 0;
  unsigned int checksum;
  /*
  while(argv[2][i]) {
    len++;
  }
  
  char *hexString = atoHexStr(argv[2], len);
  
  FILE *fp = fopen(argv[1], "rb");
  fread(&elf, sizeof(elf), 1, fp);
  len = 0;
  
  /*
  for(i = 0; i < elf.e_shnum; i++ ) {
    if (i == elf.e_shstrndx) {
      
    }
  
  }
  
  len = 0x40;
  buff = (char *) malloc(len);
  
  fread(buff, len, 1, fp);
  fwrite(buff, len, 1, fp);
  
  checksum = crc32(buff, len);
  printf("%8x\n", checksum);
  
  fclose(fp);
  */
}
