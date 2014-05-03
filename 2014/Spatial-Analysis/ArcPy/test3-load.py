path_base = 'X://DEMO2/';
path_gdb3 = path_base + 'test3.gdb/';
path_data3 = path_base + 'data/3/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb3;

# source data
path_parcels = path_data3 + 'parcels.shp';
path_pools = path_data3 + 'vernal_pools.shp';

# get document
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Data frame, aka "Layers" (empty by far)

# Add Layers
layer = mapping.Layer(path_parcels);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_pools);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");

# set relative path
mxd.relativePaths = True;

# save a copy
mxd.saveACopy(path_base + 'test3-not-empty.mxd');