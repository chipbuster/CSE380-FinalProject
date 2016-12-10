import numpy as np
import matplotlib.pyplot as plt
import pickle
from matplotlib import rc
from mpl_toolkits.mplot3d import Axes3D
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import pdb

def plotOne(filename):
    """Plot the data in a single file"""
    data = np.loadtxt(filename, delimiter=",")
    print("Data Loaded!")

    x = data[0,::100]
    y = data[0,::100]
    z = data[0,::100]
    u = data[0,::100]
    v = data[0,::100]
    w = data[0,::100]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    ax.plot(x,y,zs=z)
    fig.show()
