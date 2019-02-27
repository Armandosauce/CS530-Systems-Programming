#include <stdio.h>
#include <stdlib.h>

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

  printf("Assignment #1-1, Armando Perez, armandoperez0001@gmail.com\n");

  int len;
  char *buff;
  unsigned int checksum;
  
  FILE *fp = fopen(argv[1], "rb");
  fseek(fp, 0, SEEK_END);
  len = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  buff = (char *) malloc(len);
  fread(buff, len, 1, fp);
  
  checksum = crc32(buff, len);
  printf("%8x\n", checksum);
  fclose(fp);
  
}
