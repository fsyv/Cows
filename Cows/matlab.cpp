#include "matlab.h"

Matlab::Matlab()
{

}

void Matlab::DS_fusion(QList<real_t> &x, QList<real_t> &y)
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

//求均值
real_t Matlab::CalcAverage(const QList<real_t> &numbers)
{
    real_t sum = 0.0;
    for(auto num : numbers)
        sum += num;
    return sum / numbers.size();
}

/*
//求零均值序列
// numbers : 需要转换的序列
// aver这组序列的均值
*/
void Matlab::NorAverageSequence(QList<real_t> &numbers, real_t aver)
{
    for(int i = 0; i < numbers.size(); ++i)
        numbers[i] -= aver;
}

//前向差分
void Matlab::ForwardDifference(QList<real_t> &numbers)
{
    for(int i = 0; i < numbers.size() - 1; ++i)
        numbers[i] = numbers[i + 1] - numbers[i];

    numbers.takeLast();
}

//标准差  Standard Deviation
real_t Matlab::CalcStandardDeviation(const QList<real_t> &numbers)
{
    if(!numbers.size())
        return 0.0;

    real_t aver = CalcAverage(numbers);
    real_t sum = 0.0;

    for(auto num : numbers)
        sum += pow(num - aver, 2.0);

    return sqrt(sum / numbers.size());
}

//极差   全距(Range)，又称极差
real_t Matlab::CalcRange(const QList<real_t> &numbers)
{
    real_t max = 0.0;
    real_t min = numbers.first();

    for(int i = 0; i < numbers.size(); ++i)
    {
        if(numbers[i] > max)
            max = numbers[i];

        if(numbers[i] < min)
            min = numbers[i];
    }

    return max - min;
}

//峰度   Kurtosis
real_t Matlab::CalcKurtosis(const QList<real_t> &numbers)
{
    //采样不足
    if(numbers.size() < 2)
        return 0.0;

    real_t s = CalcStandardDeviation(numbers);

    //后面s作为除数，防止s等于0,
    s = s != 0.0 ? s : 0.00000000001;

    real_t aver = CalcAverage(numbers);

    real_t sum = 0.0;

    for(auto num : numbers)
        sum += pow(num - aver, 4.0);

    return sum / (numbers.size() - 1) / pow(s, 4.0);
}

QList<real_t> Matlab::AnalysisCredibilityDependS(const real_t &s)
{
    // s = matlab中的a
    ////////////////////////////////////////////////////////////////////
    /// 标准差a：
    /// 若a<1，则m(1)=0. 9, m (2)=0, m(θ)=0. 1；
    /// 若1 ≤a<2，则m(1)=[1一(a一1) ] X 0. 9, m (2)=[a一1] X0. 9, m(θ)=0. 1；
    /// 若a≥2，则m(1)=0, m (2)=0.9,m(θ)=0. 1 。
    ////////////////////////////////////////////////////////////////////

    QList<real_t> m;

    if(s < 1.0)
    {
        m.push_back(0.9);
        m.push_back(0.0);
        m.push_back(0.1);
    }
    else if(s >= 1.0 && s < 2)
    {
        m.push_back((2 - s) * 0.9);
        m.push_back((s - 1) * 0.9);
        m.push_back(0.1);
    }
    else
    {
        m.push_back(0);
        m.push_back(0.9);
        m.push_back(0.1);
    }

    return m;
}

QList<real_t> Matlab::AnalysisCredibilityDependRange(const real_t &range)
{
    // range = matlab中的b
    /////////////////////////////////////
    /// 极差b：
    /// 若b<5，则m(1)=0. 9, m (2)=0, m(θ)=0. 1;
    /// 若5 ≤ b<7，则m(1)=[1一(b一5) /2] X 0. 9, m (2)=[ (b一5)/2] X0. 9,m(θ)=0.1；
    /// 若b≥7，则m(1)=0, m (2)=0.9,m(θ)=0. 1。
    ////////////////////////////////////

    QList<real_t> m;

    if(range < 5.0)
    {
        m.push_back(0.9);
        m.push_back(0.0);
        m.push_back(0.1);
    }
    else if(range >= 5.0 && range < 7)
    {
        m.push_back((1 - (range - 5) / 2.0) * 0.9);
        m.push_back(((range - 5) / 2.0) * 0.9);
        m.push_back(0.1);
    }
    else
    {
        m.push_back(0);
        m.push_back(0.9);
        m.push_back(0.1);
    }

    return m;
}

QList<real_t> Matlab::AnalysisCredibilityDependKurtosis(const real_t &kurtosis)
{
    // kurtosis = matlab中的c
    /////////////////////////////////////
    /// 峰度c：
    /// 若c<2，则m(1)=0. 9, m (2)=0, m(θ)=0. 1;
    /// 若2 ≤ c<3，则m(1)=[1一(c一2) ] X 0. 9, m (2)=[c一2] X0. 9, m(θ)=0. 1
    /// 若c≥3，则m(1)=0, m (2)=0.9,m(θ)=0. 1。
    ////////////////////////////////////
    QList<real_t> m;

    if(kurtosis < 2.0)
    {
        m.push_back(0.9);
        m.push_back(0.0);
        m.push_back(0.1);
    }
    else if(kurtosis >= 2.0 && kurtosis < 3)
    {
        m.push_back((3 - kurtosis) * 0.9);
        m.push_back((kurtosis - 2) * 0.9);
        m.push_back(0.1);
    }
    else
    {
        m.push_back(0);
        m.push_back(0.9);
        m.push_back(0.1);
    }

    return m;
}
