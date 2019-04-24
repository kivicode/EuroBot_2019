import cv2
import cv2.aruco as aruco

# parameters = aruco.DetectorParameters_create()
# dictionary = aruco.Dictionary_get(aruco.DICT_6X6_250)
#
# cap = cv2.VideoCapture("http://10.5.5.9:8080/live/amba.m3u8")
# while True:
#     ret, frame = cap.read()
#     frame=cv2.resize(frame,(1080,720))
#
#     cv2.imshow("GoPro OpenCV", frame)
#
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break
#
# # cap.release()

def getMarkers(gray, debug=False):
    markers = {}
    cornerss, ids, rejectedImgPoints = aruco.detectMarkers(gray, dictionary,
                                                           parameters=parameters)
    i = 0
    for corners in cornerss:
        for cur in corners:
            center = [int((cur[0][0] + cur[2][0]) / 2), int((cur[0][1] + cur[2][1]) / 2)]
            markers[ids[i][0]] = {'center': center, 'corners': list([list(cor) for cor in list(cur)])}
            if debug:
                cv2.circle(gray, (center[0], center[1]), 10, (0, 0, 255), -1)
                cv2.putText(gray, str(ids[i][0]), (center[0], center[1]), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2,
                            cv2.LINE_AA)
                cv2.imshow("Fin", gray)
            i += 1
    return markers

# camA = cv2.VideoCapture(0)
#
# while True:
#     _, frame = camA.read()
#     gray = frame
#     cv2.imshow('Fin', gray)
#     markers = getMarkers(gray, debug=True)
#     print(markers)
#     if cv2.waitKey(1) & 0xFF == ord('q'):
#         break
#
#
# cv2.destroyAllWindows()
