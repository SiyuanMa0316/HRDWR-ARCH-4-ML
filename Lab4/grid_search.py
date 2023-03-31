import sys
import os
import pandas as pd
# n = len(sys.argv)
# assert(n==3)
# # define grids
# ArrayHeight = int(sys.argv[1])
# ArrayWidth = int(sys.argv[2])
ArrayHeight = 32
ArrayWidth = 32
IfmapSramSz = [128, 256, 512, 1024]
FilterSramSz = [32, 64, 128, 256, 512, 1024]
OfmapSramSz = [32, 64, 128, 256, 512, 1024]
IfmapOffset = 0
FilterOffset = 10000000
OfmapOffset = 20000000
Dataflow = 'ws'

# generate and run config files
length = len(IfmapSramSz)
count_config = 0

for i in IfmapSramSz:
    for j in FilterSramSz:
        for k in OfmapSramSz:
            # constraint 1
            if ((i+j+k) < 5000):
               #filename = "SCALE-Sim/configs/"+"lab4_"+ str(ArrayHeight)+"x" + str(ArrayWidth)+"x" + str(i)+"_"+str(j)+"_"+str(k)+".cfg"
                filename = "SCALE-Sim/configs/"+"lab4_"+ str(i)+"_"+str(j)+"_"+str(k)+".cfg"
                print(filename)
                f = open(filename, "w")
                f.write("[general]\n")
                f.write("run_name = \"lab4_")
                f.write(str(i))
                f.write("_")
                f.write(str(j))
                f.write("_")
                f.write(str(k))
                f.write("\"\n")
                f.write("\n[architecture_presets]\n")
                f.write("ArrayHeight:")
                f.write(str(ArrayHeight))
                f.write("\nArrayWidth:")
                f.write(str(ArrayWidth))
                f.write("\nIfmapSramSz:")
                f.write(str(i))
                f.write("\nFilterSramSz:")
                f.write(str(j))
                f.write("\nOfmapSramSz:")
                f.write(str(k))
                f.write("\nIfmapOffset:")
                f.write(str(IfmapOffset))
                f.write("\nFilterOffset:")
                f.write(str(FilterOffset))
                f.write("\nOfmapOffset:")
                f.write(str(OfmapOffset))
                f.write("\nDataflow:")
                f.write(Dataflow)
                f.close()
                os.system("python SCALE-Sim/scale.py -arch_config="+str(filename)+" -network=SCALE-Sim/topologies/Topology_lab4.csv")                
                count_config+=1


