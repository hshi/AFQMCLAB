import subprocess
import sys
import os

if len(sys.argv) < 2:
    sys.exit("Missing arguments!!! Example: python dataAnalyze.py blockSize")
blockSize  = int( sys.argv[1] )

#Read Lattice Size
f = open("model_param", 'r')
firstLine =  f.readline()
L =  int(firstLine)
f.close()

if os.path.isfile('./HNum.dat'):
    print( "\033[1m" "Calculate HAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis HNum.dat den.dat HAverage.dat", shell=True)

if os.path.isfile('./KNum.dat'):
    print( "\033[1m" "Calculate KAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis KNum.dat den.dat KAverage.dat", shell=True)

if os.path.isfile('./VNum.dat'):
    print( "\033[1m" "Calculate VAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis VNum.dat den.dat VAverage.dat", shell=True)

if os.path.isfile('./RNum.dat'):
    print( "\033[1m" "Calculate RAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis RNum.dat den.dat RAverage.dat", shell=True)

if os.path.isfile('./NupTotNum.dat'):
    print( "\033[1m" "Calculate NupTotAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis NupTotNum.dat den.dat NupTotAverage.dat", shell=True)

if os.path.isfile('./NdnTotNum.dat'):
    print( "\033[1m" "Calculate NdnTotAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis NdnTotNum.dat den.dat NdnTotAverage.dat",shell=True)

if os.path.isfile('./SplusTotNum.dat'):
    print( "\033[1m" "Calculate SplusTotAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis SplusTotNum.dat den.dat SplusTotAverage.dat", shell=True)

if os.path.isfile('./SminusTotNum.dat'):
    print( "\033[1m" "Calculate SminusTotAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis SminusTotNum.dat den.dat SminusTotAverage.dat", shell=True)

if os.path.isfile('./NupNum.dat'):
    print( "\033[1m" "Calculate NupAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis NupNum.dat den.dat Nup_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./NdnNum.dat'):
    print( "\033[1m" "Calculate NdnAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis NdnNum.dat den.dat Ndn_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SplusNum.dat'):
    print( "\033[1m" "Calculate SplusAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SplusNum.dat den.dat Splus_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SminusNum.dat'):
    print( "\033[1m" "Calculate SminusAverage." "\033[0m" )
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SminusNum.dat den.dat Sminus_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)
