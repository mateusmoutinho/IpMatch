//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end


IpMatch *IpMatch_new_ip(const char *raw_ip, _private_type_malloc_IpMatch private_allocate){

  IpMatch *self = (IpMatch*)private_allocate(sizeof(IpMatch));
  if(!self){
    return 0;
  }

  self->ip_string = raw_ip;

  if(IpMatch_is_ipv6(self->ip_string)){
    return 0;
  }

  if(!Private_IpMatch_parser_ipv4(self)){
    return 0;
  }

  return self;
}

void IpMatch_free(IpMatch *self, _private_type_free_IpMatch private_free){
  if(self){
    private_free(self);
  }
}








