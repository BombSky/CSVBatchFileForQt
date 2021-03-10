#include "csvbatchfileforqt.h"

void CSVBatchFileForQt::PutInMTPAWidgetView()
{
    vector<vector<double>> MTPACsv = OpenTheCSV("角度地址");
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, "转速");
    model->setHeaderData(1, Qt::Horizontal, "扭矩");
    model->setHeaderData(2, Qt::Horizontal, "Id");
    model->setHeaderData(3, Qt::Horizontal, "Iq");

    for (unsigned int i = 0; i < MTPACsv.size(); i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(MTPACsv[i][0], 'd' , 2)));
        model->setItem(i, 1, new QStandardItem(QString::number(MTPACsv[i][1], 'd' , 2)));
        model->setItem(i, 2, new QStandardItem(QString::number(MTPACsv[i][2], 'd' , 2)));
        model->setItem(i, 3, new QStandardItem(QString::number(MTPACsv[i][3], 'd' , 2)));
    }
    ui->TBV_MTPA->setModel(model);
}

void CSVBatchFileForQt::PutInWMWidgetView()
{
    vector<vector<double>> csv     = OpenTheCSV("弱磁地址");
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, "转速");
    model->setHeaderData(1, Qt::Horizontal, "扭矩");
    model->setHeaderData(2, Qt::Horizontal, "Id");
    model->setHeaderData(3, Qt::Horizontal, "Iq");

    for (unsigned int i = 0; i < csv.size(); i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(csv[i][0], 'd', 2)));
        model->setItem(i, 1, new QStandardItem(QString::number(csv[i][1], 'd', 2)));
        model->setItem(i, 2, new QStandardItem(QString::number(csv[i][2], 'd', 2)));
        model->setItem(i, 3, new QStandardItem(QString::number(csv[i][3], 'd', 2)));
    }
    ui->TBV_WM->setModel(model);
}
