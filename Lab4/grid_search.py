import sys
import os
import pandas as pd

# define grids
ArrayHeight = 256
ArrayWidth = 256
IfmapSramSz = [32, 64, 128, 256, 512, 1024, 2048]
FilterSramSz = [32, 64, 128, 256, 512, 1024, 2048]
OfmapSramSz = [32, 64, 128, 256, 512, 1024, 2048]
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

# parse all outputs
conv1_Max_DRAM_IFMAP_Read_BW = []
conv1_Max_DRAM_Filter_Read_BW = []
conv1_Max_DRAM_OFMAP_Write_BW = []
conv2_Max_DRAM_IFMAP_Read_BW = []
conv2_Max_DRAM_Filter_Read_BW = []
conv2_Max_DRAM_OFMAP_Write_BW = []
conv1_cycles = []
conv2_cycles = []
conv1_DRAM_IFMAP_Read_BW = []
conv1_DRAM_Filter_Read_BW = []
conv1_DRAM_OFMAP_Write_BW = []
conv2_DRAM_IFMAP_Read_BW = []
conv2_DRAM_Filter_Read_BW = []
conv2_DRAM_OFMAP_Write_BW = []
cost = []
index = 0

for i in IfmapSramSz:
    for j in FilterSramSz:
        for k in OfmapSramSz:
            foldername = "outputs/"+"lab4_"+ str(i)+"_"+str(j)+"_"+str(k)+"/"
            
            name = str(foldername)+"Topology_lab4_max_bw.csv"
            df = pd.read_csv(name)
 
            # constraint 2
            if ((df['\tMax DRAM IFMAP Read BW'][0]<20) | (df['\tMax DRAM Filter Read BW'][0]<20) | (df['\tMax DRAM OFMAP Write BW'][0]<20) | (df['\tMax DRAM IFMAP Read BW'][1])<20 | (df['\tMax DRAM Filter Read BW'][1]<20) | (df['\tMax DRAM OFMAP Write BW'][1]<20)):
                # max BW
                conv1_Max_DRAM_IFMAP_Read_BW.append(df['\tMax DRAM IFMAP Read BW'][0])
                conv1_Max_DRAM_Filter_Read_BW.append(df['\tMax DRAM Filter Read BW'][0])
                conv1_Max_DRAM_OFMAP_Write_BW.append(df['\tMax DRAM OFMAP Write BW'][0])
                conv2_Max_DRAM_IFMAP_Read_BW.append(df['\tMax DRAM IFMAP Read BW'][1])
                conv2_Max_DRAM_Filter_Read_BW.append(df['\tMax DRAM Filter Read BW'][1])
                conv2_Max_DRAM_OFMAP_Write_BW.append(df['\tMax DRAM OFMAP Write BW'][1])
      
                # cycles
                name = str(foldername)+"Topology_lab4_cycles.csv"
                df = pd.read_csv(name)
                conv1_cycles.append(df['\tCycles'][0])
                conv2_cycles.append(df['\tCycles'][1])
 
            	# avg BW
                name = str(foldername)+"Topology_lab4_avg_bw.csv"
                df = pd.read_csv(name)
                conv1_DRAM_IFMAP_Read_BW.append(df['\tDRAM IFMAP Read BW'][0])
                conv1_DRAM_Filter_Read_BW.append(df['\tDRAM Filter Read BW'][0])
                conv1_DRAM_OFMAP_Write_BW.append(df['\tDRAM OFMAP Write BW'][0])
                conv2_DRAM_IFMAP_Read_BW.append(df['\tDRAM IFMAP Read BW'][1])
                conv2_DRAM_Filter_Read_BW.append(df['\tDRAM Filter Read BW'][1])
                conv2_DRAM_OFMAP_Write_BW.append(df['\tDRAM OFMAP Write BW'][1])
            
                # cost 
                cost = conv1_cycles[index]*(conv1_DRAM_IFMAP_Read_BW[index]+conv1_DRAM_Filter_Read_BW[index]+conv1_DRAM_OFMAP_Write_BW[index]) + conv2_cycles[index]*(conv2_DRAM_IFMAP_Read_BW[index]+conv2_DRAM_Filter_Read_BW[index]+conv2_DRAM_OFMAP_Write_BW[index])
            
                index+=1
            
# write to output.csv file
output_df = pd.DataFrame(
    {'conv1 cycles': conv1_cycles,
     'conv1 DRAM IFMAP Read BW': conv1_DRAM_IFMAP_Read_BW,
     'conv1 DRAM Filter Read BW': conv1_DRAM_Filter_Read_BW,
     'conv1 DRAM OFMAP Write BW': conv1_DRAM_OFMAP_Write_BW,
     'conv2 cycles': conv2_cycles,
     'conv2 DRAM IFMAP Read BW': conv2_DRAM_IFMAP_Read_BW,
     'conv2 DRAM Filter Read BW': conv2_DRAM_Filter_Read_BW,
     'conv2 DRAM OFMAP Write BW': conv2_DRAM_OFMAP_Write_BW,
     'cost': cost
    })
   
output_df.to_csv('output.csv')

'''print(conv1_Max_DRAM_IFMAP_Read_BW)
print(conv1_Max_DRAM_Filter_Read_BW)
print(conv1_Max_DRAM_OFMAP_Write_BW)
print(conv2_Max_DRAM_IFMAP_Read_BW)
print(conv2_Max_DRAM_Filter_Read_BW)
print(conv2_Max_DRAM_OFMAP_Write_BW)
print(conv1_cycles)
print(conv2_cycles)
print(conv1_DRAM_IFMAP_Read_BW)
print(conv1_DRAM_Filter_Read_BW)
print(conv1_DRAM_OFMAP_Write_BW)
print(conv2_DRAM_IFMAP_Read_BW)
print(conv2_DRAM_Filter_Read_BW)
print(conv2_DRAM_OFMAP_Write_BW)
print(cost)'''
