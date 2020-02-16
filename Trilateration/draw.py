import turtle
import pandas as pd
import tkinter
import math
import keyboard
import pyautogui as gui
import time
import re

def map(targ, min0, max0, min1, max1):
    return (targ-min0)*(max1-min1)/(max0-min0) + min1

def rememberPath():
    f = open('coord.csv', 'w')
    while True:
        if keyboard.is_pressed('b'):
            x, y = gui.position()
            print(x, y)
            f.write(str(x) + ',' + str(y) + '\n')
            time.sleep(.5)
        elif keyboard.is_pressed('e'):
            break
    f.close()

def drawStaticNode(pen, coord):
    pen.hideturtle()
    pen.speed(0)
    turtle.Screen().bgcolor('#dfdfdf')

    pen.up()

    rad = 100
    for i, j in coord.iterrows():
        x, y = (coord['x'][i], coord['y'][i])
        pen.goto(x, y)
        pen.dot()
        # pen.goto(x, y - rad)
        # pen.down()
        # pen.circle(rad)
        # pen.up()

csv = pd.read_csv('koordiam.csv')

coord = {'x':[], 'y':[]}

for x in csv['x']:
    coord['x'].append(math.trunc(map(x*1000000, -6977000, -6976100, -300, 300)))
for x in csv['y']:
    coord['y'].append(math.trunc(map(x*1000000, 107630500, 107631400, -300, 300)))

coord = pd.DataFrame(coord)

pen = turtle.Turtle()

drawStaticNode(pen, coord)
for x_elt in csv['x']:
  coord['x'].append(math.trunc(map(x*1000000, -6977000, -6976100, -300, 300)))
for x_eLg in csv['y']:
  coord['y'].append(math.trunc(map(x*1000000, 107630500, 107631400, -300, 300)))

r_earth = 6378
new_latitude  = x_eLt  + (dy / r_earth) * (180 / pi)
new_longitude = x_eLg + (dx / r_earth) * (180 / pi) / cos(x_e * pi/180)
csv = pd.read_csv('coord.csv')
f = open('minmax.txt', 'r')
mm = re.split(',',f.read())
f.close()

for i, x in enumerate(mm):
    mm[i] = int(x)

pen.goto(map(csv['x'][0], mm[0], mm[2], -300, 300), map(csv['y'][0], mm[3], mm[1], -300, 300))
pen.down()
for i, data in csv.iterrows():
    x, y = data
    x, y = (map(x, mm[0], mm[2], -300, 300), map(y, mm[3], mm[1], -300, 300))
    x, y = (math.trunc(x), math.trunc(y))
    pen.color('#ff0000')
    pen.width(3)
    pen.goto(x, y)
    pen.color('#00ff00')
    pen.width(5)
    pen.dot()
pen.up()

tkinter.mainloop()

print('Program End')