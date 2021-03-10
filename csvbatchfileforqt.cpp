#include "csvbatchfileforqt.h"
#include <QKeyEvent>

CSVBatchFileForQt::CSVBatchFileForQt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CSVBatchFileForQt)
{
    ui->setupUi(this);
    setText();
    setComboBox();
    connect(ui->Btn_PutIn      , SIGNAL(clicked()), this, SLOT(judge                  ));
    connect(ui->Btn_MTPAAddress, SIGNAL(clicked()), this, SLOT(GetMTPAAddress         ));
    connect(ui->Btn_PutInText  , SIGNAL(clicked()), this, SLOT(GetWeakMagneticAddress ));
    connect(ui->Btn_PutOutTxt  , SIGNAL(clicked()), this, SLOT(GetPutOutAddressAddress));
}

void CSVBatchFileForQt::keyPressEvent(QKeyEvent *e)
{
    if(Qt::Key_Enter) mathout();
    e->key();
}

CSVBatchFileForQt::~CSVBatchFileForQt()
{
    delete ui;
}

void CSVBatchFileForQt::judge()
{
//设置控件为空时不能执行
    if (!QString(ui->LE_MTPAAddress  ->text()).isEmpty() &&
        !QString(ui->LE_PutInText    ->text()).isEmpty() &&
        !QString(ui->LE_PutOutText   ->text()).isEmpty() &&
        !QString(ui->LE_MaxTorque    ->text()).isEmpty() &&
        !QString(ui->LE_Step         ->text()).isEmpty())

        return mathout();
}

