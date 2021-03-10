#include "csvbatchfileforqt.h"
#include <QTableView>

void CSVBatchFileForQt::setText()
{
    QFont* font = new QFont();
    font->setPointSize(26);
    font->setFamily("微软雅黑");
    ui->LB_HPText->setFont(*font);
    delete (font);
    QFont* otherFont = new QFont();
    otherFont->setPointSize(10);
    otherFont->setFamily("微软雅黑");
    ui->Btn_PutIn->setFont(*otherFont);
    ui->Btn_PutInText->setFont(*otherFont);
    ui->Btn_PutOutTxt->setFont(*otherFont);
    ui->Btn_MTPAAddress->setFont(*otherFont);
    ui->LE_Step->setFont(*otherFont);
    ui->LE_MaxTorque->setFont(*otherFont);
    ui->LE_PutInText->setFont(*otherFont);
    ui->LE_PutOutText->setFont(*otherFont);
    ui->LE_MTPAAddress->setFont(*otherFont);
    delete (otherFont);
}

void CSVBatchFileForQt::setComboBox()
{
    QStringList *strList = new QStringList();
    *strList << "900" << "1000";
    ui->comboBox->addItems(*strList);
}
