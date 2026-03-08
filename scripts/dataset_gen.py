import csv
import os
import random

from faker import Faker


def calcular_pontuacao(kills, mortes, assistencias):
    # Regra identica a usada no C para classificar os cenarios.
    pontuacao = (kills * 10) + (assistencias * 5) - (mortes * 2)
    return pontuacao if pontuacao > 0 else 0


def gerar_jogadores_aleatorios(qtd, fake):
    jogadores = []
    for _ in range(qtd):
        kills = random.randint(0, 30)
        mortes = random.randint(0, 20)
        assistencias = random.randint(0, 25)
        jogadores.append(
            {
                "nome": fake.first_name() + " " + fake.last_name(),
                "kills": kills,
                "mortes": mortes,
                "assistencias": assistencias,
                "pontuacao": calcular_pontuacao(kills, mortes, assistencias),
            }
        )
    return jogadores


def salvar_csv(jogadores, arquivo):
    os.makedirs(os.path.dirname(arquivo), exist_ok=True)

    with open(arquivo, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["nome", "kills", "mortes", "assistencias"])
        for jogador in jogadores:
            writer.writerow(
                [
                    jogador["nome"],
                    jogador["kills"],
                    jogador["mortes"],
                    jogador["assistencias"],
                ]
            )


def limpar_arquivos_legado(data_dir, cenarios):
    # Remove arquivos antigos na raiz data/ para evitar poluicao.
    for nome in cenarios.keys():
        legado_base = os.path.join(data_dir, f"jogadores_{nome}.csv")
        if os.path.exists(legado_base):
            os.remove(legado_base)

        for tipo in ("aleatorio", "ordenado", "inverso"):
            legado = os.path.join(data_dir, f"jogadores_{nome}_{tipo}.csv")
            if os.path.exists(legado):
                os.remove(legado)

    legado_padrao = os.path.join(data_dir, "jogadores.csv")
    if os.path.exists(legado_padrao):
        os.remove(legado_padrao)


if __name__ == "__main__":
    fake = Faker("pt_BR")

    cenarios = {
        "pequeno": 100,
        "medio": 1000,
        "grande": 10000,
    }

    script_dir = os.path.dirname(os.path.abspath(__file__))
    data_dir = os.path.join(script_dir, "..", "data")
    cenarios_dir = os.path.join(data_dir, "cenarios")
    os.makedirs(data_dir, exist_ok=True)
    os.makedirs(cenarios_dir, exist_ok=True)

    limpar_arquivos_legado(data_dir, cenarios)

    # Gera os arquivos por volume e tipo de entrada em subpastas.
    for nome, qtd in cenarios.items():
        jogadores_aleatorios = gerar_jogadores_aleatorios(qtd, fake)
        jogadores_ordenados = sorted(
            jogadores_aleatorios,
            key=lambda jogador: jogador["pontuacao"],
            reverse=True,
        )
        jogadores_inversos = list(reversed(jogadores_ordenados))

        arquivos_por_tipo = {
            "aleatorio": jogadores_aleatorios,
            "ordenado": jogadores_ordenados,
            "inverso": jogadores_inversos,
        }

        for tipo, jogadores in arquivos_por_tipo.items():
            pasta_tipo = os.path.join(cenarios_dir, tipo)
            caminho = os.path.join(pasta_tipo, f"jogadores_{nome}.csv")
            salvar_csv(jogadores, caminho)
            print(f"Arquivo {caminho} gerado com {qtd} jogadores.")
