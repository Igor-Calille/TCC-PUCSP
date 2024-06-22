from transformers import BertTokenizer, BertForSequenceClassification, pipeline, Trainer, TrainingArguments
import tensorflow as tf
import pandas as pd
from sklearn.model_selection import train_test_split
from tensorflow.keras.preprocessing.text import Tokenizer
from tensorflow.keras.preprocessing.sequence import pad_sequences
import re

# Carregar os dados

"""
data = pd.read_json('data/banco_brasil.json')
data = pd.DataFrame({'texto': data["title"] + " " +data["description"]})

"""


data_bancodobrasil = pd.read_json("data/banco_brasil.json")
data_bancodobrasil_con = pd.DataFrame({'texto': data_bancodobrasil["title"] + " " + data_bancodobrasil["description"]})

data_magalu = pd.read_json("data/magazineluiza.json")
data_magalu_con = pd.DataFrame({'texto': data_magalu["title"] + " " + data_magalu["description"]})


data_mglu3 = pd.read_json("data/mglu3.json")
data_mglu3_con = pd.DataFrame({'texto': data_mglu3["title"] + " " + data_mglu3["description"]})


data_varejo = pd.read_json("data/varejo.json")
data_varejo_con = pd.DataFrame({'texto': data_varejo["title"] + " " + data_varejo["description"]})


data = pd.merge(data_bancodobrasil_con, data_magalu_con, on='texto', how='outer').merge(data_mglu3_con, on='texto', how='outer').merge(data_varejo_con, on='texto', how='outer')


bert_classifier = pipeline('sentiment-analysis', model='neuralmind/bert-base-portuguese-cased')


data['texto'] = data['texto'].str.replace('\n', '')

#Função para obter o sentimento do BERTimbau e mapealo em positivo, negativo e neutro
def bert_sentiment(text):
    result = bert_classifier(text)[0]['label']
    if result == 'LABEL_0':
        return 0
    elif result == 'LABEL_1':
        return 1
    else:
        return 2
    
data['sentimento_bert'] = data['texto'].apply(bert_sentiment)




"""
from merge.wordbank_mine import lexicon

# Função para calcular sentimento baseado em pontuação de léxico
def lexicon_sentiment(text):
    sentiment_score = 0
    words = re.findall(r'\w+', text.lower())
    for word in words:
        if word in lexicon:
            sentiment_score += lexicon[word]
    if sentiment_score > 0:
        return 2
    elif sentiment_score < 0:
        return 0
    else:
        return 1

data['sentimento_keyword'] = data['texto'].apply(lexicon_sentiment)


print(data.head())
data.to_csv('merged.csv')

def combine_sentiments(bert_sentiment, keyword_sentiment):
    if bert_sentiment == keyword_sentiment:
        return bert_sentiment
    else: 
        if keyword_sentiment == 1:
            return bert_sentiment
        else:
            return keyword_sentiment


def combine(data):
    for i in range(len(data)):
    
        data.loc[i,'sentimento_final'] = int(combine_sentiments(int(data.loc[i,'sentimento_bert']), int(data.loc[i,'sentimento_keyword'])))
   
# Aplicar a função de combinação nos dados
combine(data)
data.to_csv('data_sentimento_final.csv', sep=';', index=False)

"""





"""

data = pd.read_csv('data_sentimento_final.csv', sep=';')

train_texts, test_texts, train_labels, test_labels = train_test_split(data['texto'], data['sentimento_final'], test_size=0.2)

#Tokenizar os textos
max_words = 10000
max_len = 128

tokenizer = Tokenizer(num_words=max_words, lower=True)
tokenizer.fit_on_texts(train_texts)

train_sequences = tokenizer.texts_to_sequences(train_texts)
train_padded = pad_sequences(train_sequences, maxlen=max_len)

test_sequences = tokenizer.texts_to_sequences(test_texts)
test_padded = pad_sequences(test_sequences, maxlen=max_len)


from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Embedding, LSTM, Dense, Dropout

#Definir a arquitetura do modelo
model = Sequential()
model.add(Embedding(input_dim=max_words, output_dim = 64, input_length=max_len))
model.add(LSTM(64, return_sequences=True))
model.add(Dropout(0.5))
model.add(LSTM(64))
model.add(Dense(64, activation='relu'))
model.add(Dropout(0.5))
model.add(Dense(3, activation='softmax'))

model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

model.summary()

history = model.fit(train_padded, train_labels, epochs=6, batch_size=32, validation_split=0.2)

loss, accuracy = model.evaluate(test_padded, test_labels)

print(f'Test Accuracy: {accuracy * 100:.2f}%')

model.save('sentiment_model.h5')


tokenizer_json = tokenizer.to_json()
with open('tokenizer.json', 'w', encoding='utf-8') as f:
   f.write(tokenizer_json)

   
   """