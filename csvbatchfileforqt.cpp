#include "csvbatchfileforqt.h"

CSVBatchFileForQt::CSVBatchFileForQt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CSVBatchFileForQt)
{
    ui->setupUi(this);
    setText();
    connect(ui->Btn_PutIn      , SIGNAL(clicked()), this, SLOT(mathout()));
    connect(ui->Btn_MTPAAddress, SIGNAL(clicked()), this, SLOT(GetMTPAAddress()));
    connect(ui->Btn_PutInText  , SIGNAL(clicked()), this, SLOT(GetWeakMagneticAddress()));
    connect(ui->Btn_PutOutTxt  , SIGNAL(clicked()), this, SLOT(GetPutOutAddressAddress()));
}

CSVBatchFileForQt::~CSVBatchFileForQt()
{
    delete ui;
}

