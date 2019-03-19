import glob
import sys
import serial
import time

RECIEVED = '-'  # символ прянития команды
SUCCESS = '~'  # символ успешного выполнения
REFUSED = '|'  # символ ошибки выполнения

API = {'forward': 'f(%d)',  # Ехать вперёд на Х см
       'backward': 'b(%d)',  # Ехать назад на Х см
       'left': 'l(%d)',  # Повернуть влево на Х градусов
       'right': 'r(%d)',  # Повернуть вправо на Х градусов

       'calibrate forward': 'cf()',
       'calibrate backward': 'cb()',
       'calibrate left': 'cl()',
       'calibrate right': 'cr()',

       'manipulator up': 'mu()',
       'manipulator down': 'md()'  # Опустить манипулятор + взять присоской
       }


def select_serial():
    """ Автоматически выбирает сериал порт """
    # MAGIC CODE
    ports = []
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.usb*')
    else:
        print('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result[0]


def initialize():
    global ser
    try:
        ser = serial.Serial(select_serial(), 9600, timeout=.1)
        time.sleep(4)
    except Exception:
        print("Arduino not found")


def send(cmd):
    """ Отправка строки в сериал """
    ser.write((cmd + '\n').encode('utf-8'))


def read():
    """ Читает данные из сериал """
    # CHECK: Maybe delete decoding
    # CHECK: Check for the last char '\n'
    line = ser.readline()
    return line.decode()


def wait_for(symbol, max_time=-1):
    """ Ждёт, пока не придёт заданный символ """
    start_time = 0
    if max_time != -1:
        start_time = time.time()
    while True:
        if max_time != -1 and time.time() - start_time >= max_time:
            return -2
        data = read()
        if data.find(symbol) != -1:  # выходит из цикла, если передётся параметр
            print(data)
            return 1
        elif data.find(REFUSED) != -1:  # Возвращает код ошибки, если ардуино не смогла выплнить
            print(data)
            return -1


def do(command, param=None):
    """Пыается выплнить и ждёт, пока не придёт ответ"""
    request = command  # генерация запроса, если передётся параметр
    if not param is None:  # генерация запроса, если передётся параметр
        request = request % param  # передача парамтра в запрос
    send(request + '\n')  # отправка запроса
    # print(request + '\n')
    if wait_for(RECIEVED, 1) == -2:
        print(f'Command was not recieved {request}')
        return
    if wait_for(SUCCESS, 1) == -1:
        print("Something happened while executing this command: %s" % request)
    else:
        print("Successfully complete: %s" % request)
