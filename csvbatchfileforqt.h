#ifndef CSVBATCHFILEFORQT_H
#define CSVBATCHFILEFORQT_H

#include <QMainWindow>
#include "ui_csvbatchfileforqt.h"
#include <QString>
#include <QFile>
#include <iostream>
#include <vector>
#include <list>
#include <QMap>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class CSVBatchFileForQt; }
QT_END_NAMESPACE

class CSVBatchFileForQt : public QMainWindow
{
    Q_OBJECT

public:
    CSVBatchFileForQt(QWidget *parent = nullptr);
    ~CSVBatchFileForQt();
public:     //外部接口
    QString GetFileAddress(QString where);
//步进差值算法                [(跨度起始值，即前扭矩)，(跨度终点值，后扭矩)，  (要计算的值1)，     (要计算的值2)，     (步进)]
    double marginCalculation(double firstTorque, double secondTorque, double firstData, double secondData, int currentTorque);
//获取表
    vector<vector<double>> OpenTheCSV(QString FileAddress);
//四舍五入算法 参数表（原像，浮动量，精度）
    int round_double(double number, int excursion, int precision);
protected:
    int mymath(double a);                       //除以900
    int momentmatch(double a);                  //除以500
    int Ismatch(double Id_ref, double Iq_ref);  //is电流的计算
    int Thetamatch(double Iq_ref, int Is);      //角度计算
public slots:
    void mathout();

private:
    Ui::CSVBatchFileForQt *ui;
};
#endif // CSVBATCHFILEFORQT_H
