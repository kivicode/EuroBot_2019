import glob
import sys
import serial

SUCCESS = '~'  # символ успешного выполнения
REFUSED = '|'  # символ ошибки выполнения

API = {'forward': 'f(%d)',  # Ехать вперёд на Х см
       'backward': 'b(%d)',  # Ехать назад на Х см
       'left': 'l(%d)',  # Повернуть влево на Х градусов
       'right': 'r(%d)',  # Повернуть вправо на Х градусов
       'manipulator up': 'mu()',  # Поднять манипулятор
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
        ports = glob.glob('/dev/tty.*')
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
    return result


try:
    ser = serial.Serial(select_serial(), 9600, timeout=1)
except Exception as ignore:
    print("Arduino not found")


def send(cmd):
    """ Отправка строки в сериал """
    ser.write(str.encode(cmd))


def read():
    """ Читает данные из сериал """
    # CHECK: Maybe delete decoding
    # CHECK: Check for the last char '\n'
    line = ser.readline()
    return line.decode()


def wait_for(symbol):
    """ Ждёт, пока не придёт заданный символ """
    while True:
        data = read()
        if data == symbol:  # выходит из цикла, если передётся параметр
            break
        elif data == REFUSED:  # Возвращает код ошибки, если ардуино не смогла выплнить
            return -1
    return 1


def do(command, param=None):
    """Пыается выплнить и ждёт, пока не придёт ответ"""
    request = API[command]  # генерация запроса, если передётся параметр
    if not param is None:  # генерация запроса, если передётся параметр
        request = request % param  # передача парамтра в запрос
    send(request)  # отправка запроса
    if wait_for(SUCCESS) == -1:
        print("Something happened while executing this command: %s" % request)
    else:
        print("Successfully complete: %s" % request)
