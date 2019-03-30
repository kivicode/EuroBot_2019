import cv2
import imutils

camA = cv2.VideoCapture(1)


def getImage():
    _, frameA = camA.read()
    return cv2.flip(frameA, 0)


def show(name, frame, rpi=False):
    return cv2.imshow(name, imutils.resize(frame, height=600) if rpi else frame)