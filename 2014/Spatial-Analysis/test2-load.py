path_base = 'X://DEMO2/';
path_gdb2 = path_base + 'test2.gdb/';
path_data2 = path_base + 'data/2/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb2;

# source data
path_midschool = path_data2 + 'MidSchol.shp';
path_counties = path_data2 + 'Counties.shp';
path_centract = path_data2 + 'Centract.shp';

# get document
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Dataframe, aka "Layers" (empty by far)

# Add Layers
layer = mapping.Layer(path_midschool);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_counties);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
layer = mapping.Layer(path_centract);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");
# set relative path
mxd.relativePaths = True;

# save a copy
mxd.saveACopy(path_base + 'test2-not-empty.mxd');