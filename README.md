# Análise de Algoritmos de Ordenação em Listas (aplicação em C e análise com Python)

O repositório consiste no desenvolvimento de um trabalho acadêmico que estuda a eficiência de algoritmos de ordenação no contexto de Listas (dinâmicas e estáticas) em Estruturas de Dados. Nesse sentido, foi escolhido como tema de pesquisa uma Leaderboard de jogos eletrônicos.

Além disso, a análise do desempenho dos algorítmos será feita com Python através dos dados obtidos com a implementação em C para uma lista de 100, 1.000 e 10.000 jogadores a serem ordenados.

A proposta foi dada no contexto da disciplina de Estruturas de Dados do curso de Bacharelado em Engenharia de Software da Universidade Federal do Cariri (UFCA), pelo professor [Weskley Mauricio](http://lattes.cnpq.br/9422036169528018). Os discentes envolvidos na pesquisa são: [Aisha Tomaz](https://github.com/aishatomaz), [Ramom Mascena](https://github.com/RamomRicarto), [Pedro Kauan](https://github.com/DevPKauan01), [Ramona Cardoso](https://github.com/ramona-dev), [Sabrina Alencar](https://github.com/sabrinaalencaar) e [Sebastião Sousa](https://github.com/SebastiaoSoares).

## Especificação e Documentação

As especificações e a documentação do projeto estão contidos na pasta `/docs`.

### Fluxo de Desenvolvimento do Projeto

O projeto seguirá o seguinte fluxo durante o desenvolvimento e a testagem:
1. Geração do volume de dados (Python) para serem consumidos pela implementação em C (`scripts/dataset_gen.py`);
2. Execução da implementação do projeto (`src/main.c`) para ordenação das listas e geração dos resultados (`data/results.csv`);
3. Plotagem de gráficos em Python (`plot_results.py`) que ficarão no diretório de dados (`data/plots/`).

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

## Como realizar os testes

### Preparando o Ambiente

Clone o repositório:
```bash
git clone https://github.com/aishatomaz/estrutura-de-dados.git
```
Caso queira, você pode contribuir através de um **fork**._

Prepare o ambiente - Python:
```bash
# 1. Crie um ambiente virtual
python -m venv venv

# 2. Entre no ambiente virtual
source ./venv/bin/activate # LINUX
.\venv\Scripts\activate # WINDOWS

# 3. Instale as dependências do Python
pip install -r requirements.txt
```

Prepare o ambiente - C:
```bash
# Compile os arquivos de execução

gcc -Iinclude src/main.c src/algoritmos/*.c src/estruturas/*.c src/desempenho/teste_desempenho.c -o main # LINUX

gcc -Iinclude src\main.c src\algoritmos\*.c src\estruturas\*.c src\desempenho\teste_desempenho.c -o main.exe # WINDOWS
```

### Executando

Execute os testes:
```bash
# Gere os dados com o Python
python ./scripts/dataset_gen.py

# Faça as análises com o C
./main # LINUX
.\main.exe # WINDOWS

# Gere os gráficos de desempenho
python ./scripts/plot_result.py
```
