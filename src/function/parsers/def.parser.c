//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



short Private_IpMatch_parser_ipv4(IpMatch *self){

  if(!self || !self->ip_string){
    return 0;
  }

  int octets[4];
  short mask;

  if(!IpMatch_is_ipv4_valid(self->ip_string, octets, &mask)){
    return 0;
  }

  unsigned int ip_binary = 0;
  for (int i = 0; i < 4; i++) {
    ip_binary = (ip_binary << 8) | octets[i];
  }

  self->ip_binary = ip_binary;
  self->mask = mask;
  self->mask_binary = (mask == 0) ? 0 : 0xFFFFFFFF << (32 - mask);

  return 1;
}




