path_base = 'X://DEMO2/';
path_gdb4 = path_base + 'test4.gdb/';
path_data4 = path_base + 'data/4/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb4;

# source data
path_roads = path_data4 + 'Roads.shp';
path_study = path_data4 + 'study.shp';
path_water = path_data4 + 'Water.shp';

# get document
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Data frame, aka "Layers" (empty by far)

# Add Layers
layer = mapping.Layer(path_roads);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_study);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_water);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");

# set relative path
mxd.relativePaths = True;

# save a copy
mxd.saveACopy(path_base + 'test4-not-empty.mxd');