# Análise de Algoritmos de Ordenação em Listas (aplicação em C e análise com Python)

O repositório consiste no desenvolvimento de um trabalho acadêmico que estuda a eficiência de algoritmos de ordenação no contexto de Listas (dinâmicas e estáticas) em Estruturas de Dados. Nesse sentido, foi escolhido como tema de pesquisa uma Leaderboard de jogos eletrônicos.

Além disso, a análise do desempenho dos algorítmos será feita com Python através dos dados obtidos com a implementação em C para uma lista de 100, 1.000 e 10.000 jogadores a serem ordenados.

A proposta foi dada no contexto da disciplina de Estruturas de Dados do curso de Bacharelado em Engenharia de Software da Universidade Federal do Cariri (UFCA), pelo professor [Weskley Mauricio](http://lattes.cnpq.br/9422036169528018). Os discentes envolvidos na pesquisa são: [Aisha Tomaz](https://github.com/aishatomaz), [Ramom Mascena](https://github.com/RamomRicarto), [Pedro Kauan](https://github.com/DevPKauan01), [Ramona Cardoso](https://github.com/ramona-dev), [Sabrina Alencar](https://github.com/sabrinaalencaar) e [Sebastião Sousa](https://github.com/SebastiaoSoares).

## Especificação e Documentação

As especificações e a documentação do projeto estão contidos na pasta `/docs`.

## Organização do Projeto

A orgnização do repositório e do código do projeto reflete a seguinte estrutura de pastas e arquivos:

```bash
/
├── data/                     # Dados geras (ignorado pelo Git)
│   ├── plots/                # Gráficos (gerados pelo Python)
│   ├── jogadores.csv         # Jogadores (gerados pelo Python)
│   └── results.csv           # Dados (gerados pelo C)
├── include/                  # Cabeçalhos (.h)
│   ├── algoritmos.h          
│   └── listas.h              
├── src/                      # Implementação (C)
│   ├── main.c
│   ├── algoritmos/           # ordenação
│   │   ├── bubble.c
│   │   ├── quick.c
│   │   └── ...
│   └── estruturas/           # Estruturas de Dados
│       ├── lista_din.c
│       └── lista_est.c
│── scripts/                  # Plotagem e dados (Python)
│   ├── plot_results.py       # Gera gráficos
│   └── dataset_gen.py        # Gera jogadores para o C
│── docs/
└── requirements.txt
```

## Guia de Contribuição

### Preparando o Ambiente

Clonagem do repositório:
```bash
git clone https://github.com/aishatomaz/estrutura-de-dados.git
```
_Você também pode constribuir através de um **fork**._

Certifique-se de instalar as dependências do Python contidas no arquivo `requirements.txt`.

_**[O guia será atualizado confome o projeto for desenvolvido.]**_