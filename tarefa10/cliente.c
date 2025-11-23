#include "tabela_hash.h"

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    struct tabela_hash hash = cria_hash();
    preenche_hash(&hash, m);
    
    corretor(&hash, n);
   
    libera_hash(hash);

   return 0;
}