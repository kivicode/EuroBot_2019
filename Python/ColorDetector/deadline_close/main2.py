import sys
from utils import *
import serial
import time
import numpy as np
import math
import cv2.aruco as aruco
import urllib
import cv2

camA = cv2.VideoCapture(1)
PORT = 'COM10'

zanyato = -1
inside = [0, 0, 0, 0]
points = []
pizda = 0
shmor = ''
lowers = {}  # массив с нижними уровнями для 3 цветов
uppers = {}  # массив с верхними уровнями для 3 цветов
field = ['green_field', 'blue_field', 'red_field']
index = 0

init = 0
aruco_dict = aruco.Dictionary_get(aruco.DICT_6X6_250)
parameters = aruco.DetectorParameters_create()

storona = ''
serials = {}

RECIEVED = '-'  # символ прянития команды
SUCCESS = '~'  # символ успешного выполнения
REFUSED = '|'  # символ ошибки выполнения

WHEELS = 0
MANIPULATOR = 1

colors = ['green', 'white', 'blue', 'red']
pucks = {colors[0]: [], colors[1]: [], colors[2]: [], colors[3]: []}  # кортеж с шайбами
color_index = 0

start_grabbing = False

action_index = 0

SIDE = 'PURPLE'

PORT = 'COM10'


def initialize():
    global ser_wheels
    global init
    ser_wheels = serial.Serial(PORT, 9600, timeout=1)
    time.sleep(1)
    print('Can start')
    init = 1


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
            # print(data)
            return data
        elif data.find(REFUSED) != -1:  # Возвращает код ошибки, если ардуино не смогла выплнить
            # print(data)
            return -1


def do(request, wait=False, extra=False):
    global init
    if init == 1:
        """Пыается выплнить и ждёт, пока не придёт ответ"""
        ser = ser_wheels
        send(ser, request + '\n')  # отправка запроса
        print(request)

        if wait:
            # if not extra:
            if wait_for(ser, RECIEVED, 1) == -2:
                print('Command was not received {}'.format(request))
                return
            suc = wait_for(ser, SUCCESS, 1)
            if suc == -1:
                print("Something happened while executing this command: %s" % request)
            else:
                print("Successfully complete: %s" % suc)
                return suc

        # time.sleep(0.4)
    else:
        print('no device connected')


def press(event, x, y, z, k):  # функция выбора пикселя для настройки цвета
    if event == cv2.EVENT_LBUTTONDBLCLK:
        points.append([x, y])


def getImage():
    _, frameA = camA.read()
    resized = cv2.resize(frameA, (400, 300))
    return cv2.flip(resized, 0)


def calibrate(pixel, name, sensitivity):  # функция настройи по заданному цвету на изображении
    upper = np.array([pixel[0] + sensitivity, pixel[1] + sensitivity, pixel[2] + 2 * sensitivity])
    lower = np.array([pixel[0] - sensitivity, pixel[1] - sensitivity, pixel[2] - 2 * sensitivity])
    lowers[name] = lower
    uppers[name] = upper


def first():
    global points
    cv2.namedWindow("Final")
    cv2.setMouseCallback('Final', press)
    for i in colors:
        points = []
        while True:
            frame = getImage()
            cv2.putText(frame, "Select %s color" % i, (10, 40), 2, 1, (255, 255, 250))
            cv2.imshow('Final', frame)
            if cv2.waitKey(1) & 0xFF == ord('p') or len(points) == 1:
                print('pizdec')
                blurred = cv2.GaussianBlur(frame, (11, 11), 0)  # блюр
                hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
                pixel = hsv[points[0][1], points[0][0]]
                calibrate(pixel, i, 40)
                break
    for i in field:
        points = []
        while True:
            frame = getImage()
            cv2.putText(frame, "Select %s color" % i, (10, 40), 2, 1, (255, 255, 250))
            cv2.imshow('Final', frame)
            if cv2.waitKey(1) & 0xFF == ord('p') or len(points) == 1:
                blurred = cv2.GaussianBlur(frame, (11, 11), 0)  # блюр
                hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
                pixel = hsv[points[0][1], points[0][0]]
                calibrate(pixel, i, 40)
                break
    print("start")


