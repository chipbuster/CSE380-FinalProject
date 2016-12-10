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


from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d
class Arrow3D(FancyArrowPatch):
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)

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

    # Draw curve
    ax.plot(x,y,zs=z, lw=4)

    # Draw some arrows
    scale = 0.2
    for j in range(100):
        if j % 5 == 0:
            x = data[0,j]
            y = data[1,j]
            z = data[2,j]
            u = data[3,j] * scale
            v = data[4,j] * scale
            w = data[5,j] * scale
            print(x,y,z,u,v,w)
            a = Arrow3D([x,x+u],[y,y+v],[z,z+w], mutation_scale=20, lw=1, arrowstyle="-|>", color="k")
            ax.add_artist(a)

#    plt.title("Charged Particle with RK-CK")
    fig.show()

def plotComparison(rk4Fn,rkckFn,rkf45Fn):
    """Plot three results on the same axis."""
    rk4data = np.loadtxt(rk4Fn, delimiter=",")
    rkckdata = np.loadtxt(rkckFn, delimiter=",")
    rkf45data = np.loadtxt(rkf45Fn, delimiter=",")

    print("Data Loaded!")

    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Draw curve
    ax.plot(rk4data[0,:],rk4data[1,:],zs=rk4data[2,:], lw=1, label="RK4")
    ax.plot(rkckdata[0,:],rkckdata[1,:],zs=rkckdata[2,:], lw=1, label="RKCK")
    ax.plot(rkf45data[0,:],rkf45data[1,:],zs=rkf45data[2,:], lw=1, label="RKF45")

    ax.legend()

    fig.show()

plotOne( 'rkckCharged/0.1_1000.test/output.csv')

plotComparison('rk4Charged/0.1_1000.test/output.csv',
               'rkckCharged/0.1_1000.test/output.csv',
               'rkf45Charged/0.1_1000.test/output.csv')
