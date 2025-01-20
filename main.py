import pyscreenshot as ImageGrab
import time

images_folder = "captured_images/9/"

def image_grab():
    for i in range(99,100):
        time.sleep(5)
        im = ImageGrab.grab(bbox=(120,210,380,530))
        print("saved........")
        im.save(images_folder+str(i)+".png")
        print("clear screen and redraw........... ",i)

# image_grab()
import cv2
import csv
import glob

def create_dataset():
    header = ["label"]
    for i in range(0,784):
        header.append("pixel"+str(i))
    with open('dataset.csv','a') as f:
        writer = csv.writer(f)
        writer.writerow(header)

    for label in range(10):
        dirList = glob.glob("captured_images/"+str(label)+"/*.png")

        for image_path in dirList:
            im = cv2.imread(image_path)
            im_gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
            im_gray = cv2.GaussianBlur(im_gray,(15,15),0)
            roi = cv2.resize(im_gray,(28,28), interpolation=cv2.INTER_AREA)

            data = []
            data.append(label)
            rows, cols = roi.shape

            for i in range(rows):
                for j in range(cols):
                    k = roi[i,j]
                    if k>100:
                        k = 1
                    else:
                        k = 0
                    data.append(k)
            with open('dataset.csv','a') as f:
                writer = csv.writer(f)
                writer.writerow(data)

# create_dataset()


import pandas as pd
from sklearn.utils import shuffle

data = pd.read_csv('dataset.csv')
data = shuffle(data)
# print(data)



X = data.drop(["label"], axis = 1)
Y = data["label"]

import matplotlib.pyplot as plt

idx = 314
img = X.iloc[idx].values.reshape(28,28)
# print(Y.iloc[idx])
# plt.imshow(img)
# plt.show()


from sklearn.model_selection import  train_test_split

train_x,test_x,train_y,test_y = train_test_split(X,Y, test_size=0.2)


import joblib
from sklearn.svm import SVC

classifier = SVC(kernel="linear", random_state=6)
classifier.fit(train_x, train_y)
def create_model():
    joblib.dump(classifier, "model/digit_recognizer")

from sklearn import metrics

prediction = classifier.predict(test_x)

# print("Accurancy = ", metrics.accuracy_score(prediction, test_y)) Accurancy = 91


import numpy as np

model = joblib.load("model/digit_recognizer")
images_folder = "img/"

while True:
    img = ImageGrab.grab(bbox=(120,210,380,530))

    img.save(images_folder + "img.png")
    im = cv2.imread(images_folder + "img.png")

    im_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
    im_gray = cv2.GaussianBlur(im_gray, (15,15),0)

    ret, im_th = cv2.threshold(im_gray, 100, 255, cv2.THRESH_BINARY)

    roi = cv2.resize(im_th, (28, 28), interpolation=cv2.INTER_AREA)

    rows, cols = roi.shape
    X = []

    for i in range(rows):
        for j in range(cols):
            k = roi[i, j]
            if k>100:
                k=1
            else:
                k = 0
            X.append(k)

    predictions = model.predict([X])

    print("Prediction:", predictions[0])

    cv2.putText(im, "Prediction is: " + str(predictions[0]), (20, 20),0, 0.8, (0,255,0),2,cv2.LINE_AA)

    cv2.startWindowThread()
    cv2.namedWindow("Result")
    cv2.imshow("Result", im)
    if cv2.waitKey(1) == 27:
        print("ESC key pressed. Exiting loop")
        break
    cv2.waitKey(10000)

cv2.destroyAllWindows()





