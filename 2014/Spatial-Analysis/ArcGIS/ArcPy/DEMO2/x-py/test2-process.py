path_base = 'X://DEMO2/';
path_gdb2 = path_base + 'test2.gdb/';
path_data2 = path_base + 'data/2/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb2;

# Processing

arcpy.SelectLayerByAttribute_management("Centract", "NEW_SELECTION", '"POP_90" < 5786.054054');
# arcpy.SelectLayerByLocation_management("Centract", "COMPLETELY_CONTAINS", "MidSchol");
arcpy.SelectLayerByLocation_management("Centract", "COMPLETELY_CONTAINS", "MidSchol", selection_type="SUBSET_SELECTION");


arcpy.SelectLayerByAttribute_management("Counties", "NEW_SELECTION", '"Name" = \'Cobb County\'');
arcpy.SelectLayerByLocation_management("Centract", "COMPLETELY_WITHIN", "Counties", selection_type="SUBSET_SELECTION");

count = arcpy.GetCount_management( "Centract");
print count
percap= [row[0] for row in arcpy.da.SearchCursor("Centract", ("PER_CAPINC"))];
print percap # ===> [19867.69921875, 12793.2998046875, 17364.80078125]

