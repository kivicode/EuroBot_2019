from utils import *

POINTS = []

debug_colors = True
debug_markers = False

PURPLE = 0

lowers = [[0] * 3] * 3
uppers = [[0] * 3] * 3

pucks = {'purple': []}


def press(event, x, y, a, b):
    if event == cv2.EVENT_LBUTTONDBLCLK:
        POINTS.append([x, y])


def calibrate_purple(pixel, name=PURPLE):
    sensitivity: int = 60
    upper = np.array([pixel[0] + sensitivity, pixel[1] + sensitivity, pixel[2] + 2 * sensitivity])
    lower = np.array([pixel[0] - sensitivity, pixel[1] - sensitivity, pixel[2] - 2 * sensitivity])
    lowers[name] = lower
    uppers[name] = upper
    print(lower, upper)


def setup():
    cv2.namedWindow("Final")
    cv2.setMouseCallback('Final', press)

    while True:
        frame = getImage()
        cv2.imshow('Final', frame)
        if cv2.waitKey(1) & 0xFF == ord('p') or len(POINTS) == 1:
            blurred = cv2.GaussianBlur(frame, (11, 11), 0)
            hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
            pix = hsv[POINTS[0][1], POINTS[0][0]]
            calibrate_purple(pix)
            break


def main():
    orig = getImage()
    gray = cv2.cvtColor(orig, cv2.COLOR_BGR2GRAY)

    if debug_colors:
        try:
            blurred = cv2.GaussianBlur(orig, (11, 11), 0)
            hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)
            low = lowers[0]
            up = uppers[0]
            kernel = np.ones((10, 10), np.uint8)
            mask = cv2.inRange(hsv, low, up)
            mask = cv2.erode(mask, kernel)
            mask = cv2.dilate(mask, kernel)
            mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
            mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)

            _, contours, _ = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
                                              cv2.CHAIN_APPROX_SIMPLE)
            pucks['purple'].clear()
            h, w, c = orig.shape
            cv2.line(orig, (int(w / 2), 0), (int(w / 2), h), (0, 255, 0))
            for cnt in contours:
                if cv2.contourArea(cnt) > 500:
                    M = cv2.moments(cnt)
                    cx = int(M['m10'] / M['m00'])
                    cy = int(M['m01'] / M['m00'])
                    pucks['purple'].append((cx, cy))
                    cv2.circle(orig, (cx, cy), 10, (255, 255, 255), -1)
                    # rect = cv2.minAreaRect(cnt)
                    # box = cv2.boxPoints(rect)
                    # box = np.int0(box)
                    # cv2.drawContours(new_mask, [box], 0, (255, 255, 255), -1)
            y_max = 0
            goal = pucks['purple'][0]
            for purple in pucks['purple']:
                x, y = purple
                if y > y_max:
                    y_max = y
                    goal = purple
            text = ""
            goal_y = 560
            if abs(goal[0] - (w / 2)) < 15:
                text = "OK"
            elif goal[0] < w / 2:
                text = "Turn Left"
            elif goal[0] > w / 2:
                text = "Turn Right"

            if abs(goal[1] - goal_y) < 30:
                text += "  OK"
            elif goal[1] < goal_y:
                text += "  Go Forward"
            elif goal[1] > goal_y:
                text += "  Go Backward"
            cv2.circle(orig, goal, 10, (0, 0, 255), -1)
            cv2.putText(orig, text, (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 0, 0), 3)

            cv2.imshow("Mask", mask)
        except Exception as exception:
            print("Color detection runtime error: %s" % exception)
            pass
    # if debug_markers:
    #     try:
    #         marker = getMarkers(gray)[120]
    #         cv2.circle(orig, marker, 20, (255, 0, 255), -1)
    #     except Exception as exception:
    #         print("Marker %d no found" % int(str(exception)))
    cv2.imshow('Final', orig)


setup()

while True:
    try:
        main()
    except Exception as e:
        print(e)

    if cv2.waitKey(1) & 0xFF == ord('m'):
        debug_markers = not debug_markers
    if cv2.waitKey(1) & 0xFF == ord('c'):
        debug_colors = not debug_colors
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
