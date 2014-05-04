import os, sys, arcpy, arcpy.mapping as mapping

# Try and Error
# arcpy.AddField_management("destination", 'example-field', "TEXT")
# ===> WARNING 000304: Renamed field example-field to example_field
# and then we learn

# So we use this revised version of AddField
arcpy.AddField_management("destination", 'field_example', "TEXT") 
# ===> 
#     Adding field_example to destination...
#     Succeeded at Tue Apr 22 14:15:54 2014 (Elapsed Time: 0.02 seconds)

# To Do
# edit = arcpy.da.Editor