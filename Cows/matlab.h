#ifndef MATLAB_H
#define MATLAB_H

#include <QList>

typedef qreal real_t;

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
    static void DS_fusion(QList<real_t> &x, QList<real_t> &y);

    //求均值
    static real_t CalcAverage(const QList<real_t> &numbers);

    /*
    //求零均值序列
    // numbers : 需要转换的序列
    // aver这组序列的均值
    */
    static void NorAverageSequence(QList<real_t> &numbers, real_t aver);

    //前向差分
    static void ForwardDifference(QList<real_t> &numbers);

    //标准差  Standard Deviation
    static real_t CalcStandardDeviation(const QList<real_t> &numbers);

    //极差   全距(Range)，又称极差
    static real_t CalcRange(const QList<real_t> &numbers);

    //峰度   Kurtosis
    static real_t CalcKurtosis(const QList<real_t> &numbers);
};

#endif // MATLAB_H
