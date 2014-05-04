path_base = 'X://DEMO2/';
path_gdb1 = path_base + 'test1.gdb/';
path_data1 = path_base + 'data/1/';

# import modules
import sys, os, arcpy;
import arcpy.mapping as mapping;

# set workspace 
arcpy.env.workspace = path_gdb1;

# Processing

arcpy.SelectLayerByAttribute_management("Streets", "NEW_SELECTION", '"STR" = \'I40\''); # 靠，看成了140 。。。
# ==> 30 features selected


arcpy.SelectLayerByLocation_management("Stations", "WITHIN_A_DISTANCE", "Streets", "1000 Feet", "NEW_SELECTION");

count = arcpy.GetCount_management("Stations");
# Ques: How many sites, and their name?
# Ans: 
print 'There are ' + str(count) + ' Stations are ... within 140 feets from 140 road'; # ===> 2, ...
with arcpy.da.SearchCursor("Stations", ("NAME")) as cursor:
	for row in sorted(cursor):
		print row[0] # have a better looking than `print row'


arcpy.SelectLayerByLocation_management("Business", "WITHIN_A_DISTANCE", "Stations", "1320 Feet", "NEW_SELECTION");
count = arcpy.GetCount_management( "Business"); # ==> 19

print "有 " + str(count) + " 个商业站点位于已选中的加油站 1320 英尺以内"

# =================================================================================================

arcpy.SelectLayerByAttribute_management("Zoning", "NEW_SELECTION", '"DESCRIPTIO" = \'DRAIN\'');

arcpy.SelectLayerByLocation_management("Zoning", "BOUNDARY_TOUCHES", "Zoning"); # ==> 37





juris= [row[0] for row in arcpy.da.SearchCursor("Zoning", ("JURISDICTI"))];

JURIS=set(juris);
# >>> print JURIS
# set([u'COUNTY', u'CITY'])

acres= [row[0] for row in arcpy.da.SearchCursor("Zoning", ("ACRES"))];

key-val= [(row[0], row[1]) for row in arcpy.da.SearchCursor("Zoning", ("JURISDICTI", "ACRES"))]
# how to use dict?


