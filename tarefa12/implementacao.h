//adaptado, retorna distancias tal que distancias[i] é a distância da cidade de id i até a origem escolhida
int * dijkstra (struct grafo * grafo, int origem);

//dados dois centros de distribuição já escolhidos, retorna a maior das menores distâncias nessa configuração
int maior_menor_distancia(struct grafo * grafo, int centro1, int centro2);

/*analiza todas as combinações de cidades possíveis, escolhe a configuração de menor distância de atendimento, aplicando o critério
de número de habitantes e imprime a resposta */
void melhor_cenario (struct grafo * grafo);