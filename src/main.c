//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "imports/imports.def.h"
//silver_chain_scope_end

#include <stdio.h>
#include <stdlib.h>

void print_bin(unsigned int value) {
  for (int i = 31; i >= 0; i--) {
    char bit = (value & (1U << i)) ? '1' : '0';
    putchar(bit);
    if (i % 8 == 0 && i != 0) putchar('.'); // separador opcional entre octetos
  }
}

int main(){
  printf("\n\tComeçou\n");

  const char *ip = "1.1.1.1/24";

  IpMatch *ip_criado = IpMatch_new_ip(ip, malloc);

  if(!ip_criado){
    printf("\n\tNão deu certo!!\n");
    return 1;
  }

  printf("\n\tIP:<%s>\n", ip_criado->ip_string);
  printf("\n\tIP_byn:<");
  print_bin(ip_criado->ip_binary);
  printf(">\n");
  printf("\n\tmask:<%hd>\n", ip_criado->mask);
  printf("\n\tmask_byn:<");
  print_bin(ip_criado->mask_binary);
  printf(">\n");

  return 0;
}

 
