path_base = 'X://DEMO2/';
path_gdb1 = path_base + 'test1.gdb/';
path_data1 = path_base + 'data/1/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb1;

# Processing
Qry = '"STR" = \'140\'';

arcpy.SelectLayerByAttribute_management("Streets", "NEW_SELECTION", Qry);

arcpy.SelectLayerByLocation_management("Stations", "WITHIN_A_DISTANCE", "Streets", "1000 Feet", "SUBSET_SELECTION");

count = arcpy.GetCount_management("Stations");
# Ques: How many sites, and their name?
# Ans: 
print 'There are ' + str(count) + ' Stations are ... within 140 feets from 140 road'; # ===> 7, ...
with arcpy.da.SearchCursor("Stations", ("NAME")) as cursor:
	for row in sorted(cursor):
		print row[0] # have a better looking than `print row'


arcpy.SelectLayerByLocation_management("Business", "WITHIN_A_DISTANCE", "Stations", "1320 Feet", "SUBSET_SELECTION");
count = arcpy.GetCount_management( "Business");
print count # ==> 100