
// C++ program to demonstrate the
// cin object
#include <iostream>
#include <stdio.h> 
#include <stdlib.h> /* pour exit */ 
#include <string.h> /* pour memcpy */ 
#include "aes/aes.h"
using namespace std;
// Driver Code
int main()
{
  printf("tester \n");
  uint8_t key[] = { 0x61, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
                      0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 };
  uint8_t in[]  = { 'A', 'L', 'E', 'X', 'E', 'S', 'T', 'U', 'N', 'B', 'G','4','r', 't', 'o', 'b','f' };
  struct AES_ctx ctx;
  AES_init_ctx(&ctx, key);
  for (int i = 0; i <17 ; i++)
  {
    printf("-%c",in[i]);
  }
  printf("\n");
  AES_ECB_encrypt(&ctx, in);
  for (int i = 0; i <17 ; i++)
  {
    printf("/%c",in[i]);
  }
  printf("\n");
  AES_ECB_decrypt(&ctx,in);
  for (int i = 0; i <17 ; i++)
  {
    printf("*%c",in[i]);
  }
  printf("\n");

}

