from bs4 import BeautifulSoup
import requests


def parse(num):
    url = "https://inf-oge.sdamgia.ru/test?theme=20"
    r = requests.get(url)

    parser = BeautifulSoup(r.text, 'html.parser')

    # try:
    #     divs = str(parser.find_all("div")[num]).split('<b>20.2</b>')
    # except:
    #     divs = str(parser.find_all("div", {"class": "pbody"})[num]).split('<b>20.2 </b>')[1]
    return str(parser).split('Напишите программу')[num + 1].split('</p>')[0].replace('­', '').replace('<p>', '')
    # divs = divs.split('<p>')[0].replace('­', '')
