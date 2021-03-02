#include "csvbatchfileforqt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CSVBatchFileForQt w;
    w.setWindowTitle("电机标定数据处理器");
    w.show();
    return a.exec();
}
