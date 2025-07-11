//silver_chain_scope_start
//mannaged by silver chain: https://github.com/OUIsolutions/SilverChain
#include "../../imports/imports.dec.h"
//silver_chain_scope_end


char *Private_IpMatch_strdup(const char *src, _private_type_malloc_IpMatch allocator) {
  if (!src || !allocator) return 0;

  // 1. Calcular o tamanho manualmente
  unsigned long len = 0;
  const char *tmp = src;
  while (*tmp++) len++;

  // 2. Alocar memória (tamanho + 1 para '\0')
  char *copy = (char *)allocator(len + 1);
  if (!copy) return 0;

  // 3. Copiar caractere por caractere
  for (unsigned long i = 0; i < len; i++) {
    copy[i] = src[i];
  }
  copy[len] = '\0'; // Garantir terminação

  return copy;
}

