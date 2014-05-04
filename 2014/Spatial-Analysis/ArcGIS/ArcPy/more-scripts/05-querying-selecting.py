qry = '"SVCAREA" = \'North\''

qry = '"SVCAREA" LIKE \'N%\''

qry = '"SVCAREA" IS NULL'
qry = '"SVCAREA" IS NOT NULL'

AddFieldDelimiters(dataSource,field)



arcpy.env.workspace = "c:/ArcpyBook/data/CityOfSanAntonio.gdb"

try:
	fLayer = arcpy.MakeFeatureLayer_management("Burglary","BurglaryLayer") # make an in-memory copy of table
	tView = arcpy.MakeTableView_management("Crime2009Table", "Crime2009TView") # a view, not a table
	arcpy.SelectLayerByLocation_management (flayer, "COMPLETELY_WITHIN", "c:/ArcpyBook/Ch8/EdgewoodSD.shp")
except:
	print "An error occurred during creation"


arcpy.SelectLayerByAttribute_management()

print 'count is ' + str(arcpy.GetCount_management("School_site")) # ===> count is 1




