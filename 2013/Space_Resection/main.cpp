#include <QCoreApplication>
#include "matrix.h"
#include "point_3d.h"
#include "space_resection_tzx.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    space_resection_tzx * test = new space_resection_tzx();

    return a.exec();
}
