# import modules
import sys, os, arcpy, arcpy.mapping as mapping

# Set Base-path of 'Spatial'

path_base = 'X://TZX/'

mxd = mapping.MapDocument("CURRENT");
# >>> arcpy.env.workspace
# u'X:\\TZX\\00-empty.gdb'
for el in mapping.ListLayoutElements(mxd):
	if el.name != '':
		print el.name # ===> Layers

for el in mapping.ListLayoutElements(mxd):
	print el.name # ===> Layers

print mapping.ListPrinterNames() # ===> None

# for df in mapping.ListDataFrames(mxd):
# 	mapping.PrintMap(mxd, "", df) # ===> Told you, there is no printer

mapping.ExportToPDF(mxd, path_base + 'before.pdf');

for df in mapping.ListDataFrames(mxd):
	if (df.name == 'Layers'):
		layers = mapping.ListLayers(mxd, 'schools',df)
	for layer in layers:
		print "before query: ", layer.name
		Query = '"SCHLNAME" = \'Stowe Elementary School\''
                layer.DefinitionQuery = Query
                print "after query: ", layer.name
		df.extent = layer.getExtent()

mapping.ExportToPDF(mxd, path_base + 'after.pdf'); # ===> seems no difference...
mapping.ExportToPNG(mxd, path_base + 'exported.png')
mapping.ExportToSVG(mxd, path_base + 'exported.svg')

toDelete = path_base + 'exported.svg'
if os.path.exists(toDelete):
	os.remove(toDelete) # ===> Deleted 

pdfPath = path_base + 'newly-created.pdf'
pdfDoc = mapping.PDFDocumentCreate(pdfPath)
pdfDoc.appendPages(path_base + 'before.pdf')
pdfDoc.appendPages(path_base + 'after.pdf')
pdfDoc.saveAndClose()

mxd.saveACopy(path_base + '02.mxd');
