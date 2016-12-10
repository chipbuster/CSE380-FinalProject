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

print("Due to filesize limitations, required files for this program cannot go on GitHub")

with open('0.00001_10000000.test/output.csv.pickle', 'rb') as pklfile:
    refdata = pickle.load(pklfile)[0:3,:]


maxerr = {}

for r,d,fasd in os.walk('.'):
    for f in fasd:
        if f.split('.')[-1] == 'pickle':
            fname = os.path.join(r,f)
            with open(fname,'rb') as pfile:
                data = pickle.load(pfile)[0:3,:]
                h = 100.0 / np.shape(data)[1]

            maxdiff = 0

            arrSkip = int(round(h / 0.00001))
            j = 0
            k = 0
            while j < np.shape(data)[1]:
                if j % 1000 == 0:
                    print("Done",j,"of",np.shape(data)[1])
                diff = np.linalg.norm(data[:,j] - refdata[:,k])
                if diff > maxdiff:
                    maxdif = diff
                j += 1
                k += arrSkip

            maxerr[h] = maxdiff


with open('diffs.pickle','wb') as outfile:
    pickle.dump(maxerr,outfile)
