import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import pdb

def plotOne(filename):
    """Plot the data in a single file"""
    data = np.loadtxt(filename, delimiter=",")
    plt.plot(data[0,:],data[1,:])
    plt.show()

def plotNumVsAn(numericalFn, analyticFn, params):
    """Plot the numerical and analytic solutions on the same graph"""

    (method, stepSz,nSteps) = params

    nData = np.loadtxt(numericalFn, delimiter=",")
    aData = np.loadtxt(analyticFn, delimiter=",")

    nPts = np.shape(nData)[1]

    # Sanity check: are time values the same?
    assert np.amax(nData[1,:] - aData[1,:]) < 1e-7

    numPtsInPlot = 100
    skip = nPts // numPtsInPlot

    time = nData[1,::skip]
    nVals = nData[0,::skip]
    aVals = aData[0,::skip]

    plt.plot(time, nVals, 'r--', label="Numeric")
    plt.plot(time, aVals, 'b+', label="Analytic")
    plt.xlabel(r't')
    plt.xlabel(r'x(t)')
    plt.legend(loc='upper left')
    plt.suptitle(r"Trajectory for  $\frac{dx}{dt} = 4 \sin(x(t)) + 2 t^3$",fontsize=18)
    plt.title("Method: %s | Step size: %d | Num Steps: %d" % params)
    plt.show()

# Example output runs
# A decent output: step size 10, 1000 steps, Euler Method

plotNumVsAn('./data/10_1e3/output.csv','./data/10_1e3/analytic.csv', ("Euler", 10, 1000))

# An output with 10x the step size, same range
plotNumVsAn('./data/100_100/output.csv','./data/100_100/analytic.csv', ("Euler", 100, 100))

# An RK4 plot
plotNumVsAn('./data/0.1_1e4_rk4/output.csv','./data/0.1_1e4_rk4/analytic.csv', ("RK4", 0.1, 10000))
