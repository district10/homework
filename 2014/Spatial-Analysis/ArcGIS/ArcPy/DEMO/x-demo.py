path_base = 'X://DEMO/';
path_gdb = path_base + 'demo.gdb/';
path_data = path_base + 'Spatial/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;
from arcpy.sa import *
from arcpy.mapping import *


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

####################################################################################

for df in mapping.ListDataFrames(mxd):
	if (df.name == 'Layers'): # that's for sure
		layers = mapping.ListLayers(mxd, 'elevation', df);
		arcpy.env.extent = layers[0].getExtent(); # set extent to whole map, that's what we want

arcpy.CheckOutExtension("Spatial");

# Execute HillShade
outHillShade = arcpy.sa.Hillshade("elevation", 180, 75, "SHADOWS", 1); # done
outHillShade.save(path_gdb + 'HillShade');

# fine
Slope = arcpy.sa.Slope("elevation", "DEGREE");
Slope.save(path_gdb + 'Slope');

# Distance to Rec Site
DistanceRec = arcpy.sa.EucDistance("rec_sites", cell_size = 30);
DistanceRec.save(path_gdb + 'DistanceRec');

# Distance to School
DistanceSch = arcpy.sa.EucDistance("schools", cell_size = 30);
DistanceSch.save(path_gdb + 'DistanceSch');

# this is it, Reclassify
ReclassSlope = arcpy.sa.Reclassify("Slope", "Value",
						RemapRange([[0,8,1],[8,15,2],[15,23,3],[23,31,4],[31,39,5],
									[39,46,6],[46,54,7],[54,62,8],[62,69,9],[69,78,10]]), "NODATA"); # this is what we want~
ReclassSlope.save(path_gdb + 'ReclassSlope');
									
ReclassRec = arcpy.sa.Reclassify("DistanceRec", "Value",
						RemapRange([[0,1349,1],[1349,2698,2],[2698,4046,3],[4046,5395,4],[5395,6744,5],
									[6744,8093,6],[8093,9441,7],[12139,13488,8],[10790,12139,9],[12139,13488,10]]), "NODATA"); # good~
ReclassRec.save(path_gdb + 'ReclassRec');
									
# seem we need a function to help us out
def partition (beg, end, num):
	pace = ( end - beg ) / num + 1;
	return [[beg+pace*i, beg+pace*i+pace] for i in xrange(num)] # shit, I used 'from' once... terrible mistake

range = partition (0, 16928, 10);
ReclassSch = arcpy.sa.Reclassify("DistanceSch", "Value",
						RemapRange(range), "NODATA");
ReclassSch.save(path_gdb + 'ReclassSch');


with arcpy.da.SearchCursor("landuse", ("LANDUSE")) as cursor:
	for row in sorted(cursor):
		print row[0]
