# import modules
import sys, os, arcpy, arcpy.mapping as mapping
from arcpy import env
from arcpy.sa import *


# Set Base-path of 'Spatial'

path_base = 'X://TZX/';
workspace = path_base;

# Assign Path to Layer Files
path_elevation = path_base + 'Spatial/elevation';

path_out = path_base + '04.mxd';
# Get The Empty Document (you just newed)
mxd = mapping.MapDocument("CURRENT");
df = mapping.ListDataFrames(mxd)[0]; # Get First Dataframe, empty by now

# Add Layers
layer = mapping.Layer(path_elevation);
mapping.AddLayer(df, layer, "AUTO_ARRANGE");


Contour("elevation", "elevation100", 100, 0, 1);
Contour("elevation", "elevation500", 500, 0, 1);
Hillshade = Hillshade("elevation", 315, 45, "NO_SHADOWS", 1);
Back = Raster("elevation") >= 0;
maxPoint = BlockStatistics("elevation", NbrRectangle(11,11),"MAXIMUM", "NODATA");
SD = (Raster("elevation") - Raster("maxPoint")) == 0;
RE_SD = Reclassify("SD", "Value", RemapValue([[1, 1]]),"NODATA");
arcpy.RasterToPoint_conversion("RE_SD", "Out", "Value")

mxd.relativePaths = True
mxd.saveACopy(path_out)