import os, sys, arcpy, arcpy.mapping as mapping

fcList = arcpy.ListFeatureClasses() # fc -> FeatureClass... What the fuck, troubled me alot 

for fc in fcList:
	print fc




