from math import sqrt, sin, cos, pi

import matplotlib.pyplot as plt
import json


def show_img(data):
    plt.imshow(data)
    plt.show()


def open_image_json(path):
    with open(path, 'r') as file:
        return json.load(file)


def circle_hough_transform(data):
    N_rows, N_cols = len(data), len(data[0])
    max_radius =  (N_cols >> 1) if N_rows > N_cols else (N_rows >> 1)
    print(N_rows, N_cols, max_radius)
    # (x - a)^2 + (y - b)^2 = r^2
    circle_space = [[[0 for i in range(max_radius + 1)] for j in range(N_cols)] for k in range(N_rows)]
    for row in range(N_rows):
        for col in range(N_cols):
            if data[row][col]:
                for degree in range(361):
                    theta = degree * pi / 180
                    for radius in range(max_radius + 1):
                        a = int(row - radius * sin(theta))
                        b = int(col - radius * cos(theta))
                        if a > row or b > col: continue
                        circle_space[a][b][radius] += 1
    return circle_space


def calculate_hough_space(hough_space, x, y, N_rows, N_cols):
    # x*cos(theta) + y*sin(theta) = p
    # (x - N_cols / 2)*cos(theta) + (y - N_rows / 2)*sin(theta) = p ?
    d = len(hough_space) >> 1
    radian = pi / 180
    for degree in range(0, 181):
        angle = radian * degree
        # p = int(x * cos(angle) + y * sin(angle)) + d
        p = int((x - N_cols / 2) * cos(angle) + (y - N_rows / 2) * sin(angle)) + d
        hough_space[degree][p] += 1


# x*cos(theta) + y*sin(theta) = p
# this function uses this formula
def hough_transform(data):
    N_rows, N_cols = len(data), len(data[0])
    d = int(sqrt(N_rows * N_rows + N_cols * N_cols)) >> 1
    hough_space = [[0 for j in range(-d, d + 1)] for i in range(0, 181)]

    for y in range(len(data)):
        for x in range(len(data[0])):
            if data[y][x]:
                calculate_hough_space(hough_space, x, y, N_rows, N_cols)
    return hough_space


def calculate_params(data):
    params = []     # contains params like (a, b)
    N_rows, N_cols = len(data), len(data[0])

    a_range = {"min": 0, "max": 0}
    b_range = {"min": 0, "max": 0}

    for y1 in range(N_rows):
        for x1 in range(N_cols):
            if data[y1][x1]:
                if N_rows - 1 == y1 and N_cols - 1 == x1:
                    continue

                for y2 in range(y1 + 1, N_rows):
                    for x2 in range(x1 + 1, N_cols):
                        if data[y2][x2]:
                            a = int((y1 - y2) / (x1 - x2))
                            b = int((y2 * x1 - y1 * x2) / (x1 - x2))

                            if a < a_range["min"]:
                                a_range["min"] = a
                            elif a > a_range["max"]:
                                a_range["max"] = a

                            if b < b_range["min"]:
                                b_range["min"] = b
                            elif b > b_range["max"]:
                                b_range["max"] = b

                            params.append((a, b))
    return params, a_range, b_range


# sl == straight line
# y = ax + b
def hough_transform_sl(data):
    params, a_axis, b_axis = calculate_params(data)

    a_axis["min"] = -a_axis["min"]
    b_axis["min"] = -b_axis["min"]

    print(a_axis)
    print(b_axis)

    N_rows, N_cols = int(sum(a_axis.values())), int(b_axis["max"])

    map = [[0 for j in range(N_cols + 1)] for i in range(N_rows + 1)]
    print(N_rows, N_cols)

    for (a, b) in params:
        i, j = int(b), int(a_axis["min"] + a)
        if i < 0:
            i = 0
        # print(i, j)
        map[j][i] += 1

    return map


origin_image = open_image_json("image_cirlces.json")
image = circle_hough_transform(origin_image)
circle_img = []

for row in image:
    arr = []
    for col in row:
        arr.append(sum(col))
    circle_img.append(arr)


show_img(origin_image)
show_img(circle_img)

# image = hough_transform(origin_image)
#
# figure = plt.figure(figsize=(6, 3))
#
# figure.add_subplot(1, 2, 1)
# plt.imshow(origin_image)
# plt.title("Origin image")
#
# figure.add_subplot(1, 2, 2)
# plt.imshow(image)
# plt.title("Hough space")
#
# plt.show()
