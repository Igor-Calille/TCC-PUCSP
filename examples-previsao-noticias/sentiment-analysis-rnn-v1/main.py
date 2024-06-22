import pandas as pd


from scripts.PreProcessing import PreProcessing, TranslateText
#from models.BERTPipeline import SentimentAnalysis_BERTimbau, SentimentAnalysis_BERT_multilingual_cased






if __name__ == "__main__":

    data = pd.read_csv("data/processed/data_merged.csv")

    translate_instance = TranslateText()
    
    data['texto'] = data['texto'].apply(lambda x: translate_instance.translate(x))
    
    data.to_csv("data/processed/data_merged_en.csv", index=False)

    """
    BERT_instance = SentimentAnalysis_BERT_multilingual_cased()

    data['sentimento_BERTimbau'] = data['texto'].apply(lambda x: BERT_instance.predict(x))

    data.to_csv("data/sentiment/data_Bertimbau.csv", index=False)
    """
    