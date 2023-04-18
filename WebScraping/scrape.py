from bs4 import BeautifulSoup
import pandas as pd
import requests

url = "https://books.toscrape.com/catalogue/category/books_1/index.html"

response = requests.get(url)
potato = BeautifulSoup(response.content, 'html.parser')

outFile = open("potato.txt", "w")
outFile.write(str(potato))
