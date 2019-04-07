from utils import *  # импорт некоторых полезных функци
from api import *
import numpy as np
from matplotlib.colors import to_rgba as rgb

POINTS = []

lowers = {}  # массив с нижними уровнями для 3 цветов
uppers = {}  # массив с верхними уровнями для 3 цветов

colors = [
    'green',
    'white',
    'blue',
    'red'
]

pucks = {colors[0]: [], colors[1]: [], colors[2]: [], colors[3]: []}  # массив с шайбами

start_grabbing = False

color_index = 0


def press(event, x, y, *kw):  # функция выбора пикселя для настройки цвета
    if event == cv2.EVENT_LBUTTONDBLCLK:
        POINTS.append([x, y])


def calibrate(pixel, name):  # функция настройи по заданному цвету на изображении
    sensitivity = 60
    upper = np.array([pixel[0] + sensitivity, pixel[1] + sensitivity, pixel[2] + 2 * sensitivity])
    lower = np.array([pixel[0] - sensitivity, pixel[1] - sensitivity, pixel[2] - 2 * sensitivity])
    lowers[name] = lower
    uppers[name] = upper


def setup():  # первый цикл настройки, вызывается в начале программы
    global POINTS
    cv2.namedWindow("Final")
    cv2.setMouseCallback('Final', press)

    for i in colors:
        POINTS = []
        while True:
            frame = getImage()
            print(rgb(i)[::-1][1:][::-1])
            cv2.putText(frame, "Select %s color" % i, (10, 40), 2, 1, tuple([i * 255 for i in rgb(i)[::-1][1:]]))
            cv2.imshow('Final', frame)
            if cv2.waitKey(1) & 0xFF == ord('p') or len(POINTS) == 1:
                blurred = cv2.GaussianBlur(frame, (11, 11), 0)  # блюр
                hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
                pix = hsv[POINTS[0][1], POINTS[0][0]]
                calibrate(pix, i)
                break

    initialize()
    print("start")
    # input("Enter something: ")
    do("first", wait=True)
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

    _, contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
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
    print(pucks)


def main():  # основной цикл
    global start_grabbing, color_index
    orig = getImage()

    get_cur_puck(orig)
    h, w, c = orig.shape  # размеры картинки

    y_max = 0
    goal = pucks[colors[color_index]][0]
    for purple in pucks[colors[color_index]]:  # поиск контура с максимальнм игреком (ближайшая)
        x, y = purple
        if y > y_max:
            y_max = y
            goal = purple
    text = ""
    goal_y = 671  # целевое значение по игреку (для манипулятора)
    tolerance_x = 60  # чуствительность по иксу
    tolerance_y = 20  # чуствительность по игреку

    cmdA = ""
    cmdB = ""

    shift_x = -10

    if abs(goal[0] - ((w / 2) + shift_x)) < tolerance_x:
        text = "OK"
    elif goal[0] < (w / 2) + shift_x:
        text = "Turn Right"
        cmdA = 'cr()'
    elif goal[0] > (w / 2) + shift_x:
        text = "Turn Left"
        cmdA = 'cl()'

    if abs(goal[1] - goal_y) < tolerance_y:
        text += "  OK"
    elif goal[1] < goal_y:
        text += "  Go Forward"
        cmdB = 'cf()'
    elif goal[1] > goal_y:
        text += "  Go Backward"
        cmdB = 'cb()'

    do(cmdA)
    do(cmdB)

    if text == 'OK  OK':
        do("get", wait=True)
        print("Grabbed a new punk")
        time.sleep(2)
        color_index += 1

    cv2.circle(orig, goal, 10, (0, 0, 255), -1)  # отмечаем целевую шайбу красным цветом
    cv2.putText(orig, text, (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0),
                3)  # рисуем указания по движению робота

    # except Exception as exception:
    #     print("Color detection runtime error: %s" % exception)
    #     pass

    cv2.imshow('Final', orig)


setup()

while True:  # вызывает главную функцию каждый кадр
    key = cv2.waitKey(1) & 0xFF
    main()

    if key == ord('f'):
        do(WHEELS, 'calibrate forward')
    elif key == ord('b'):
        do(WHEELS, 'calibrate backward')
    elif key == ord('l'):
        do(WHEELS, 'cl()')
    elif key == ord('r'):
        do(WHEELS, 'calibrate right')
    elif key == ord('g'):
        do(MANIPULATOR, 'get()')
    if key == ord('q'):
        break

cv2.destroyAllWindows()
