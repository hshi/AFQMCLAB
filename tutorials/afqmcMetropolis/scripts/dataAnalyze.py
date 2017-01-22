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

print "\033[1m" "Manipulate data to generate other numerator files." "\033[0m"
subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/generateNumeratorHubbardSOC model_param", shell=True)

if os.path.isfile('./HNum.dat'):
    print "\033[1m" "Calculate HAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis HNum.dat den.dat HAverage.dat", shell=True)

if os.path.isfile('./KNum.dat'):
    print "\033[1m" "Calculate KAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis KNum.dat den.dat KAverage.dat", shell=True)

if os.path.isfile('./VNum.dat'):
    print "\033[1m" "Calculate VAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis VNum.dat den.dat VAverage.dat", shell=True)

if os.path.isfile('./RNum.dat'):
    print "\033[1m" "Calculate RAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis RNum.dat den.dat RAverage.dat", shell=True)

if os.path.isfile('./NupTotNum.dat'):
    print "\033[1m" "Calculate NupTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis NupTotNum.dat den.dat NupTotAverage.dat", shell=True)

if os.path.isfile('./NdnTotNum.dat'):
    print "\033[1m" "Calculate NdnTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis NdnTotNum.dat den.dat NdnTotAverage.dat",shell=True)

if os.path.isfile('./NTotNum.dat'):
    print "\033[1m" "Calculate NTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis NTotNum.dat den.dat NTotAverage.dat", shell=True)

if os.path.isfile('./SzTotNum.dat'):
    print "\033[1m" "Calculate SzTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis SzTotNum.dat den.dat SzTotAverage.dat", shell=True)

if os.path.isfile('./SplusTotNum.dat'):
    print "\033[1m" "Calculate SplusTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis SplusTotNum.dat den.dat SplusTotAverage.dat", shell=True)

if os.path.isfile('./SminusTotNum.dat'):
    print "\033[1m" "Calculate SminusTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis SminusTotNum.dat den.dat SminusTotAverage.dat", shell=True)

if os.path.isfile('./SxTotNum.dat'):
    print "\033[1m" "Calculate SxTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis SxTotNum.dat den.dat SxTotAverage.dat", shell=True)

if os.path.isfile('./SyTotNum.dat'):
    print "\033[1m" "Calculate SyTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumDenErrorAnalysis SyTotNum.dat den.dat SyTotAverage.dat", shell=True)

if os.path.isfile('./greenMatrixNum.dat'):
    print "\033[1m" "Calculate greenMatrixAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+
                     "/bin/NumArrayDenErrorAnalysis greenMatrixNum.dat den.dat greenMatrix_{1:d}_Average.dat {0:d} {1:d}".format(4*L*L, blockSize),shell=True)

if os.path.isfile('./NupNum.dat'):
    print "\033[1m" "Calculate NupAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis NupNum.dat den.dat Nup_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./NdnNum.dat'):
    print "\033[1m" "Calculate NdnAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis NdnNum.dat den.dat Ndn_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./NNum.dat'):
    print "\033[1m" "Calculate NAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis NNum.dat den.dat N_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SzNum.dat'):
    print "\033[1m" "Calculate SzAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SzNum.dat den.dat Sz_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SplusNum.dat'):
    print "\033[1m" "Calculate SplusAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SplusNum.dat den.dat Splus_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SminusNum.dat'):
    print "\033[1m" "Calculate SminusAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SminusNum.dat den.dat Sminus_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SxNum.dat'):
    print "\033[1m" "Calculate SxAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SxNum.dat den.dat Sx_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SyNum.dat'):
    print "\033[1m" "Calculate SyAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SyNum.dat den.dat Sy_{1:d}_Average.dat {0:d} {1:d}".format(L, blockSize),shell=True)

if os.path.isfile('./SzSzNum.dat'):
    print "\033[1m" "Calculate SzSzAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis SzSzNum.dat den.dat SzSz_{1:d}_Average.dat {0:d} {1:d}".format(L*L, blockSize),shell=True)

if os.path.isfile('./NTotNTotNum.dat'):
    print "\033[1m" "Calculate NTotNTotAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis NTotNTotNum.dat den.dat NTotNTot_{1:d}_Average.dat {0:d} {1:d}".format(L*L, blockSize),shell=True)

if os.path.isfile('./spinSpinNum.dat'):
    print "\033[1m" "Calculate spinSpinAverage." "\033[0m"
    subprocess.call( os.environ['AFQMCLAB_DIR']+"/bin/NumArrayDenErrorAnalysis spinSpinNum.dat den.dat spinSpin_{1:d}_Average.dat {0:d} {1:d}".format(L*L, blockSize),shell=True)
