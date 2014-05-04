# buffer, methods calling, etc
import arcpy, os, sys, arcpy.mapping as mapping

arcpy.env.workspace = ""

# Two ways to call methods
# method 1: arcpy.Clip_analysis(in_features,clip_features,out_feature_class)
# method 2: arcpy.analysis.Clip (in_features,clip_features,out_feature_class)

try:
 # Buffer areas of impact around major roads
 	streams = "Streams.shp"
	streamsBuffer = "StreamsBuffer.shp"
	distance = "2640 Feet"
	schools2mile = "Schools.shp"
	arcpy.Buffer_analysis(streams, streamsBuffer, distance,'FULL','ROUND','ALL')
	arcpy.MakeFeatureLayer_management(schools2mile, 'Schools2Mile_lyr')
	arcpy.SelectLayerByLocation_management('Schools2Mile_lyr', 'intersect', streamsBuffer)

except:
 print 'Error in script'



try:
 	print something_not_exist; 
except:
 	print 'Try Catch Except, You Deserve it'

