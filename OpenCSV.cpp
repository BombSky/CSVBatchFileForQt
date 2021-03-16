#include "csvbatchfileforqt.h"
#include <QLineEdit>
#include <QTextStream>
#include <QFileDialog>

#define MTPAAddress 0
#define FluxAddress 1


vector<vector<double>> CSVBatchFileForQt::OpenTheCSV(QString FileAddress)
{
    QString FluxWeakeningAddress = GetFileAddress(FileAddress);
    QFile* openFluxWeakeningFile = new QFile(FluxWeakeningAddress);
    QStringList* openFluxWeakeningLines = new QStringList;
    vector<vector<double>> csv;
    vector<double> hang;

    if (openFluxWeakeningFile->open(QIODevice::ReadOnly))
    {
        QTextStream* stream_text = new QTextStream(openFluxWeakeningFile);
        while (!stream_text->atEnd())			openFluxWeakeningLines->push_back(stream_text->readLine());
        delete(stream_text);
        for (int i = 1; i < openFluxWeakeningLines->size(); i++)
        {
            QString line = openFluxWeakeningLines->at(i);
            QStringList split = line.split(",");/*列数据*/
            hang.emplace_back(round_double(split.at(0).toDouble()       , 50, 100));	//转速    round_double(split.at(0). toDouble(), 50, 100)
            hang.emplace_back(abs(split.at(1).toDouble()));	//力矩
            hang.emplace_back(abs(split.at(2).toDouble()));	//Id_ref
            hang.emplace_back(abs(split.at(3).toDouble()));	//Iq_ref
            hang.emplace_back(round_double(Ismatch(hang[2], hang[3])    , 5 , 10 ));	//计算得出的Is电流
            hang.emplace_back(Thetamatch(hang[3], hang[4]));	//计算得出的夹角
            csv.emplace_back(hang);
            hang.clear();
        }
        openFluxWeakeningFile->close();
    }
    delete(openFluxWeakeningFile);
    delete(openFluxWeakeningLines);
    return csv;
}

