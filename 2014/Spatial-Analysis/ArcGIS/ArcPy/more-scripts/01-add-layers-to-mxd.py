path_base = 'X://TZX/'

# import modules
import sys, os, arcpy
from arcpy.mapping import *
from arcpy.sa import *
from arcpy import env  

arcpy.env.workspace = path_base

# Assign Path to Layer Files
path_elevation = path_base + 'Spatial/elevation'
path_landuse = path_base + 'Spatial/landuse'
path_school_site = path_base + 'Spatial/School_site.shp'

path_destination = path_base +  'Spatial/Stowe.gdb/destination'
path_rec_sites = path_base + 'Spatial/Stowe.gdb/rec_sites'
path_roads = path_base + 'Spatial/Stowe.gdb/roads'
path_schools = path_base + 'Spatial/Stowe.gdb/schools'


path_out = path_base + '01-not-empty.mxd'
# Get The Empty Document (you just newed)
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0] # Get First Dataframe, empty by now

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
# Adding Layers Done, Fantantic~

mxd.relativePaths = True
mxd.saveACopy(path_out)