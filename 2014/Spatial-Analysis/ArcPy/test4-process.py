path_base = 'X://DEMO2/';
path_gdb4 = path_base + 'test4.gdb/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb3;


# Processing
arcpy.analysis.Buffer("Roads", "Roads_BUFFER", "500 Meter", "FULL", "ROUND", "ALL");

arcpy.analysis.Buffer("Roads", "Roads_BUFFER", "500 Meter", "FULL", "ROUND", "ALL");



arcpy.analysis.Union(("Water_BUFFER", "Roads_BUFFER"), "water_road", "ALL", gaps="GAPS")
