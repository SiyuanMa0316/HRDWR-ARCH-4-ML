import sys
import os
import pandas as pd

# define grids
ArrayHeight = 256
ArrayWidth = 256
IfmapSramSz = [32, 64]
FilterSramSz = [32, 64, 128, 256, 512, 1024, 2048]
OfmapSramSz = [32, 64, 128, 256, 512, 1024, 2048]
IfmapOffset = 0
FilterOffset = 10000000
OfmapOffset = 20000000
Dataflow = 'ws'

# generate and run config files
length = len(IfmapSramSz)
count_config = 0
# parse all outputs
conf_ArrHeight = []
conf_ArrWidth = []
conf_IfmapSramSz = []
conf_FilterSramSz = []
conf_OfmapSramSz = []
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
            
            
            if((i+j+k) < 5000):
                name = str(foldername)+"Topology_lab4_max_bw.csv"
                df = pd.read_csv(name)
                # constraint 2
                if ( (df['\tMax DRAM IFMAP Read BW'][0]<=20) and (df['\tMax DRAM Filter Read BW'][0]<=20) and (df['\tMax DRAM OFMAP Write BW'][0]<=20) and (df['\tMax DRAM IFMAP Read BW'][1])<=20 and (df['\tMax DRAM Filter Read BW'][1]<=20) and (df['\tMax DRAM OFMAP Write BW'][1]<=20)):
                    conf_ArrHeight.append(ArrayHeight)
                    conf_ArrWidth.append(ArrayWidth)
                    conf_IfmapSramSz.append(i)
                    conf_FilterSramSz.append(j)
                    conf_OfmapSramSz.append(k)
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
                    cost.append(conv1_cycles[index]*(conv1_DRAM_IFMAP_Read_BW[index]+conv1_DRAM_Filter_Read_BW[index]+conv1_DRAM_OFMAP_Write_BW[index]) + conv2_cycles[index]*(conv2_DRAM_IFMAP_Read_BW[index]+conv2_DRAM_Filter_Read_BW[index]+conv2_DRAM_OFMAP_Write_BW[index]))
                
                    index+=1
            
# write to output.csv file
output_df = pd.DataFrame(
    {
        'Array Height': conf_ArrHeight,
        'Array Width': conf_ArrWidth,
        'IFMAP SRAM Size': conf_IfmapSramSz,
        'Filter SRAM Size': conf_FilterSramSz,
        'OFMAP SRAM Size': conf_OfmapSramSz,
        'conv1 cycles': conv1_cycles,
        'conv1 avg DRAM IFMAP Read BW': conv1_DRAM_IFMAP_Read_BW,
        'conv1 max DRAM IFMAP Read BW': conv1_Max_DRAM_IFMAP_Read_BW,
        'conv1 avg DRAM Filter Read BW': conv1_DRAM_Filter_Read_BW,
        'conv1 max DRAM Filter Read BW': conv1_Max_DRAM_Filter_Read_BW,
        'conv1 avg DRAM OFMAP Write BW': conv1_DRAM_OFMAP_Write_BW,
        'conv1 max DRAM OFMAP Write BW': conv1_Max_DRAM_OFMAP_Write_BW,
        'conv2 cycles': conv2_cycles,
        'conv2 avg DRAM IFMAP Read BW': conv2_DRAM_IFMAP_Read_BW,
        'conv2 max DRAM IFMAP Read BW': conv2_Max_DRAM_IFMAP_Read_BW,
        'conv2 avg DRAM Filter Read BW': conv2_DRAM_Filter_Read_BW,
        'conv2 max DRAM Filter Read BW': conv2_Max_DRAM_Filter_Read_BW,
        'conv2 avg DRAM OFMAP Write BW': conv2_DRAM_OFMAP_Write_BW,
        'conv2 max DRAM OFMAP Write BW': conv2_Max_DRAM_OFMAP_Write_BW,
        'cost': cost
    })
   
output_df.to_csv('output2.csv')

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