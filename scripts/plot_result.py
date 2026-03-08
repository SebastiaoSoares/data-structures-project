import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def carregar_dados(caminho_csv):
    """Carrega e trata os dados do CSV gerado pelo programa em C."""
    try:
        df = pd.read_csv(caminho_csv)
        
        df[['Nome_Algoritmo', 'Estrutura']] = df['Algoritmo'].str.split(' ', n=1, expand=True)
        
        mapa_tamanhos = {"Pequeno": 100, "Medio": 1000, "Grande": 10000}
        df['N'] = df['Tamanho'].map(mapa_tamanhos)
        
        # Converter Tempo(ns) para Tempo(ms)
        if 'Tempo(ns)' in df.columns:
            df['Tempo_ms'] = df['Tempo(ns)'] / 1_000_000
        elif 'Tempo(ms)' in df.columns:
            df.rename(columns={'Tempo(ms)': 'Tempo_ms'}, inplace=True)
        
        return df
    except Exception as e:
        print(f"Erro ao carregar os dados: {e}")
        return None

def plotar_comparacao_algoritmos(df, diretorio_saida):
    """Gera gráficos de linha comparando os algoritmos para cada tipo de estrutura."""
    sns.set_theme(style="whitegrid")
    estruturas = df['Estrutura'].unique()

    for estrutura in estruturas:
        dados_cenario = df[df['Estrutura'] == estrutura]
        
        if dados_cenario.empty:
            continue

        plt.figure(figsize=(10, 6))
        sns.lineplot(
            data=dados_cenario, 
            x='N', 
            y='Tempo_ms', 
            hue='Nome_Algoritmo', 
            marker='o',
            linewidth=2
        )

        plt.title(f'Desempenho dos Algoritmos - Lista {estrutura}', fontsize=14)
        plt.xlabel('Volume de Dados (N)', fontsize=12)
        plt.ylabel('Tempo Médio de Execução (ms)', fontsize=12)
        
        plt.xscale('log') 
        plt.yscale('log') 
        
        plt.legend(title='Algoritmos')
        plt.tight_layout()

        nome_arquivo = f"comparacao_algoritmos_{estrutura.lower()}.png"
        caminho_salvar = os.path.join(diretorio_saida, nome_arquivo)
        plt.savefig(caminho_salvar)
        plt.close()

def plotar_impacto_estrutura(df, diretorio_saida):
    """Compara o tempo do mesmo algoritmo executado em Lista Estática vs Dinâmica."""
    sns.set_theme(style="whitegrid")
    algoritmos = df['Nome_Algoritmo'].unique()

    for alg in algoritmos:
        dados_cenario = df[df['Nome_Algoritmo'] == alg]
        
        if dados_cenario.empty:
            continue

        plt.figure(figsize=(8, 5))
        sns.barplot(
            data=dados_cenario, 
            x='Tamanho', 
            y='Tempo_ms', 
            hue='Estrutura',
            order=["Pequeno", "Medio", "Grande"]
        )

        plt.title(f'Impacto da Estrutura de Dados - {alg}', fontsize=14)
        plt.xlabel('Cenário (Volume de Dados)', fontsize=12)
        plt.ylabel('Tempo Médio de Execução (ms)', fontsize=12)
        
        nome_arquivo = f"impacto_estrutura_{alg.lower()}.png"
        caminho_salvar = os.path.join(diretorio_saida, nome_arquivo)
        plt.savefig(caminho_salvar)
        plt.close()

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    caminho_csv = os.path.join(script_dir, "..", "data", "results.csv")
    diretorio_saida = os.path.join(script_dir, "..", "data", "plots")

    os.makedirs(diretorio_saida, exist_ok=True)

    df_resultados = carregar_dados(caminho_csv)

    if df_resultados is not None:
        print("Gerando gráficos comparativos de algoritmos...")
        plotar_comparacao_algoritmos(df_resultados, diretorio_saida)
        
        print("Gerando gráficos sobre o impacto das estruturas...")
        plotar_impacto_estrutura(df_resultados, diretorio_saida)
        
        print("\nPronto! Todos os gráficos foram salvos na pasta 'data/plots'.")