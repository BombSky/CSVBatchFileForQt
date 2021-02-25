#include "csvbatchfileforqt.h"

CSVBatchFileForQt::CSVBatchFileForQt(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CSVBatchFileForQt)
{
    ui->setupUi(this);
    connect(ui->Btn_PutIn, SIGNAL(clicked()), this, SLOT(mathout()));
}

CSVBatchFileForQt::~CSVBatchFileForQt()
{
    delete ui;
}

