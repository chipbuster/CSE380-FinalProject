import numpy as np
import os
import matplotlib.pyplot as plt
import pickle
from matplotlib import rc
rc('font',**{'family':'sans-serif','sans-serif':['Helvetica']})
rc('text', usetex=True)
plt.rc('text', usetex=True)
plt.rc('font', family='serif')
import pdb

with open('rk4Charged/diffs.pickle', 'rb') as pklfile:
    rk4 = pickle.load(pklfile)

with open('rkckCharged/diffs.pickle', 'rb') as pklfile:
    rkck = pickle.load(pklfile)

with open('rkf45Charged/diffs.pickle', 'rb') as pklfile:
    rkf45 = pickle.load(pklfile)

print(rk4,rkck,rkf45)

steps = np.array([10,1,0.1,0.01,0.001,0.0001,0.00001])
rk4Err = np.array([ rk4[x] for x in steps ])
rkckErr = np.array([ rkck[x] for x in steps ])
rkf45Err = np.array([ rkf45[x] for x in steps ])

plt.loglog(steps,rk4Err)
