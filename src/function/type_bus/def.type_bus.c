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



