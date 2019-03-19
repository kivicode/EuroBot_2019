from utils import *  # импорт некоторых полезных функци
from api import *

POINTS = []

PURPLE = 0

lowers = [[0] * 3] * 3  # массив с нижними уровнями для 3 цветов
uppers = [[0] * 3] * 3  # массив с верхними уровнями для 3 цветов

pucks = {'purple': []}  # массив с шайбами

start_grabbing = False


def press(event, x, y, a, b):  # функция выбора пикселя для настройки цвета
    if event == cv2.EVENT_LBUTTONDBLCLK:
        POINTS.append([x, y])


def calibrate_purple(pixel, name=PURPLE):  # функция настройи по заданному цвету на изображении
    sensitivity: int = 30
    upper = np.array([pixel[0] + sensitivity, pixel[1] + sensitivity, pixel[2] + 2 * sensitivity])
    lower = np.array([pixel[0] - sensitivity, pixel[1] - sensitivity, pixel[2] - 2 * sensitivity])
    lowers[name] = lower
    uppers[name] = upper
    print(lower, upper)


def setup():  # первый цикл настройки, вызывается в начале программы
    cv2.namedWindow("Final")
    cv2.setMouseCallback('Final', press)

    while True:
        frame = getImage()
        cv2.imshow('Final', frame)
        if cv2.waitKey(1) & 0xFF == ord('p') or len(POINTS) == 1:  # вызов настроки цвета при выборе пикселя
            blurred = cv2.GaussianBlur(frame, (11, 11), 0)  # блюр
            hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
            pix = hsv[POINTS[0][1], POINTS[0][0]]
            calibrate_purple(pix)
            break
    initialize()


def main():  # основной цикл
    global start_grabbing
    orig = getImage()

    command = ord('p')

    try:
        blurred = cv2.GaussianBlur(orig, (11, 11), 0)  # блюр
        hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)  # перевод в HSV
        low = lowers[0]
        up = uppers[0]
        kernel = np.ones((10, 10), np.uint8)  # настройка ядра для морфологических преобразований
        mask = cv2.inRange(hsv, low, up)  # создание маски для цвета
        mask = cv2.erode(mask, kernel)  # эрозия
        mask = cv2.dilate(mask, kernel)  # растяжение
        mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)  # фильтрация шумов
        mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

        _, contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                                          cv2.CHAIN_APPROX_SIMPLE)  # поиск контуров шайб
        pucks['purple'].clear()  # чистка массива фиолетовых шайб для нового кадра
        h, w, c = orig.shape  # размеры картинки
        cv2.line(orig, (int(w / 2), 0), (int(w / 2), h),
                 (0, 255, 0))  # рисуем верт линию в центре экрана (для дебага)
        for cnt in contours:
            if cv2.contourArea(cnt) > 500:  # фильтрация по минимальной площади
                M = cv2.moments(cnt)  # поиск моментов контура
                cx = int(M['m10'] / M['m00'])  # вычисление центра по иксу
                cy = int(M['m01'] / M['m00'])  # вычисление центра по игреку
                pucks['purple'].append((cx, cy))  # добавляем центр шайбы в массив
                cv2.circle(orig, (cx, cy), 10, (255, 255, 255), -1)  # рисуем центр

        y_max = 0
        goal = pucks['purple'][0]
        for purple in pucks['purple']:  # поиск контура с максимальнм игреком (ближайшая)
            x, y = purple
            if y > y_max:
                y_max = y
                goal = purple
        text = ""
        goal_y = 615  # целевое значение по игреку (для манипулятора)
        tolerance_x = 80  # чуствительность по иксу
        tolerance_y = 50  # чуствительность по игреку
        # if not start_grabbing:
        if abs(goal[0] - (w / 2)) < tolerance_x:
            text = "OK"
        elif goal[0] < w / 2:
            text = "Turn Left"
            do('cl()\n')
        elif goal[0] > w / 2:
            text = "Turn Right"
            do('cr')

        if abs(goal[1] - goal_y) < tolerance_y:
            text += "  OK"
        elif goal[1] < goal_y:
            text += "  Go Forward"
            do('cf')
        elif goal[1] > goal_y:
            text += "  Go Backward"
            do('cb')

        if text == 'OK  OK':
            sys.exit()

        cv2.circle(orig, goal, 10, (0, 0, 255), -1)  # отмечаем целевую шайбу красным цветом
        cv2.putText(orig, text, (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0),
                    3)  # рисуем указания по движению робота

    except Exception as exception:
        print("Color detection runtime error: %s" % exception)
        pass

    cv2.imshow('Final', orig)


setup()

while True:  # вызывает главную функцию каждый кадр
    key = cv2.waitKey(1) & 0xFF
    main()
    # print(key if key != 255 else '')
    if key == ord('f'):
        do('calibrate forward')
    elif key == ord('b'):
        do('calibrate backward')
    elif key == ord('l'):
        do('cl()')
    elif key == ord('r'):
        do('calibrate right')
    if key == ord('q'):
        break

cv2.destroyAllWindows()
