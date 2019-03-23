from bs4 import BeautifulSoup
import requests


def parse(num):
    url = "https://inf-oge.sdamgia.ru/test?theme=20"
    r = requests.get(url)
    parser = BeautifulSoup(r.text, 'html.parser')
    return str(parser).split('Напишите программу')[num + 1].split('</p>')[0].replace('­', '').replace('<p>', '')