void CSVBatchFileForQt::mathout()
{
    QString PutOutAddress = GetFileAddress("输出地址");
    QFile aFile(PutOutAddress);
    QTextStream aStream(&aFile);
    aFile.open(QIODevice::ReadWrite | QIODevice::Truncate);

    vector<vector<double>> MTPACsv = OpenTheCSV("角度地址");
    vector<vector<double>> csv = OpenTheCSV("弱磁地址");
    vector<vector<double>> merge;

    unsigned int p_csv = 0;
    while ( p_csv < csv.size())
    {
        unsigned int p_MTPA = 1;
        while ( p_MTPA < MTPACsv.size() )
        {
            if (csv[p_csv][5] == 0)
            {
                if (csv[p_csv][1] == 0)
                    merge.emplace_back(csv[p_csv]);		//这行如果遇到没有零位的弱磁跨转速会出问题，可能要单独弄一个头
                p_csv++;	//弱磁列表下一行
            }
            else if (csv[p_csv][5] == 90)
            {
                merge.emplace_back(csv[p_csv]);
                p_csv++;
                while (p_csv < csv.size()&&csv[p_csv][0] == csv[p_csv - 1][0])
                {
                    merge.emplace_back(csv[p_csv]);
                    p_csv++;
                }
                p_MTPA = MTPACsv.size();
            }
            else if (MTPACsv[p_MTPA][4] == csv[p_csv][4])	//相同电流时MTPA调速比较占优势的时候
            {
                while (p_MTPA < MTPACsv.size())
                {
                    if (MTPACsv[p_MTPA][5] > csv[p_csv][5] && MTPACsv[p_MTPA][4] == csv[p_csv][4])
                    {
                        merge.emplace_back(MTPACsv[p_MTPA]);
                        p_csv++;	//弱磁列表下一行
                        p_MTPA++;	//mtpa列表下一行
                    }
                    else if (MTPACsv[p_MTPA][4] == csv[p_csv + 1][4] && MTPACsv[p_MTPA + 1][4] != csv[p_csv + 1][4])	p_csv++;
                    else if (MTPACsv[p_MTPA][5] <= csv[p_csv][5])
                    {
                        while (p_csv < csv.size() && csv[p_csv][1] != 0 && csv[p_csv][5] != 0)
                        {
                            merge.emplace_back(csv[p_csv]);
                            p_csv++;
                        }
                        p_MTPA = MTPACsv.size();
                    }
                    else			p_MTPA++;	//mtpa列表下一行
                }
            }
            else if (MTPACsv[p_MTPA][4] == csv[p_csv + 1][4] && MTPACsv[p_MTPA + 1][4] != csv[p_csv + 1][4])			p_csv++;
            else if (MTPACsv[p_MTPA][4] < csv[p_csv][4]/* && MTPACsv[p_MTPA][5] > csv[p_csv][5]*/)		//当弱磁电流的最小电流大于MTPA时
            {
                merge.emplace_back(MTPACsv[p_MTPA]);
                p_MTPA++;
            }
            else
                p_MTPA++;	//mtpa列表下一行
        }
    }

    for (unsigned int i = MTPACsv.size(); i >= 1; i--)
        merge.emplace(merge.begin(), MTPACsv[i - 1]);

    vector<vector<double>> newCSV;
    vector<double> linshi;
//尾部添加空行
    linshi.emplace_back(merge[merge.size() - 2][0]);
    linshi.insert(linshi.end(), 3, 0);
    merge.emplace_back(linshi);
    linshi.clear();
//====================================================

    int stepSize = GetFileAddress("扭矩步进").toInt();
    int maxstep = GetFileAddress("最大扭矩").toInt();
    int currentTorque = 0;
    for (unsigned int i = 0; i < merge.size()-1; i++)
    {
        currentTorque = 0;
        while (currentTorque <= maxstep)
        {
            if(currentTorque > merge[i + 1][1])			i++;
            else if (currentTorque <= merge[i + 1][1])
            {
                linshi.emplace_back(merge[i][0]);	//转速
                linshi.emplace_back(currentTorque);	//扭矩
                linshi.emplace_back(marginCalculation(merge[i][1], merge[i + 1][1], merge[i][2], merge[i + 1][2], currentTorque));		//Id_ref
                linshi.emplace_back(marginCalculation(merge[i][1], merge[i + 1][1], merge[i][3], merge[i + 1][3], currentTorque));		//Iq_ref
                newCSV.emplace_back(linshi);
                linshi.clear();
                currentTorque += stepSize;
            }
            if (merge[i + 1][1] == 0)
                break;
        }
        while (currentTorque <= maxstep)
        {
            linshi.emplace_back(merge[i][0]);	//转速
            linshi.emplace_back(merge[i][1]);	//扭矩
            linshi.emplace_back(merge[i][2]);	//Id_ref
            linshi.emplace_back(merge[i][3]);	//Iq_ref
            newCSV.emplace_back(linshi);
            linshi.clear();
            currentTorque += stepSize;
        }
    }
    for (unsigned int i = 0; i < newCSV.size(); i++)
    {
        if (i == 0)			aStream << "\r\n" << "//" << "mtpa" << "\r\n";
        else if (newCSV[i][1] == 0)			aStream << "\r\n" << "//" << round_double(newCSV[i][0], 50, 100) << "rpm" << "\r\n";
        aStream << 	mymath(newCSV[i][2]) << ",\t" <<	mymath(newCSV[i][3]) << ",\t";
    }    
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHeaderData(0, Qt::Horizontal, "转速");
    model->setHeaderData(1, Qt::Horizontal, "扭矩");
    model->setHeaderData(2, Qt::Horizontal, "Id");
    model->setHeaderData(3, Qt::Horizontal, "Iq");

    for (unsigned int i = 0; i < newCSV.size(); i++)
    {
        model->setItem(i, 0, new QStandardItem(QString::number(newCSV[i][0], 'd' , 2)));
        model->setItem(i, 1, new QStandardItem(QString::number(newCSV[i][1], 'd' , 2)));
        model->setItem(i, 2, new QStandardItem(QString::number(newCSV[i][2], 'd' , 2)));
        model->setItem(i, 3, new QStandardItem(QString::number(newCSV[i][3], 'd' , 2)));
    }
    ui->TBV_PutOut->setModel(model);
    aFile.close();
}

void CSVBatchFileForQt::GetMTPAAddress()
{
    QString s = QFileDialog::getOpenFileName(
                this, "选择MTPA文件",
                "/",
                "MTPA表格文件 (*.csv *.CSV);; 所有文件 (*.*); ");
    ui->LE_MTPAAddress->setText(s);
    PutInMTPAWidgetView();
}

void CSVBatchFileForQt::GetWeakMagneticAddress()
{
    QString s = QFileDialog::getOpenFileName(this, "选择弱磁文件", "/", "弱磁表格文件 (*.csv *.CSV);; 所有文件 (*.*);");
    ui->LE_PutInText  ->setText(s);
    PutInWMWidgetView();
}
void CSVBatchFileForQt::GetPutOutAddressAddress()
{
    QString s = QFileDialog::getOpenFileName(this, "选择TXT文件", "/", "输出路径 (*.txt);; 所有文件 (*.*); ");
    ui->LE_PutOutText ->setText(s);
}
