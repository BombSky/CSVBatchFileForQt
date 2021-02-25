#include "csvbatchfileforqt.h"
#include <QLineEdit>
#include <map>

QString CSVBatchFileForQt::GetFileAddress(QString where)
{
    map<QString, QString>* Address = new map<QString, QString>;
    *Address = {
        {"弱磁地址", ui->LE_PutInText   ->text()},
        {"输出地址", ui->LE_PutOutText  ->text()},
        {"扭矩步进", ui->LE_Step        ->text()},
        {"最大扭矩", ui->LE_MaxTorque   ->text()},
        {"角度地址", ui->LE_MTPAAddress ->text()}
    };
    QString dizhi = Address->find(where)->second;
    delete(Address);
    return dizhi;
}
