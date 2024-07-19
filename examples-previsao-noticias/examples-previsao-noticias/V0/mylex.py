import pandas as pd
import re

# Carregar seus textos
data = pd.read_json('banco_brasil.json')  # Supondo que você tenha um CSV com uma coluna de textos

# Dicionário de polaridade simples (exemplo)
lexicon = {
    # Muito Positivo
    'ótimo': 2,
    'excelente': 2,
    'maravilhoso': 2,
    'fantástico': 2,
    'impressionante': 2,
    'espetacular': 2,
    'perfeito': 2,
    'brilhante': 2,
    'recorde histórico': 2,
    'alta expressiva': 2,
    'lucro extraordinário': 2,
    'crescimento robusto': 2,
    'desempenho excepcional': 2,
    'valorização recorde': 2,
    'expansão acelerada': 2,
    'forte demanda': 2,
    'incrível': 2,
    'formidável': 2,
    'fenomenal': 2,
    'extraordinário': 2,
    'deslumbrante': 2,
    'notável': 2,
    'sensacional': 2,
    'esplêndido': 2,
    'glorioso': 2,
    'lucros recordes': 2,
    'forte crescimento': 2,
    'expansão significativa': 2,
    'balanço robusto': 2,
    'alta recorde': 2,
    'lucro impressionante': 2,
    'performance notável': 2,
    'resultados extraordinários': 2,
    'dividendos elevados': 2,
    'crescimento exponencial': 2,
    
    # Positivo
    'bom': 1,
    'agradável': 1,
    'positivo': 1,
    'satisfatório': 1,
    'interessante': 1,
    'agradável surpresa': 1,
    'favorável': 1,
    'animador': 1,
    'alta': 1,
    'crescimento': 1,
    'lucro': 1,
    'otimista': 1,
    'recuperação': 1,
    'apreciação': 1,
    'satisfatório': 1,
    'bem-sucedido': 1,
    'promissor': 1,
    'conveniente': 1,
    'gratificante': 1,
    'vantajoso': 1,
    'proveitoso': 1,
    'incremento': 1,
    'desempenho positivo': 1,
    'aumento': 1,
    'valorização': 1,
    'progresso': 1,
    'ganhos': 1,
    'estabilidade financeira': 1,
    'previsão otimista': 1,
    
    # Neutro
    'normal': 0,
    'comum': 0,
    'regular': 0,
    'estável': 0,
    'moderado': 0,
    'habitual': 0,
    'usual': 0,
    'aceitável': 0,
    'estabilidade': 0,
    'neutro': 0,
    'sem alteração': 0,
    'previsão mantida': 0,
    'sem impacto': 0,
    'manutenção': 0,
    'sem mudanças': 0,
    'mediano': 0,
    'razoável': 0,
    'adequado': 0,
    'ordinário': 0,
    'inalterado': 0,
    'sem variação': 0,
    'constante': 0,
    'previsão estável': 0,
    'mercado lateralizado': 0,
    'sem alterações significativas': 0,
    
    # Negativo
    'ruim': -1,
    'negativo': -1,
    'insatisfatório': -1,
    'fraco': -1,
    'decepcionante': -1,
    'desfavorável': -1,
    'problemático': -1,
    'inferior': -1,
    'queda': -1,
    'prejuízo': -1,
    'perda': -1,
    'desaceleração': -1,
    'retração': -1,
    'desapontador': -1,
    'lamentável': -1,
    'desaprovador': -1,
    'desagradável': -1,
    'redução': -1,
    'declínio': -1,
    'balanço negativo': -1,
    'revisão para baixo': -1,
    
    # Muito Negativo
    'péssimo': -2,
    'horrível': -2,
    'terrível': -2,
    'catastrófico': -2,
    'desastroso': -2,
    'desolador': -2,
    'chocante': -2,
    'deplorável': -2,
    'colapso': -2,
    'crise': -2,
    'desastre': -2,
    'falência': -2,
    'insolvência': -2,
    'recessão': -2,
    'pânico': -2,
    'desvalorização abrupta': -2,
    'abominável': -2,
    'deplorável': -2,
    'miserável': -2,
    'pavoroso': -2,
    'calamitoso': -2,
    'devastador': -2,
    'lastimável': -2,
    'colapso financeiro': -2,
    'quebra': -2,
    'insolvência': -2,
    'recessão profunda': -2,
    'crise aguda': -2,
    'desvalorização drástica': -2,
    'pânico no mercado': -2,
    'derrocada': -2,
    'calamidade econômica': -2,
}


# Função para calcular sentimento baseado em lexicon
def lexicon_sentiment(text):
    sentiment_score = 0
    words = re.findall(r'\w+', text.lower())
    for word in words:
        if word in lexicon:
            sentiment_score += lexicon[word]
    return sentiment_score

# Aplicar a função de sentimento ao conjunto de dados
data['sentimento'] = data['title'].apply(lexicon_sentiment)

# Normalizar os sentimentos em categorias
def categorize_sentiment(score):
    if score >= 2:
        return 2  # Muito positivo
    elif score == 1:
        return 1  # Positivo
    elif score == 0:
        return 0  # Neutro
    elif score == -1:
        return -1  # Negativo
    else:
        return -2  # Muito negativo

data['categoria_sentimento'] = data['sentimento'].apply(categorize_sentiment)

# Salvar o conjunto de dados anotado
data.to_csv('textos_com_sentimento_anotado.csv', index=False)
