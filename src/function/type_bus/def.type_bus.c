//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end




short IpMatch_is_ipv6(const char *ip_raw){

  while(*ip_raw){
      if (*ip_raw == ':') return 1; // IPv6
      ip_raw++;
  }
  return 0;

}

short IpMatch_is_ipv4_valid(const char *ip_raw, int *octets_out, short *mask_out){

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

  if(mask_out){
    *mask_out = mask;
  }
  if(octets_out){
    for (int i = 0; i < 4; i++) {
      octets_out[i] = octets_temp[i];
    }
  }

  return 1;
}



