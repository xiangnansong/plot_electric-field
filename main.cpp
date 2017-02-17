#include <QtWidgets/qapplication.h>
#include "Field.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Field field;
    field.show();
    return a.exec();

}