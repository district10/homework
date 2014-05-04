import os, sys, arcpy, arcpy.mapping as mapping

for row in arcpy.da.SearchCursor("rec_sites", ["OID@", "SHAPE@"]):
 	print("Feature {0}:".format(row[0])) # Like C#..., I just learned it.
 	# ==> Feature {1..29}:
 	partnum = 0
	for part in row[1]
 		print("Part {0}:".format(partnum))
 		for pnt in part: 	
 			if pnt:
 				print("{0}, {1}".format(pnt.X, pnt.Y))
 			else:	
 				print("Interior Ring:")
 		partnum += 1

# wrong again!!!



#==============================================
# History of Trail and Error
# for row in arcpy.da.SearchCursor("rec_sites", ["OID@", "SHAPE@"]):
# 	print("Feature {0}:".format(row[0])) # Like C#..., I just learned it.
# 	for part in row[1]:
# 		partnum = 0
# 		# Print the part number
# 		print("Part {0}:".format(partnum)) # ===> TypeError: 'PointGeometry' object is not iterable
#	print row[1][0] # ===> TypeError: 'PointGeometry' object does not support indexing
