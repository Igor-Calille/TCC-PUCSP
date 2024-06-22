import torch
from transformers import BertTokenizer, BertForSequenceClassification
import pandas as pd

model_name = 'neuralmind/bert-base-portuguese-cased'
tokenizer = BertTokenizer.from_pretrained(model_name)
model = BertForSequenceClassification.from_pretrained(model_name, num_labels=3)

def predict_sentiment(text):
    inputs = tokenizer(text, return_tensors="pt", truncation=True, padding=True, max_length=512)
    outputs = model(**inputs)
    probs = torch.nn.functional.softmax(outputs.logits, dim=-1)
    sentiment = torch.argmax(probs, dim=1).item()
    return sentiment # 0: Negativo, 1: Neutro, 2: Positivo

data_bancodobrasil = pd.read_json("banco_brasil.json")
data_bancodobrasil_con = pd.DataFrame({'body': data_bancodobrasil["title"] + " " + data_bancodobrasil["description"]})

data_magalu = pd.read_json("magazineluiza.json")
data_magalu_con = pd.DataFrame({'body': data_magalu["title"] + " " + data_magalu["description"]})


data_mglu3 = pd.read_json("mglu3.json")
data_mglu3_con = pd.DataFrame({'body': data_mglu3["title"] + " " + data_mglu3["description"]})

data_pedrobras = pd.read_json("Petrobras_noticias.json")
data_pedrobras_con = pd.DataFrame({'body': data_pedrobras["title"] + " " + data_pedrobras["description"]})


data_varejo = pd.read_json("varejo.json")
data_varejo_con = pd.DataFrame({'body': data_varejo["title"] + " " + data_varejo["description"]})


data_merged = pd.merge(data_bancodobrasil_con, data_magalu_con, on='body', how='outer').merge(data_mglu3_con, on='body', how='outer').merge(data_pedrobras_con, on='body', how='outer').merge(data_varejo_con, on='body', how='outer')



data_merged["sentimento"] = data_merged["body"].apply(predict_sentiment)


data_op_positivo = data_merged[data_merged["sentimento"] == 2]
data_op_negativo = data_merged[data_merged["sentimento"] == 0]

data_op_positivo.to_csv("banco_brasil_sentimentos_positivos.csv", index=False)
data_op_negativo.to_csv("banco_brasil_sentimentos_negativos.csv", index=False)