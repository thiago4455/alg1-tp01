# Trabalho prático 1 -  Algoritmos 1

###### Thiago Buenos Aires Mattos

O objetivo desse trabalho é solucionar um problema de atribuição de bicicletas para pessoas dado determinado mapa e prioridades.

De forma simplificada, cada pessoa possuí uma lista de bicicletas preferidas. Dado o mesmo número de bicicletas e pessoas, devemos achar a distribuição mais justa, utilizando a distância até a bicicleta como critério de desempate.
A distância deve ser encontrada atavés de um mapa informado na entrada do programa.

**Ex de entrada:**

```
2				// Número de visitantes (e bicicletas)
4 4			// Dimensão do mapa (h w)
a**1 		// Mapa
--**		// ...
*-**		// ...
b*0*		// ...
3 4			// Lista de preferencia do visitante 0
4 5			// Lista de preferencia do visitante 1
```

Atentamos ao fato que um número menor significa maior preferencia sobre a respectiva biscicleta.

**Ex de saída:**

```
a 1			// Visitante a (0) com bicicleta 1
b 0			// Visitante b (1) com bicicleta 0
```

**Simbolos no mapa**:

```
a-j		// Visitantes (de 0-9)
0-9		// Bicicletas
*			// Caminho livre
-			// Barreira (seção do mapa não atravessável)
```



**Comando para compilação e execução do trabalho:**

```bash
g++ -o tp01 src/main.cpp
./tp01 < test_cases/01.txt 
```



### Modelagem do problema

Podemos separar o problema em duas partes:

* Uma simples verificação de maior valor em um conjunto (encontrar a pessoa com maior prioridade)
* Um problema de menor caminho (para as distâncias no mapa)

Para o primeiro caso basta encontrar o valor mínimo para cada bicicleta, dado as listas de preferencia.

Já para o segundo caso, podemos pensar em um grafo não ponderado, onde cada espaço no mapa é um vértice (exeto as barreiras), e com vertices entre os espaços adjacenstes.
Para encontrar a distância então, podemos utilizar um algoritmo de caminho mais curto. Nesse trabalho foi utilizado uma implementação do algoritmo de Dijkstra.



### Solução

Para a verificação das prioridades foi percorrido cada pessoa para cada bicicleta, e armazenado as com maior prioridade. Caso só exista uma com aquele valor de prioridade, ele a atribuí à bicicleta. Caso contrário encontre a com menor distância.

Pseudocódigo:

```pseudocode
for (i =0; i < V; i++){
	highest_priority;
	highest_priority_persons[];
  for (j =0; j < V; j++){
		if person[j] has bike or person[j].priorities[i] < highest_priority:
			continue
		if person[j].priorities[i] == highest_priority:
			highest_priority_persons.insert(person[j])
		else
			highest_priority_persons = [person[j]]
  }
  
  if size of highest_priority_persons == 1:
    highest_priority_persons[0].bike = bike[i]
  else
    // Find lowest distance between highest_priority_persons and bike[i]
}
```



Para o algoritmo de caminho mais curto, foi feito uma função que com a fonte no heap, e para cada ponto no heap ele adiciona também os adjacentes para serem verificados. Os pontos já verificados são marcados, e ao encontrar um ponto igual ao destino é retornado a distância atual.

Pseudocódigo:

```pseudocode
while(pq is not empty){
	u = pq.pop()
	foreach position p adjacent to u.position{
		pq.push(p.position, u.distance + 1)
	}
	u.visited = true
}
```

Como a cada ponto adicionado no heap tem um deslocamento de 1, não é necessário verificar qual será o mais curto, e o primeiro que alcançar o destino já pode ser retornado.

### Complexidade de tempo

Dado a solução assima, podemos analisar a complexidade de cada parte individualmente.

A primeira, pode ser vista claramente como $O(V^2)$.
A segunda é uma implementação do algoritmo de Dijkstra, que possuí sua complexidade de $O(m\log n)$. Porém como o número de arestas é de no máximo $vertices\cdot4$ , podemos afirmar que a complexidade dessa etapa é de $O(NM)$ (N = linhas, N = colunas do mapa);

Os custos de leitura da entrada é de $O(V)$ e $O(NM)$, então não incrementam a complexidade.

Podemos constatar então uma complexidade de tempo total de $O(NM+V^2)$