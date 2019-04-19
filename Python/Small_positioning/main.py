import cv2
from math import sin, cos, radians

pos = (70, 50)
angle = 45
length = 19

img = cv2.imread('img.png')


cv2.circle(img, pos, 6, (255, 0, 255), -1)
cv2.line(img, pos, (int(pos[0]+sin(radians(180-angle))*length), int(pos[1]+cos(radians(180-angle))*length)), (255, 0, 255), 2)


while True:
    cv2.imshow('field', img)
    if cv2.waitKey() & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
