from utils import *
import parser


def generate_data(num: int):
    data = {' ': ['translated task', 'generated program']}
    for i in range(num):
        try:
            content = parser.parse(i)
            translated = translate(content)
            translated = translated.replace('.', '.\n')
            vrs = generate_variables(translated)
            loop = generate_loop(translated, vrs)
            program = compare(loop, vrs)
            data['program %d' % i] = [translated, program]
        except Exception as e:
            print(e)
    generate_csv(data)


if __name__ == '__main__':
    generate_data(6)
    # content = parser.parse(4)
    # translated = translate(content)
    # translated = translated.replace('.', '.\n')
    # print(translated)
    # # translated = 'Write a program that in the sequence of integers determines the number of numbers that are multiples of 5 or 9.' \
    # #              'The program receives integers as input, the number of entered numbers is unknown,' \
    # #              'the sequence of numbers ends with 0 (0 is a sign of the end of input, is not included in the sequence).' \
    # #              'The number of numbers does not exceed 1000. The entered numbers by module do not exceed 30,000.' \
    # #              'The program should output one number: the number of numbers that are multiples of 5 or 9.'
    # vrs = generate_variables(translated)
    # loop = generate_loop(translated, vrs)
    # print('\n' + compare(loop, vrs))
