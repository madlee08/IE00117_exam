# Autor: Ing. Andres Mora Zuniga
# Script para la graficacion de curvas tridimensionales con el color como cuarta dimension
# El archivo de lectura debe de tener formato:
# X, Y, Z
# en donde cada una de las columnas esta separada por un espacio
# y cada una de las filas es un instante de tiempo distinto.
import sys
import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
import csv
x=[];
y=[];
z=[];
t=[];

if len(sys.argv) < 2:
    print("Error: especifique correctamente la ruta del archivo")
    exit()

with open(str(sys.argv[1]), 'r') as csvfile:
    fileData = csv.reader(csvfile, delimiter=',')
    count = 1
    for row in fileData:
        x.append(float(row[0]));
        y.append(float(row[1]));
        z.append(float(row[2]));
        t.append(count);
        count+=1;
x=np.array([x,x]);
y=np.array([y,y]);
z=np.array([z,z]);
t=np.array([t,t]);
mpl.rcParams['legend.fontsize'] = 10
fig = plt.figure()
ax = fig.gca(projection='3d')
ax.plot_surface(x,y,z,facecolors=cm.jet(t/float(t.max())),edgecolors=None);
ax.view_init(azim=-90.0, elev=0.0)
plt.show()
