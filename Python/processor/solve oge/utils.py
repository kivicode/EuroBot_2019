from googletrans import Translator
import pandas


def find_all(a_str, sub):
    start = 0
    while True:
        start = a_str.find(sub, start)
        if start == -1:
            return
        yield start
        start += len(sub)


def translate(text):
    translator = Translator()
    return translator.translate(text).text


def generate_variables(content: str):
    variables = []
    con = Container(content)
    if con.find('maximum'):
        variables.append({'name': 'max', 'value': str(-get_max_abs(content) - 1)})
    if con.find('minimum'):
        variables.append({'name': 'min', 'value': str(get_max_abs(content) + 1)})
    if con.find('sum'):
        variables.append({'name': 'sum', 'value': '0'})
    if con.find('number of numbers that'):
        variables.append({'name': 'count', 'value': '0'})
    if con.find('sequence as input') or con.find('as input the number of numbers'):
        variables.append({'name': 'n', 'value': 'int(input())'})
    variables.append({'name': 'last_entered', 'value': 'n'})
    return variables


def get_max_abs(text: str):
    roi = text.split('do not exceed')[1].split('.')[0]
    num = roi.replace(',', '')
    return int(num)


def get_end_sequence(text: str):
    roi = text.split('sequence of numbers ends with')[1].split('(')[0].strip()
    return int(roi)


def generate_loop(content: str, variables: list):
    con = Container(content)
    loop_type = ''
    condition = ''
    addition = ''
    if con.find('sequence as input') or con.find('number of numbers in'):
        loop_type = 'for '
        condition = 'i in range(n):'
    elif con.find('unknown'):
        loop_type = 'while'
        condition = 'True'
        addition = '\tif num == {}:\n'.format(get_end_sequence(content)) + \
                   '\t\tbreak\n'
    program = addition + \
              '\n\ts = input()' + \
              '\n\tnum = int(s)' + \
              '\n\tif {}:\n'.format(generate_global_condition(content, variables)) + \
              '{}'.format(generate_body(variables)) + \
              '\tlast_entered = num'
    return {'loop_type': loop_type, 'condition': condition, 'content': program}


def generate_body(variables: list):
    body = ''
    if contains(variables, 'max'):
        body += '\t\tmax = num\n'
    if contains(variables, 'min'):
        body += '\t\tmin = num\n'
    if contains(variables, 'sum'):
        body += '\t\tsum += num\n'
    if contains(variables, 'count'):
        body += '\t\tcount += 1\n'
    return body


def generate_global_condition(content: str, variables: list):
    condition = ''
    con = Container(content)
    if con.find('multiple of'):
        condition = 'num % '
        roi = content.split('multiple of')[1].split('.')[0].strip()
        condition += roi + ' == 0'
    elif con.find('multiples of'):
        condition = 'num % '
        delimiter = ''
        roi = content.split('multiples of')[1].split('.')[0].strip()
        if con.find('or'):
            delimiter = 'or'
        elif con.find('and'):
            delimiter = 'and'
        rois = roi.split(delimiter)
        condition += rois[0] + "== 0 " + delimiter + " "
        for i in range(1, len(rois) - 1):
            condition += 'num %' + rois[i] + ' == 0 ' + delimiter + ' '
        condition += 'num %' + rois[len(rois) - 1] + " == 0"

    if len(contains(variables, 'max')) == 1:
        condition += ' and num > max'
    elif len(contains(variables, 'min')) == 1:
        condition += ' and num < min'
    return condition


def generate_output(variables: list):
    output = 'print(%s)'
    out_variables: str = ''
    for v in list(filter(lambda var: var['name'] in ['min', 'max', 'sum', 'count'], variables)):
        out_variables += v['name'] + (
            ', ' if v != list(filter(lambda var: var['name'] in ['min', 'max', 'sum', 'count'], variables))[::-1][0] else '')
    return output % out_variables


def compare(loop, vrs: list):
    compared = ''
    for v in vrs:
        compared += '{} = {}\n'.format(v['name'], v['value'])
    compared += '\n' + loop['loop_type'] + loop['condition'] + loop['content']
    compared += '\n%s' % generate_output(vrs)
    return compared


def contains(lst, name):
    return list(filter(lambda var: var['name'] == name, lst))


def generate_csv(data):
    df = pandas.DataFrame(data=data)
    df.to_csv("./file.csv", sep=',', index=False)


class Container:
    def __init__(self, text: str):
        self.text = text

    def find(self, txt):
        return self.text.find(txt) != -1
