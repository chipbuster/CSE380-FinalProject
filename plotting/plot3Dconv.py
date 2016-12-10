import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import pdb

# Data manually input by scanning logs--not scalable :(

eulerStepSize = np.array([100,10,1,0.1,0.01,0.001,0.0001])
eulerErrors = np.array([6.855e10, 9.65399e9, 9.96504e8, 9.9965e7, 9.99965e6, 999985, 99875.1])

rk4StepSize = np.array([100, 10, 1, 0.1, 0.01, 0.001, 0.0001])
rk4Errors   = np.array([1409.68, 4.92375, 0.00292969, 0.114914,0.46283, 11.7455, 125.014])

# Calculate fit
eSlope, eIntercept = np.polyfit(np.log(eulerStepSize), np.log(eulerErrors), 1)
rSlope, rIntercept = np.polyfit(np.log(rk4StepSize[0:3]), np.log(rk4Errors[0:3]), 1)

print(eSlope, eIntercept, rSlope, rIntercept)

# Create points
eulerLinearFitY = np.power(eulerStepSize, eSlope) * np.power(2.718,eIntercept)
rk4LinearFitY = np.power(rk4StepSize, rSlope) * np.power(2.718,rIntercept)

plt.loglog(eulerStepSize,eulerErrors,'r+',label="Euler")
plt.loglog(rk4StepSize,rk4Errors,'bx',label='rk4')
plt.loglog(eulerStepSize, eulerLinearFitY, 'r--', label="Euler Best-Fit")
plt.loglog(rk4StepSize, rk4LinearFitY, 'b--', label="RK4 Best-Fit")
plt.title("Log-Log Plots of Euler and Runge-Kutta 4 error")
plt.xlabel('log(step size)')
plt.ylabel('log(max error)')
plt.legend(loc='lower right')

plt.annotate('m = %f'%rSlope, xy=(1, 0.003), xytext=(0.03, 1e-8),
            arrowprops=dict(facecolor='black', shrink=0.05),
            )
plt.annotate('m = %f'%eSlope, xy=(1, 1e9), xytext=(0.1, 1e2),
            arrowprops=dict(facecolor='black', shrink=0.05),
            )
plt.show()
