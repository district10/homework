path_base = 'X://DEMO2/';
path_gdb1 = path_base + 'test1.gdb/';
path_data1 = path_base + 'data/1/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb1;

# source data
path_business = path_data1 + 'Business.shp';
path_stations = path_data1 + 'Stations.shp';
path_streets = path_data1 + 'Streets.shp';
path_zoning = path_data1 + 'Zoning.shp';

# get document
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Data frame, aka "Layers" (empty by far)

# Add Layers
layer = mapping.Layer(path_business);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_stations);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_zoning);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_streets);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");

# set relative path
mxd.relativePaths = True;

# save a copy
mxd.saveACopy(path_base + 'test1-not-empty.mxd');