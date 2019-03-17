from bs4 import BeautifulSoup
from utils import *
import requests


def parse(number, url="https://inf-oge.sdamgia.ru/test?theme=20"):
    print('[Log]  Start send request')
    html = requests.get(url).text
    print('[Log]  Answer got')

    parsed_html = BeautifulSoup(html, features="html.parser")

    print('[Log]  Start finding')
    content = str(parsed_html.findAll("div", {"class": "pbody"})[number * 2]).strip()
    try:
        content = content.split('<b>20.2</b>')[1].split('<p>')[0]
    except:
        content = content.split('<b>20.2 </b>')[1].split('<p>')[0]

    remove_list = list(find_all(content, '\xad'))
    task = ''.join([content[i] for i in range(len(content)) if not i in remove_list])

    return task
