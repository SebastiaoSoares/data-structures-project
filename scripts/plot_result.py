import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os

def carregar_dados(caminho_csv):
    """Carrega e trata os dados do CSV gerado pelo programa em C."""
    try:
        df = pd.read_csv(caminho_csv)
        
        # Separa o nome do algoritmo e a estrutura (Ex: "BubbleSort Estatica")
        if 'Algoritmo' in df.columns:
            df[['Nome_Algoritmo', 'Estrutura']] = df['Algoritmo'].str.split(' ', n=1, expand=True)
        else:
            print("Erro: Coluna 'Algoritmo' não encontrada no CSV.")
            return None, None
            
        # Normaliza a coluna de tempo dinamicamente
        unidade_tempo = "ms"
        if 'Tempo(ns)' in df.columns:
            df.rename(columns={'Tempo(ns)': 'Tempo'}, inplace=True)
            unidade_tempo = "ns"
        elif 'Tempo(ms)' in df.columns:
            df.rename(columns={'Tempo(ms)': 'Tempo'}, inplace=True)
        else:
            nome_col_tempo = df.columns[2]
            df.rename(columns={nome_col_tempo: 'Tempo'}, inplace=True)
            
        # Identifica a ordem/cenário corretamente com base no TipoEntrada
        if 'TipoEntrada' in df.columns:
            df['Ordem'] = df['TipoEntrada']
            df['Tamanho_Cat'] = df['Tamanho']
        elif df['Tamanho'].str.contains(' - ').any():
            df[['Tamanho_Cat', 'Ordem']] = df['Tamanho'].str.split(' - ', n=1, expand=True)
        else:
            df['Tamanho_Cat'] = df['Tamanho']
            df['Ordem'] = 'Aleatorio' 
            
        # Mapeia os tamanhos para valores numéricos para o eixo X do gráfico de linhas
        mapa_tamanhos = {"Pequeno": 100, "Medio": 1000, "Grande": 10000}
        df['N'] = df['Tamanho_Cat'].str.strip().map(mapa_tamanhos)
        
        return df, unidade_tempo
    except Exception as e:
        print(f"Erro ao carregar os dados: {e}")
        return None, None

def plotar_comparacao_algoritmos(df, unidade_tempo, diretorio_saida):
    """Gera gráficos de linha comparando os algoritmos por estrutura e ordem."""
    sns.set_theme(style="whitegrid")
    estruturas = df['Estrutura'].unique()
    ordens = df['Ordem'].unique()

    for estrutura in estruturas:
        for ordem in ordens:
            dados_cenario = df[(df['Estrutura'] == estrutura) & (df['Ordem'] == ordem)]
            
            if dados_cenario.empty:
                continue

            plt.figure(figsize=(10, 6))
            sns.lineplot(
                data=dados_cenario, 
                x='N', 
                y='Tempo', 
                hue='Nome_Algoritmo', 
                marker='o',
                linewidth=2
            )

            plt.title(f'Desempenho: Lista {estrutura} ({ordem})', fontsize=14)
            plt.xlabel('Volume de Dados (N)', fontsize=12)
            plt.ylabel(f'Tempo Médio de Execução ({unidade_tempo})', fontsize=12)
            
            plt.xscale('log') 
            plt.yscale('log') 
            
            plt.legend(title='Algoritmos')
            plt.tight_layout()

            nome_arquivo = f"comparacao_{estrutura.lower()}_{ordem.lower().strip()}.png"
            caminho_salvar = os.path.join(diretorio_saida, nome_arquivo)
            plt.savefig(caminho_salvar)
            plt.close()

def plotar_impacto_estrutura(df, unidade_tempo, diretorio_saida):
    """Compara o tempo em Lista Estática vs Dinâmica para cada cenário."""
    sns.set_theme(style="whitegrid")
    algoritmos = df['Nome_Algoritmo'].unique()
    ordens = df['Ordem'].unique()

    for alg in algoritmos:
        for ordem in ordens:
            dados_cenario = df[(df['Nome_Algoritmo'] == alg) & (df['Ordem'] == ordem)]
            
            if dados_cenario.empty:
                continue

            plt.figure(figsize=(8, 5))
            sns.barplot(
                data=dados_cenario, 
                x='Tamanho_Cat', 
                y='Tempo', 
                hue='Estrutura',
                order=["Pequeno", "Medio", "Grande"]
            )

            plt.title(f'Impacto da Estrutura: {alg} ({ordem})', fontsize=14)
            plt.xlabel('Cenário (Volume de Dados)', fontsize=12)
            plt.ylabel(f'Tempo Médio de Execução ({unidade_tempo})', fontsize=12)
            
            nome_arquivo = f"impacto_est_{alg.lower().replace(' ', '')}_{ordem.lower().strip()}.png"
            caminho_salvar = os.path.join(diretorio_saida, nome_arquivo)
            plt.savefig(caminho_salvar)
            plt.close()

if __name__ == "__main__":
    script_dir = os.path.dirname(os.path.abspath(__file__))
    caminho_csv = os.path.join(script_dir, "..", "data", "results.csv")
    diretorio_saida = os.path.join(script_dir, "..", "data", "plots")

    # Cria o diretório se não existir
    os.makedirs(diretorio_saida, exist_ok=True)

    df_resultados, unidade = carregar_dados(caminho_csv)

    if df_resultados is not None:
        print("Gerando gráficos comparativos de algoritmos...")
        plotar_comparacao_algoritmos(df_resultados, unidade, diretorio_saida)
        
        print("Gerando gráficos sobre o impacto das estruturas...")
        plotar_impacto_estrutura(df_resultados, unidade, diretorio_saida)
        
        print("\nPronto! Todos os gráficos foram salvos na pasta 'data/plots'.")