import requests
from bs4 import BeautifulSoup
from datetime import datetime

def scrape_cnn_news(topic, start_date, end_date):
    base_url = "https://edition.cnn.com"
    search_url = f"{base_url}/search?q={topic}"
    

    try:
        response = requests.get(search_url)
        soup = BeautifulSoup(response.content, "html.parser")

        # Find all news headlines
        headlines = soup.find_all("h3", class_="cnn-search__result-headline")
        for headline in headlines:
            title = headline.text.strip()
            link = base_url + headline.a["href"]
            print(f"Title: {title}\nLink: {link}\n")

    except Exception as e:
        print(f"Error fetching data: {e}")

def main():
    topic_of_interest = "technology"  # Change this to your desired topic
    start_date = datetime(2020, 8, 1)  # Specify your start date
    end_date = datetime(2021, 3, 31)  # Specify your end date

    scrape_cnn_news(topic_of_interest, start_date, end_date)

if __name__ == "__main__":
    main()
