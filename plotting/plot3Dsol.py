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

    data = data[:,:]
    print("Data Loaded!")

    x = data[0,:]
    y = data[1,:]
    z = data[2,:]
    u = data[3,:]
    v = data[4,:]
    w = data[5,:]

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    ax.plot(x,y,zs=z)
    fig.show()
