import pickle
import sys
import numpy as np

infile = sys.argv[1]
outfile = sys.argv[2]

print("Transferring " + infile + " into " + outfile)

data = np.loadtxt(infile, delimiter=",")

with open(outfile,'wb') as pfile:
    pickle.dump(data,pfile)
