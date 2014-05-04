path_base = 'X://DEMO2/';
path_gdb3 = path_base + 'test3.gdb/';
path_data3 = path_base + 'data/3/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb3;


# Processing


# arcpy.analysis.Buffer("vernal_pools", "vernal_pools_Buffer.shp", "2000 Feets", "FULL", "ROUND", "ALL");
# Not Feets, it's Feet
arcpy.analysis.Buffer("vernal_pools", "vernal_pools_Buffer.shp", "2000 Feet", "FULL", "ROUND", "ALL");
arcpy.SelectLayerByLocation_management("parcels", "INTERSECT", "vernal_pools_Buffer");

arcpy.MakeFeatureLayer_management("parcels", "parcels_out") # 靠，直接导出，就是导出 selected features，查了我半天
