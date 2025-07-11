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

IpMatch *criar_um_ip(const char *ip){

  if(!IpMatch_is_ipv4_valid(ip, NULL, NULL)){
    printf("Esse ip não é valido!!!");
    exit(1);
  }

  IpMatch *ip_criado = IpMatch_new_ip(ip, malloc);
  if(!ip_criado){
    printf("\n\tNão deu certo!!!\n");
    exit(1);
  }

  return ip_criado;
}

void detalhes(IpMatch *ip_criado){
  printf("\n\tIP:<%s>\n", ip_criado->ip_string);
  printf("\n\tIP_byn:<");
  print_bin(ip_criado->ip_binary);
  printf(">\n");
  printf("\n\tmask:<%hd>\n", ip_criado->mask);
  printf("\n\tmask_byn:<");
  print_bin(ip_criado->mask_binary);
  printf(">\n");
}

int main(){
  printf("\n\tComeçou\n");

  const char *ref_str = "8.0.0.0/8";
  const char *ip_str = "8.4.2.1/23";

  IpMatch *ref = criar_um_ip(ref_str);
  IpMatch *ip = criar_um_ip(ip_str);

  printf("\n\tSão iguais? <%s>\n", IpMatch_is_ip_inside(ref, ip)?"TRUE":"FALSE");

  IpMatch_free(ref, free);
  IpMatch_free(ip, free);

  return 0;
}

 
