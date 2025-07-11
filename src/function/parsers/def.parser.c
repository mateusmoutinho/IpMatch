//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



short ipMatch_parser_ipv4(IpMatch *self){

  const char *ip_raw = self->ip_string;
  int octets_temp[5] = {0, 0, 0, 0, 0};
  short octet_index = 0;
  short number_temp = 0;
  short digits = 0;
  short mask = 32;

  if(!ip_raw){
    return 0;
  }

  // ip_raw:       255.255.255.255/32
  // octets_temp: {255,255,255,255,32}
  // octet_index:    0   1   2   3  4

  while(*ip_raw){

    if(*ip_raw >= '0' && *ip_raw <= '9'){

      number_temp = number_temp * 10 + (*ip_raw - '0');
      if(number_temp > 255){return 0;}
      digits++;
    }else if(*ip_raw == '.'){
    
      if(digits == 0){return 0;}
      if(octet_index > 2){return 0;}
      octets_temp[octet_index++] = number_temp;
      number_temp = 0;
      digits = 0;
    }else if(*ip_raw == '/'){

      if(digits == 0){return 0;}
      if(octet_index != 3){return 0;}
      octets_temp[octet_index++] = number_temp;
      number_temp = 0;
      digits = 0;
    }else{
    
      return 0; // caractere inválido
    }

    ip_raw++;
  }

  if(digits == 0 || octet_index < 3 || number_temp > 255 || octet_index > 4){
    return 0;
  }
  octets_temp[octet_index] = number_temp;

  if(octet_index == 4){
    if(octets_temp[octet_index] > 32 || octets_temp[octet_index] < 0){
      return 0;
    }

    mask = octets_temp[octet_index];
  }

  unsigned int ip_binary = 0;
  for (int i = 0; i < 4; i++) {
    ip_binary = (ip_binary << 8) | octets_temp[i];
  }

  self->ip_binary = ip_binary;
  self->mask = mask;
  self->mask_binary = (mask == 0) ? 0 : 0xFFFFFFFF << (32 - mask);

  return 1;
}