def transform(frame):
    blurred = cv2.GaussianBlur(frame, (11, 11), 0)  # блюр
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
    kernel = np.ones((10, 10), np.uint8)  # настройка ядра для морфологических преобразований
    mask = cv2.inRange(hsv, lowers[colors[index]], uppers[colors[index]])  # создание маски для цвета
    mask = cv2.erode(mask, kernel)  # эрозия
    mask = cv2.dilate(mask, kernel)  # растяжение
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)  # фильтрация шумов
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
    return mask


def get_pucks(mask, orig, index):
    contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)  # поиск контуров шайб
    pucks[colors[index]].clear()  # чистка массива  шайб для нового кадра
    for cnt in contours:
        if cv2.contourArea(cnt) > 500:  # фильтрация по минимальной площади
            M = cv2.moments(cnt)  # поиск моментов контура
            cx = int(M['m10'] / M['m00'])  # вычисление центра по иксу
            cy = int(M['m01'] / M['m00'])  # вычисление центра по игреку
            pucks[colors[index]].append((cx, cy))  # добавляем центр шайбы в массив
            cv2.circle(orig, (cx, cy), 10, (255, 255, 255), -1)  # рисуем центр
    cv2.imshow('Final', orig)
    # print(pucks)


def find_goal(frame):
    goal = [0, 0]
    y_max = 0
    color = 0
    for index in range(3):
        if len(pucks[colors[index]]) > 0:
            goal = pucks[colors[index]][0]
            for puck in pucks[colors[index]]:  # поиск контура с максимальнм игреком (ближайшая)
                x, y = puck
                if y > y_max:
                    y_max = y
                    goal = puck
                    color = index
    cv2.circle(frame, (goal), 10, (0, 0, 255), -1)
    cv2.imshow('Final', frame)
    return [goal, color]


