from transformers import pipeline


class SentimentAnalysis_BERTimbau:
    def __init__(self):
        self.bert_classifier = pipeline('sentiment-analysis', model='neuralmind/bert-base-portuguese-cased')
    
    def predict(self,text):
        result = self.bert_classifier(text)[0]['label']
        if result == 'LABEL_0':
            return 0
        elif result == 'LABEL_1':
            return 1
        else:
            return 2

class SentimentAnalysis_BERT_multilingual_cased:
    def __init__(self):
        self.bert_classifier = pipeline('sentiment-analysis', model='bert-base-multilingual-cased')
    
    def predict(self,text):
        result = self.bert_classifier(text)[0]['label']
        if result == 'LABEL_0':
            return 0
        elif result == 'LABEL_1':
            return 1
        else:
            return 2
        

    


