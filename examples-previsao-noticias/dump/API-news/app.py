from newsdataapi import NewsDataApiClient

# API key authorization, Initialize the client with your API key
api = NewsDataApiClient(apikey='pub_400541ce0a44e1d35d14f52db908560f08126')

# Fetch the latest financial news
response = api.news_api(q='IBOVESPA', language='pt',from_date='2024-01-01', to_date='2024-01-31')

# Print the response
print(response)
