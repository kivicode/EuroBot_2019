import wolframalpha as wf

app_id = "YKX6JJ-E7TW2XEP4P"  # надо зарегаться и найти app id тут http://developer.wolframalpha.com/portal делаешь
# новое приложение или можешь ползоваться моим
client = wf.Client(app_id)

formula = "sin(x^2)"  # сама формула
start = "0"  # начальная позиция
end = "100"  # окнечная позиция

q = f"Integrate {formula} from {start} to {end}"  # формирование запроса
res = client.query(q)  # отправка запроса
answer: str = next(res.results).text
result = ""
if answer.find('≈') != -1:  # выуживание ответа
    result = answer.split('≈')[1]
else:
    result = answer.split('=')[::-1][0]

print(result)
