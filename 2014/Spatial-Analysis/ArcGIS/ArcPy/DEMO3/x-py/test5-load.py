path_base = 'X://DEMO2/';
path_gdb5 = path_base + 'test5.gdb/';
path_data5 = path_base + 'data/5/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb5;

# source data
path_streets = path_data5 + 'Streets.shp';
path_streets_nd = path_data5 + 'Streets_ND.nd';
path_junctions = path_data5 + 'Streets_ND_Junctions.shp';

# get document
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Data frame, aka "Layers" (empty by far)

# Add Layers
layer = mapping.Layer(path_streets);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_streets_nd);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_junctions);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");

# set relative path
mxd.relativePaths = True;

# save a copy
mxd.saveACopy(path_base + 'test5-not-empty.mxd');