<<<<<<< HEAD
from math import sqrt, sin, cos, pi

import matplotlib.pyplot as plt
import json


def show_img(data):
    plt.imshow(data)
    plt.show()


def open_image_json(path):
    with open(path, 'r') as file:
        return json.load(file)


def calculate_p(hough_space, x, y):
    # x*cos(theta) + y*sin(theta) = p
    d = len(hough_space) >> 1
    radian = pi / 180
    for degree in range(0, 181):
        angle = radian * degree
        p = int(x * cos(angle) + y * sin(angle)) + d
        hough_space[degree][p] += 1


def hough_transform(data):
    d = int(sqrt(len(data) * len(data) + len(data[0]) + len(data[0])))
    hough_space = [[0 for j in range(-d, d + 1)] for i in range(0, 181)]

    for y in range(len(data)):
        for x in range(len(data[0])):
            if data[y][x]:
                calculate_p(hough_space, x, y)
    return hough_space


show_img(open_image_json("image_hough.json"))
image = hough_transform(open_image_json("image_hough.json"))
show_img(image)
=======
import matplotlib.pyplot as plt
import itertools as iter
import json

# Hough transform

with open("image_hough.json", 'r') as f:
    image = json.load(f)

def show_img(img):
    plt.imshow(img)
    plt.show()


def get_input(msg):
    return list(map(int, input(msg).split()))

# show_img(image)
#
# row_start, col_start = get_input("Enter start point: ")
# row_finish, col_finish = get_input("Enter finish point: ")
# row_step, col_step = get_input("Enter step: ")

row_start, col_start = 0,0
row_step, col_step = 1, 1


def get_pairs(data):
    points = []
    for i in range(row_start, len(data), row_step):
        for j in range(col_start, len(data[i]), col_step):
            if data[i][j]:
                points.append([i, j])

    return list(iter.combinations(points, 2))


def get_coeff(point_pairs):
    coeffs = []
    # row_s, col_s, row_f, col_f = 0,0,0,0
    # size = 0
    for pair in point_pairs:
        y1, x1 = pair[0]
        y2, x2 = pair[1]

        x_diff = x1 - x2
        if x_diff:
            coeffs.append(( (y1 - y2) / x_diff, (y2*x1 - y1*x2) / x_diff ))
        else:
            coeffs.append(( ((y1 - y2) / x1 != 0 if x1 else 1), ((y2*x1 - y1*x2) / x1 != 0 if x1 else 1) ))

    #     if coeffs[size][0] > row_f: row_f = coeffs[size][0]
    #     elif coeffs[size][0] < row_s: row_s = coeffs[size][0]
    #
    #     if coeffs[size][1] > col_f: col_f = coeffs[size][1]
    #     elif coeffs[size][1] < col_s: col_s = coeffs[size][1]
    #     size += 1
    #
    # map_size = (int(abs(row_s) + abs(row_f)), int(abs(col_s) + abs(col_f)))

    return coeffs


def define_brightness(map_size, points):
    map = [[0 for i in range(map_size[1])] for j in range(map_size[0])]
    for point in points:
        row, col = round(abs(point[0])), round(abs(point[1]))
        print(row, col)
        map[row][col] += 1
    return map


def find_brightest_point(map):
    brightest = 0
    row, col = 0, 0
    for i in range(len(map)):
        for j in range(len(map[i])):
            if brightest < map[i][j]:
                brightest = map[i][j]
                row, col = i, j

    return row, col


print("Image size:", (len(image), len(image[0])))
coeffs = get_coeff(get_pairs(image))

# x = (a - A_start) / step_x
# y = (b - B_start) / step_y



print(map_size)




brightness_map = define_brightness(coeffs)

show_img(brightness_map)
>>>>>>> 64d1cf8963ba50a6c2b560f66d7fe0aaddf84f1f
