#include "matlab.h"

Matlab::Matlab()
{

}

void Matlab::DS_fusion(QList<qreal> &x, QList<qreal> &y)
{
    double temp = 0.0;

    if (x.size() != y.size())
    {
        return;
    }

    int size = x.size();
    for (int i = 0; i < size; ++i)
    {
        if (i == size - 1)
        {
            x[i] = x[i] * y[i];
        }
        else
        {
            x[i] = x[i] * y[i] + x[i] * y[size - 1] + y[i] * x[size - 1];
        }
        temp = temp + x[i];
    }

    //排除异常情况
    //如果temp等于0，给它赋值为一个很小的数
    temp = temp != 0 ? temp : 0.00000001;

    for (int i = 0; i < size - 1; ++i)
    {
        x[i] = x[i] / temp;
    }
    x[size - 1] = 0.0;
}