def drive(goall, frame):
    global zanyato
    h, w, c = frame.shape  # размеры картинки
    cv2.line(frame, (int(w / 2), 0), (int(w / 2), h), (0, 255, 0))  # рисуем верт линию в центре экрана (для дебага)
    goal = goall[0]
    color = goall[1]
    tolerance_x = 40  # чуствительность по иксу
    tolerance_y = 10
    change_max = 0.1
    change_min = 0.1
    speed = 100
    shift = 0
    goal_y = 371
    motL = str(speed)
    motR = str(speed)

    if abs(goal[0] - ((w / 2) + shift)) < tolerance_x:
        motL = str(int(speed))
        motR = str(int(speed))
    elif goal[0] < (w / 2) + shift:
        motL = str(int(speed + abs(goal[0] - (w / 2)) * change_max))
        motR = str(int(speed - abs(goal[0] - (w / 2)) * change_min))
    elif goal[0] > (w / 2) + shift:
        motL = str(int(speed - abs(goal[0] - (w / 2)) * change_min))
        motR = str(int(speed + abs(goal[0] - (w / 2)) * change_max))
    cv2.putText(frame, motL, (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 3)
    cv2.putText(frame, motR, (400, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 3)
    cv2.imshow('Final', frame)

    if abs(goal[1] - goal_y) < tolerance_y:
        motL = str(0)
        motR = str(0)
        zanyato += 1
        return zanyato
    elif goal[1] > goal_y:
        motL *= -1
        motR *= -1
    do("for(%s, %s)" % (motL, motR))
    return 0


def take_puck():
    global inside
    while True:
        if cv2.waitKey(1):
            frame = getImage()
            for i in range(3):
                shok = transform(frame)
                get_pucks(shok, frame, i)
            goal = find_goal(frame)
            print(goal[1])
            p = drive(goal, frame)
            if p != 0:
                inside[zanyato] = goal[1]
                break


def get_state():
    if cv2.waitKey(1):
        _, frame = camA.read()
        corners, ids, _ = aruco.detectMarkers(frame, aruco_dict, parameters=parameters)
        detect = aruco.drawDetectedMarkers(frame, corners)
        # print(ids)
        # print(corners)
        motL = str(0)
        motR = str(0)
        if ids is None:
            ids = [0, 0]
        else:
            ids = [id[0] for id in ids]
        while (15 in ids) == False:
            if cv2.waitKey(1):
                motR = str(100)
                _, frame = camA.read()
                corners, ids, _ = aruco.detectMarkers(frame, aruco_dict, parameters=parameters)
                detect = aruco.drawDetectedMarkers(frame, corners)
                cv2.putText(frame, motL, (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 3)
                cv2.putText(frame, motR, (400, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 3)
                cv2.imshow('Final', detect)
                if ids is None:
                    ids = [0, 0]
                else:
                    ids = [id[0] for id in ids]
            do("for(%s, %s)" % (motL, motR))
            time.sleep(0.03)
        motL = str(0)
        motR = str(0)


def pryamo():
    while True:
        if cv2.waitKey(1):
            _, frame = camA.read()
            corners, ids, _ = aruco.detectMarkers(frame, aruco_dict, parameters=parameters)
            detect = aruco.drawDetectedMarkers(frame, corners)
            motL = str(0)
            motR = str(0)
            if not ids is None:
                print('g')
                motL = str(0)
                motR = str(0)
                x1 = corners[0][0][0][0]
                x2 = corners[0][0][1][0]
                prop = abs(corners[0][0][1][1] - corners[0][0][2][1]) / 20
                cv2.circle(frame, (corners[0][0][0][0], corners[0][0][0][1]), 2, (255, 0, 0), -1)
                cv2.circle(frame, (corners[0][0][1][0], corners[0][0][1][1]), 2, (0, 255, 0), -1)
                shit = 2
                print(x1, x2, prop)
                if abs(x1 - x2) < 20 * prop:
                    motL = str(100)
                    motR = str(100)
                elif x1 - x2 > - 20 * prop:
                    motL = str(100)
                    motR = str(0)
                    print('1')
                elif x2 - x1 > 20 * prop:
                    motL = str(0)
                    motR = str(100)
                    print('2')
            cv2.putText(frame, motL, (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 3)
            cv2.putText(frame, motR, (400, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 3)
            cv2.imshow('Final', detect)
            do("for(%s, %s)" % (motL, motR))
            time.sleep(0.03)


def press(event, x, y, *kw):  # функция выбора пикселя для настройки цвета
    if event == cv2.EVENT_LBUTTONDBLCLK:
        POINTS.append([x, y])


def calibrate(pixel, name):  # функция настройи по заданному цвету на изображении
    sensitivity = 70
    upper = np.array([pixel[0] + sensitivity, pixel[1] + sensitivity, pixel[2] + 2 * sensitivity])
    lower = np.array([pixel[0] - sensitivity, pixel[1] - sensitivity, pixel[2] - 2 * sensitivity])
    lowers[name] = lower
    uppers[name] = upper


def setup():  # первый цикл настройки, вызывается в начале программы
    global POINTS
    cv2.namedWindow("Final")
    cv2.setMouseCallback('Final', press)

    # for i in colors:
    i = colors[0]
    k = 0
    POINTS = []
    while True:
        frame = getImage()
        cv2.putText(frame, "Select %s color" % i, (10, 40), 2, 1, (255, 255, 250))
        cv2.imshow('Final', frame)
        if cv2.waitKey(1) & 0xFF == ord('p') or len(POINTS) == 1:
            blurred = cv2.GaussianBlur(frame, (11, 11), 0)  # блюр
            hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
            pix = hsv[POINTS[0][1], POINTS[0][0]]
            calibrate(pix, i)
            i = colors[k]
            k += 1
            POINTS = []
            if k == 4:
                break

    # initialize()
    print("start")
    # input("Enter something: ")
    # do("first", wait=True)
    print("Start")
    time.sleep(.5)


def get_cur_puck(orig):
    blurred = cv2.GaussianBlur(orig, (11, 11), 0)  # блюр
    hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
    low = lowers[colors[color_index]]
    up = uppers[colors[color_index]]
    kernel = np.ones((10, 10), np.uint8)  # настройка ядра для морфологических преобразований
    mask = cv2.inRange(hsv, low, up)  # создание маски для цвета
    mask = cv2.erode(mask, kernel)  # эрозия
    mask = cv2.dilate(mask, kernel)  # растяжение
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)  # фильтрация шумов
    mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)
    cv2.imshow('test', mask)

    contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                                   cv2.CHAIN_APPROX_SIMPLE)  # поиск контуров шайб
    pucks[colors[color_index]].clear()  # чистка массива  шайб для нового кадра
    h, w, c = orig.shape  # размеры картинки
    cv2.line(orig, (int(w / 2), 0), (int(w / 2), h),
             (0, 255, 0))  # рисуем верт линию в центре экрана (для дебага)
    for cnt in contours:
        if cv2.contourArea(cnt) > 500:  # фильтрация по минимальной площади
            M = cv2.moments(cnt)  # поиск моментов контура
            cx = int(M['m10'] / M['m00'])  # вычисление центра по иксу
            cy = int(M['m01'] / M['m00'])  # вычисление центра по игреку
            pucks[colors[color_index]].append((cx, cy))  # добавляем центр шайбы в массив
            cv2.circle(orig, (cx, cy), 10, (255, 255, 255), -1)  # рисуем центр


def main():  # основной цикл
    global start_grabbing, color_index, action_index
    k = 0

    if  action_index <= 1:
        color_index= 3
    elif action_index == 2:
        color_index = 0

    orig = getImage()
    get_cur_puck(orig)
    h, w, c = orig.shape  # размеры картинки
    if len(pucks[colors[color_index]]) > 0:
        goal = sorted(pucks[colors[color_index]], key=lambda x: x[1], reverse=True)[0]
        goal_y = 250  # целевое значение по игреку (для манипулятора)
        tolerance_x = 15  # чуствительность по иксу
        tolerance_y = 10  # чуствительность по игреку

        text = ""
        motL = ""
        motR = ""

        shift_x = 10
        if abs(goal[0] - ((w / 2) + shift_x)) < tolerance_x:
            text = "OK"
            motL = "150"
            motR = "150"
        elif goal[0] < (w / 2) + shift_x:
            text = "Turn Right"
            motL = "150"
            motR = "0"
        elif goal[0] > (w / 2) + shift_x:
            text = "Turn Left"
            motL = "0"
            motR = "150"

        if abs(goal[1] - goal_y) < tolerance_y:
            text += "  OK"
            motL = "0"
            motR = "0"
        elif goal[1] < goal_y:
            text += "  Go Forward"
        elif goal[1] > goal_y:
            text += "  Go Backward"
            motL = "-" + 'motR'
            motR = "-" + "motL"

        do("for(%s, %s)" % (motL, motR))
        time.sleep(0.04)
        print(goal[1])
        if text == 'OK  OK':
            if action_index == 0:
                k = 0
                while k != 1:
                    send(ser_wheels, 'two_arduino(0, 0)')
                    start_time = time.time()
                    while time.time() - start_time < 10:
                        if SUCCESS in read(ser_wheels):
                            k = 1
                action_index += 1

            if action_index <= 2:
                k = 0
                while k != 1:
                    send(ser_wheels, 'three_arduino(%s, 0)' % action_index)
                    start_time = time.time()
                    while time.time() - start_time < 10:
                        if SUCCESS in read(ser_wheels):
                            k = 1
                action_index += 1

        elif action_index >= 3:
            # do(..., ...)   ВЗЯТЬ ШАЙБУ ИЗ КУЧИ
            if action_index in [3, 4]:
                color_index = 3
            elif action_index == 5:
                color_index = 0
            elif action_index == 6:
                color_index = 2
            pass

    cv2.circle(orig, goal, 10, (0, 0, 255), -1)  # отмечаем целевую шайбу красным цветом
    cv2.circle(orig, (int(w / 2), goal_y), 10, (0, 255, 0), -1)  # отмечаем целевую шайбу красным цветом
    cv2.putText(orig, text, (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0),
                3)  # рисуем указания по движению робота

    # except Exception as exception:
    #     print("Color detection runtime error: %s" % exception)
    #     pass


cv2.imshow('Final', orig)

setup()
# first()
initialize()

# shmor
while True:
    if SUCCESS in read(ser_wheels):
        break

while True:  # вызывает главную функцию каждый кадр
    key = cv2.waitKey(1) & 0xFF
    main()
    if key == ord('q'):
        break

cv2.destroyAllWindows()

# start_time = time.time()
# while time.time() - start_time < 1:
#     do("for(100, 100)")
# #do("veseluha", True)
# # while zanyato != 3:
# #     take_puck()
# #     do("grab(%s, 100)" % (zanyato), True)
# # print(inside)
# cv2.destroyAllWindows()
# time.sleep(10)
