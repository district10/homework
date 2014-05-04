# Three tpyes of cursor:
#   search-cursor, insert-cursor, update-cursor
# next(), reset()

import os, sys, arcpy, arcpy.mapping as mapping

# examples
##########################################################
# SearchCursor

# get all fields
with arcpy.da.SearchCursor("rec_sites", "*") as cursor:
	for row in sorted(cursor):
		print 'site name is ' + str(row[5])

# get specific fields
with arcpy.da.SearchCursor("roads", ("STREET_NAM", "LENGTH")) as cursor:
	for row in sorted(cursor):
		print 'Length of ' row[0] + ' is ' + str(row[1])

# get spacial data, and count time elapsed
start = time.clock()
with arcpy.da.SearchCursor("roads", ("SHAPE@XY"))  as cursor: # SHAPE@ to get all geometry info (oops, maybe a reference instead)
	for row in sorted(cursor):
		print row[0]
elapsed = (time.clock() - start)
print "Time Elapsed: " + str(elapsed) + ' seconds'# ===> Time Elapsed: 2.48893884997 seconds


#########################################################
# InseartCursor

count = arcpy.GetCount_management("destination")
print 'before inseartion, there are ' + str(count) + ' rows' # ===> before inseartion, there are 1 rows
# neowValue ObjectID(ObjectId), PointXY(Geometry), ID(long)
rowValues = [{2, (484144.40802979222, 224287.4112177222), 66}, {3, (484144.40802979333, 224287.4112177333), 68}]; # Works
# rowValues = [(2, (484144.40802979222, 224287.4112177222), 11), (3, (484144.40802979333, 224287.4112177333), 6)]; # Works too
fields = ["OBJECTID", "Shape", "Id"]
# fields = ("OBJECTID", "Shape", "Id") # Works too
with arcpy.da.InsertCursor("destination", fields) as cursor:
	for row in rowValues:
		cursor.insertRow(row)
count = arcpy.GetCount_management("destination")
print 'After inseartion, there are ' + str(count) + ' rows' # ===> after inseartion, there are 3 rows

##########################################################
# UpdateCursor

# modified a field
with arcpy.da.UpdateCursor("landuse", ("COUNT", "LANDUSE")) as cursor:
	for row in cursor:
		if row[0] > 100000:
			print 'before: ' + row[1] # ===> before: Forest
			row[1] = 'Too Much ' + row[1]
			cursor.updateRow(row)
			print 'after: ' + row[1] # ===> after: Too Much Forest

# delete a row
count = arcpy.GetCount_management("destination")
print 'before deletion, there are ' + str(count) + ' rows' # ===> before deletion, there are 3 rows
qry = '"Id" > 5'
with arcpy.da.UpdateCursor("destination", "*", qry) as cursor:
	for row in cursor:
		cursor.deleteRow()
count = arcpy.GetCount_management("destination")
print 'after deletion, there are ' + str(count) + ' rows' # ===> after deletion, there are 1 rows

