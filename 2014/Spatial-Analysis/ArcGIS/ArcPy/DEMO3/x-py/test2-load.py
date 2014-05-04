path_base = 'X://DEMO2/';
path_gdb2 = path_base + 'test2.gdb/';
path_data2 = path_base + 'data/2/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb2;

# source data
path_business = path_data2 + 'Business.shp';
path_stations = path_data2 + 'Stations.shp';
path_streets = path_data2 + 'Streets.shp';
path_zoning = path_data2 + 'Zoning.shp';

# get document
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Dataframe, aka "Layers" (empty by far)

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
mxd.saveACopy(path_base + 'test2-not-empty.mxd');