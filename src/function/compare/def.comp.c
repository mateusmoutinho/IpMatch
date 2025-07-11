//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end



short IpMatch_is_ip_inside(IpMatch *ref, IpMatch *ip){
  if(!ref || !ip){return 0;}

  if (ref->mask == 32) {
    return ref->ip_binary == ip->ip_binary;
  }

  unsigned int ref_net = ref->ip_binary & ref->mask_binary;
  unsigned int test_net = ip->ip_binary & ref->mask_binary;

  return ref_net == test_net;
}


