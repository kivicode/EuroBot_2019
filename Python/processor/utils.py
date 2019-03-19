from googletrans import Translator
import pandas

variables = {'mult': ''}
use_not = False
show_len = False
use_mult = False
use_str = False
use_end = False
loop_type = ''
end_symbol = ''
end_str = ''


def translate(text):
    translator = Translator()
    return translator.translate(text).text


def get_result_task(text):
    f = Finder(text)
    if f.find('The program should'):
        return text.split('The program should')[1].split('.')[0]
    if f.find('The program must'):
        return text.split('The program must')[1].split('.')[0]


def set_vars(text):
    global use_not, show_len, use_mult, use_str, end_str, use_end
    f = Finder(text)
    if f.find('maximum'):
        variables['max'] = '-10e9'
    if f.find('minimum'):
        variables['min'] = '10e9'
    if f.find('sum'):
        variables['sum'] = '0'
    if f.find('number of numbers'):
        variables['num'] = '0'

    mult_txt = '0'

    if f.find('multipl'):
        mult_txt = text.split('multipl')[1].split('of ')[1].split(' ')[0]
        use_mult = True
    elif f.find('even'):
        mult_txt = '2'
        use_mult = True
    elif f.find('odd'):
        mult_txt = '2'
        use_not = True
        use_mult = True
    variables['mult'] = mult_txt

    if f.find('ending in') or f.find('ends'):
        use_str = True
        end_str = text.split('end')[1].split(' ')[::-1][0]

    if f.find('length of'):
        show_len = True


def set_loop(txt):
    global loop_type, end_symbol
    f = Finder(txt)
    loop_type = 'for'
    if f.find('unknown') or f.find('is not included in the sequence)'):
        loop_type = 'while'
        end_symbol = txt.split('is not included in the sequence)')[0].split('(')[1].split(' ')[0]


def run(text):
    global variables, use_not, use_mult, show_len, use_str, use_end, loop_type, end_symbol, end_str
    variables = {'mult': ''}
    use_not = False
    show_len = False
    use_mult = False
    use_str = False
    use_end = False
    loop_type = ''
    end_symbol = ''
    end_str = ''
    task = get_result_task(text)
    set_vars(task)
    set_loop(text)
    return end_str


def generate():
    program = ''
    if loop_type == 'for':
        program += 'n = int(input())\n'
    elif show_len:
        program += 'n = 0\n'

    for it in variables.items():
        name, value = it
        program += f'{name} = {value}\n'

    if loop_type == 'for':
        program += 'for i in range(n):\n\ts = input()\n\tnumber = int(s)\n\t'
    else:
        program += f'while True:\n\ts = input()\n\tnumber = int(s)\n\tif number == {end_symbol}:\n' \
                   '\t\tbreak\n\t'

    if loop_type == 'while' and show_len:
        program += 'n += 1\n\t'

    additional = ''
    if in_vars('min'):
        additional = 'and number < min'
    if in_vars('max'):
        additional = 'and number > max'

    main = "if "
    if use_mult:
        main += f"number % mult {'!=' if use_not else '=='} 0"
    if use_str:
        main += (' and ' if use_mult else ' ') + f"s.endswith(\'{end_str}\')"
    program += f"{main} {additional}:"
    if in_vars('sum'):
        program += '\n\t\tsum += number\n'
    if in_vars('min'):
        program += '\n\t\tmin = number\n'
    if in_vars('max'):
        program += '\n\t\tmax = number\n'
    if in_vars('num'):
        program += '\n\t\tnum += 1\n'

    if in_vars('min'):
        program += '\nprint(min)'
    if in_vars('max'):
        program += '\nprint(max)'
    if in_vars('sum'):
        program += '\nprint(sum)'
    if in_vars('num'):
        program += '\nprint(num)'
    if show_len:
        program += '\nprint(n)'

    return program


def in_vars(name):
    try:
        v = variables[name]
        return True
    except:
        return False


def generate_csv(data):
    df = pandas.DataFrame(data=data)
    df.to_csv("output.csv", sep=',', index=False)


class Finder:

    def __init__(self, txt):
        self.txt = txt

    def find(self, text):
        return self.txt.find(text) != -1
