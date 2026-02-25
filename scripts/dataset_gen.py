import csv
import random
import os
from faker import Faker

def gerar_jogadores(qtd, arquivo):
    fake = Faker("pt_BR")

    os.makedirs(os.path.dirname(arquivo), exist_ok=True)

    with open(arquivo, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["nome", "kills", "mortes", "assistencias"])
        for _ in range(qtd):
            nome = fake.first_name() + " " + fake.last_name()
            kills = random.randint(0, 30)
            mortes = random.randint(0, 20)
            assistencias = random.randint(0, 25)
            writer.writerow([nome, kills, mortes, assistencias])

if __name__ == "__main__":
    

    cenarios = {
        "pequeno": 100,
        "medio": 1000,
        "grande": 10000
        }

    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, "..", "data")

    os.makedirs(data_dir, exist_ok=True)

    # Gera os arquivos para cada cenário
    for nome, qtd in cenarios.items():
        arquivo = os.path.join(data_dir, f"jogadores_{nome}.csv")
        gerar_jogadores(qtd, arquivo)
        print(f"Arquivo {arquivo} gerado com {qtd} jogadores.")


# Observação:
# Para instalar a biblioteca Faker (caso ainda não tenha):
# python -m pip install Faker
