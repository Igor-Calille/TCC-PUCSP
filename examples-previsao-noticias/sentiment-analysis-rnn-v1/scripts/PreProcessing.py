import pandas as pd
import re
import requests

class PreProcessing:
    def __init__(self):
        pass


    def pre_processing(self):
        data_bancodobrasil = pd.read_json("data/raw/banco_brasil.json")
        data_bancodobrasil_con = pd.DataFrame({'texto': data_bancodobrasil["title"].str.lower() + " . " + data_bancodobrasil["description"].str.lower()})

        data_magalu = pd.read_json("data/raw/magazineluiza.json")
        data_magalu_con = pd.DataFrame({'texto': data_magalu["title"].str.lower() + " . " + data_magalu["description"].str.lower()})


        data_mglu3 = pd.read_json("data/raw/mglu3.json")
        data_mglu3_con = pd.DataFrame({'texto': data_mglu3["title"].str.lower() + " . " + data_mglu3["description"].str.lower()})


        data_varejo = pd.read_json("data/raw/varejo.json")
        data_varejo_con = pd.DataFrame({'texto': data_varejo["title"].str.lower() + " . " + data_varejo["description"].str.lower()})


        data_merged = pd.merge(data_bancodobrasil_con, data_magalu_con, on='texto', how='outer').merge(data_mglu3_con, on='texto', how='outer').merge(data_varejo_con, on='texto', how='outer')


        data_merged['texto'] = data_merged['texto'].str.replace('"', '')
        data_merged['texto'] = data_merged['texto'].str.replace('\n', '')
        data_merged['texto'] = data_merged['texto'].str.replace(';', '')
        data_merged['texto'] = data_merged['texto'].str.replace(',', '')
        data_merged['texto'] = data_merged['texto'].str.replace('´', '')
        data_merged['texto'] = data_merged['texto'].str.replace('`', '')
        data_merged['texto'] = data_merged['texto'].str.replace("'", '')
        data_merged['texto'] = data_merged['texto'].str.replace('‘', '')
        data_merged['texto'] = data_merged['texto'].str.replace('’', '')

        data_merged = data_merged.drop_duplicates(subset=['texto'])


        data_merged.to_csv("data/processed/data_merged.csv", index=False)

    def remover_caracteres_especiais(self, texto):
        return re.sub(r'[\'"´`]', '', texto)
    

class TranslateText:
    def __init__(self):
        self.url = "https://libretranslate.de/translate"

    def translate(self, text, source_lang='pt', target_lang='en'):
        payload = {
            "q": text,
            "source": source_lang,
            "target": target_lang,
            'format': 'text'
        }

        response = requests.post(self.url, data=payload)

        print(response.text)
        # Verifica se a solicitação foi bem-sucedida
        if response.status_code == 200:
            response_data = response.json()
            # Verifica se a chave 'translatedText' está presente na resposta JSON
            if 'translatedText' in response_data:
                return response_data['translatedText']
            else:
                return "Erro: 'translatedText' não encontrado na resposta."
        else:
            return f"Erro na tradução: {response.status_code} - {response.text}"