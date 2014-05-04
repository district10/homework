path_base = 'X://DEMO/';
path_gdb = path_base + 'demo.gdb/';
path_data = path_base + 'Spatial/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb;

# source data
path_elevation = path_data + 'elevation'
path_landuse = path_data + 'landuse'
path_school_site = path_data + 'School_site.shp'
path_destination = path_data +  'Stowe.gdb/destination'
path_rec_sites = path_data + 'Stowe.gdb/rec_sites'
path_roads = path_data + 'Stowe.gdb/roads'
path_schools = path_data + 'Stowe.gdb/schools'

# get document
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Data frame, aka "Layers" (empty by far)

# Add Layers
layer = mapping.Layer(path_elevation);
mapping.AddLayer(df, layer, "AUTO_ARRANGE")
layer = mapping.Layer(path_landuse);
mapping.AddLayer(df, layer, "AUTO_ARRANGE")
layer = mapping.Layer(path_school_site);
mapping.AddLayer(df, layer, "AUTO_ARRANGE")
layer = mapping.Layer(path_destination);
mapping.AddLayer(df, layer, "AUTO_ARRANGE")
layer = mapping.Layer(path_rec_sites);
mapping.AddLayer(df, layer, "AUTO_ARRANGE")
layer = mapping.Layer(path_roads);
mapping.AddLayer(df, layer, "AUTO_ARRANGE")
layer = mapping.Layer(path_schools);
mapping.AddLayer(df, layer, "AUTO_ARRANGE")
# Adding Layers Done, Fantastic~

# set relative path
mxd.relativePaths = True;

# save a copy
mxd.saveACopy(path_base + 'demo-not-empty.mxd');