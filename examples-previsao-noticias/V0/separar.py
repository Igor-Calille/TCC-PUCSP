import pandas as pd


def separar(nome_arq):

    data = pd.read_csv(nome_arq, sep=';')