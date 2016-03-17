import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import functools
import csv
import scipy.optimize
import numpy

def main():
    fxys = []
    xs = []
    ys = []
    with open('d.csv', newline='') as file:
        reader = csv.reader(file, delimiter=',')
        for x, y, fxy in reader:
            fxys.append(float(fxy))
            xs.append(float(x))
            ys.append(float(y))

    points = []
    for x, y, f in zip(xs, ys, fxys):
        points.append((x, y, f))

    params0 = [1, 1, 1]
    fun = functools.partial(error, points=points)
    res = scipy.optimize.minimize(fun, params0)

    xx, yy = numpy.meshgrid(range(0, 5), range(0, 6))
    z_plane = []
    for x, y in zip(xx, yy):
        z_plane.append(plane(x, y, res.x))

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_xlabel("Log du nombre de locations")
    ax.set_ylabel("Log de la prodcution maximale de poulet")
    ax.set_zlabel("Log du temps de calcul (s)")
    ax.scatter(xs, ys, zs=fxys)
    ax.plot_surface(xx, yy, z_plane, color='g', alpha = 0.2)
    print(res)
    plt.title("Test de puissance de l'algorithme dynamique")
    plt.show()

def plane(x, y, params):
    a, b, c = params
    return a*x + b*y + c

def error(params, points):
    result = 0 
    for(x,y,z) in points:
        plane_z = plane(x, y, params)
        diff = abs(plane_z - z)
        result += diff**2
    return result

if __name__ == "__main__":
    main()