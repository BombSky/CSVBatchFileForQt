#include "csvbatchfileforqt.h"
#include <cmath>
#define M_PI       3.14159265358979323846

int CSVBatchFileForQt::Thetamatch(double Iq_ref, int Is)
{
    if (Is == 0)	return 0;
    return acos(abs(Iq_ref)/Is) * 180/M_PI;
}

int CSVBatchFileForQt::Ismatch(double Id_ref, double Iq_ref)
{
    return sqrt(Id_ref * Id_ref + Iq_ref * Iq_ref);
}

int CSVBatchFileForQt::mymath(double a)
{
    return a = (a * 32768) / (ui->comboBox->currentText().toInt());
}
int CSVBatchFileForQt::momentmatch(double a)
{
    return a = a / 500 * 32768;
}

int CSVBatchFileForQt::round_double(double number, int excursion, int precision)
{
    int a = (number + excursion) / precision;
    return a * precision;
}
double CSVBatchFileForQt::marginCalculation(double firstTorque, double secondTorque, double firstData, double secondData, int currentTorque)
{
    return ((secondData - firstData) / (secondTorque - firstTorque)) * (currentTorque - firstTorque) + firstData;
}
