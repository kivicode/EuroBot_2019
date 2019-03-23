import serial
import time

serials = {}

RECIEVED = '-'  # символ прянития команды
SUCCESS = '~'  # символ успешного выполнения
REFUSED = '|'  # символ ошибки выполнения

WHEELS = 0
MANIPULATOR = 1

API = {'forward': 'f(%d)',  # Ехать вперёд на Х см
       'backward': 'b(%d)',  # Ехать назад на Х см
       'left': 'l(%d)',  # Повернуть влево на Х градусов
       'right': 'r(%d)',  # Повернуть вправо на Х градусов

       'calibrate forward': 'cf()',
       'calibrate backward': 'cb()',
       'calibrate left': 'cl()',
       'calibrate right': 'cr()',

       'grab': 'get()',

       'manipulator up': 'mu()',
       'manipulator down': 'md()'  # Опустить манипулятор + взять присоской
       }


def initialize():
    global ser_wheels
    ser_wheels = serial.Serial('/dev/tty.usbmodem14201', 9600, timeout=1)
    # ser_manipulator = serial.Serial('/dev/tty.wchusbserial1410', 9600, timeout=.1)
    # serials[MANIPULATOR] = ser_manipulator
    time.sleep(1)
    print('Can start')
    # except Exception:
    #     print("Arduino not found")


def send(ser, cmd):
    """ Отправка строки в сериал """
    ser.write((cmd + '\n').encode('utf-8'))


def read(ser):
    """ Читает данные из сериал """
    # CHECK: Maybe delete decoding
    # CHECK: Check for the last char '\n'
    line = ser.readline()
    return line.decode()


def wait_for(ser, symbol, max_time=-1):
    """ Ждёт, пока не придёт заданный символ """
    start_time = 0
    if max_time != -1:
        start_time = time.time()
    while True:
        if max_time != -1 and time.time() - start_time >= max_time:
            return -2
        data = read(ser)
        if data.find(symbol) != -1:  # выходит из цикла, если передётся параметр
            print(data)
            return 1
        elif data.find(REFUSED) != -1:  # Возвращает код ошибки, если ардуино не смогла выплнить
            print(data)
            return -1


def do(command, param=None):
    """Пыается выплнить и ждёт, пока не придёт ответ"""
    request = command  # генерация запроса, если передётся параметр
    ser = ser_wheels
    if not param is None:  # генерация запроса, если передётся параметр
        request = request % param  # передача парамтра в запрос
    send(ser, request + '\n')  # отправка запроса
    # print(request + '\n')
    if wait_for(ser, RECIEVED, 1) == -2:
        print(f'Command was not recieved {request}')
        return
    if wait_for(ser, SUCCESS, 1) == -1:
        print("Something happened while executing this command: %s" % request)
    else:
        print("Successfully complete: %s" % request)
