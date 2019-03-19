import parser
from utils import *

if __name__ == '__main__':
    data = {'Task': ['Answer']}
    for i in range(15):
        try:
            print(f'Start parsing number {i+1}')
            orig = parser.parse(i)
            task = translate(orig)
            out_task = task.replace('.', '.\n')
            run(task)
            program = generate()
            print(out_task)
            print(program)
            data['Напишите программу' + out_task] = program
        except:
            pass
    generate_csv(data)
