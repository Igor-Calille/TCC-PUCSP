import json
import requests

url = "https://seeking-alpha.p.rapidapi.com/news/v2/list-by-symbol"

querystring = {"id":"tsla","size":"20","number":"1"}

headers = {
	"X-RapidAPI-Key": "c72625251dmsh91dc3be203d89f8p1a3c6ejsn117c2a712388",
	"X-RapidAPI-Host": "seeking-alpha.p.rapidapi.com"
}

response = requests.get(url, headers=headers, params=querystring)

print(response.json())


output = 'exit.txt'

json_file = json.dumps(response.json(), indent=4)

with open(output, "w") as file:
    file.write(json_file)