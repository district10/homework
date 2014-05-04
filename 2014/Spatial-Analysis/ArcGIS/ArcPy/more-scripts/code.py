import sys, arcpy, arcpy.mapping as mapping

path_base = 'X://tutorial-example/'

path_elevation = path_base + 'Spatial/elevation'
path_landuse = path_base + 'Spatial/landuse'
path_school-site = path_base + 'Spatial/School_site.shp'
path_destination = path_base +  'Spatial/Stowe.gdb/destination'
path_rec_sites = path_base + 'Spatial/Stowe.gdb/rec_sites'
path_roads = path_base + 'Spatial/Stowe.gdb/roads'

path_in = path_base + 'tzx.mxd'
path_out = path_base + 'output.mxd'

arcpy.env.workspace  = path_base;

## arcpy.Buffer_analysis("schools", "school-buf", 50, "FULL", "ROUND", "ALL", "POSTSEC");

fields = arcpy.ListFields(path_landuse)

for fld in fields:
	print fld.name

mxd = mapping.MapDocument("CURRENT");
# mxd = mapping.MapDocument(path_in);

print mxd.title

frames = mapping.ListDataFrames(mxd);
for frame in frames:
	lastFrame = frame.name
	print frame.name
# ===> layers
	
layers = mapping.ListLayers(mxd);
for layer in layers:
	print layer.name
# ===> 
"""
destination
rec_sites
schools
roads
School_site
elevation
landuse
"""


for df in mapping.ListDataFrames(mxd):
	if (df.name == 'Layers'):
		layers = mapping.ListLayers(mxd, 'schools',df)
	for layer in layers:
		print "before query: ", layer.name
		Query = '"SCHLNAME" = \'Stowe Elementary School\''
                layer.DefinitionQuery = Query
                print "after query: ", layer.name
		df.extent = layer.getExtent()
		

mxd.title = 'new title'
mxd.saveACopy(outpath);


