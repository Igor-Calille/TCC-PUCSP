import tensorflow as tf
from tensorflow.keras.models import load_model
from tensorflow.keras.preprocessing.text import tokenizer_from_json
from tensorflow.keras.preprocessing.sequence import pad_sequences
import pandas as pd
import json
import numpy as np

model = load_model('sentiment_model.h5')


with open('tokenizer.json') as json_file:
    tokenizer_json  = json_file.read()
    tokenizer = tokenizer_from_json(tokenizer_json)

def preprocess_text(texts, tokenizer, max_len=128):
    sequences = tokenizer.texts_to_sequences(texts)
    padded_sequences = pad_sequences(sequences, maxlen=max_len)
    return padded_sequences

def predict_sentiment(texts, model, tokenizer):
    preprocessed_texts = preprocess_text(texts, tokenizer)

    predictions = model.predict(preprocessed_texts)

    class_labels = ['negative', 'neutral', 'positive']
    predicted_labels = [class_labels[np.argmax(prediction)] for prediction in predictions]

    return predicted_labels

data = pd.read_json('data/Petrobras_noticias.json')
data = pd.DataFrame({'texto': data["title"] + " " + data["description"]})

data['sentimento'] = predict_sentiment(data['texto'].tolist(),model, tokenizer)


data.to_csv('data_exit.csv')