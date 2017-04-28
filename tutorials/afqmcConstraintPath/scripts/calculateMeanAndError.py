import subprocess
import sys
import os

if len(sys.argv) < 2:
    sys.exit("Missing arguments!!! Example: python calculateMeanAndError.py skipStep")
skipStep  = int( sys.argv[1] )

subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/doubleErrorAnalysis energySimple.dat energySimpleError.dat {0:d}".format(skipStep), shell=True)
subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis HNum.dat den.dat energyError.dat {0:d}".format(skipStep), shell=True)

