#ifndef MATLAB_H
#define MATLAB_H

#include <QList>

class Matlab
{
public:
    Matlab();
    /*
    % 功能：融合x,y两行向量(经典Dempster-Shafer组合公式)
    % x,y的格式形如[m1 m2 m3, ... , mk, m(全集), m(空集)]
    % 要求m1 m2 m3 ...之间互相无交集
    % m(全集)可不为0，表示不确定度
    % m(空集)肯定是0
    */
    //nx为x数组的长度
    static void DS_fusion(QList<qreal> &x, QList<qreal> &y);
};

#endif // MATLAB_H
