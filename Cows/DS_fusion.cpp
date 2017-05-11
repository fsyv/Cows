#include "stdafx.h"
#include "DS_fusion.h"

#include <vector>

DS_fusion::DS_fusion()
{
}


DS_fusion::~DS_fusion()
{
}

/*
% 功能：融合x,y两行向量(经典Dempster-Shafer组合公式)
% x,y的格式形如[m1 m2 m3, ... , mk, m(全集), m(空集)]
% 要求m1 m2 m3 ...之间互相无交集
% m(全集)可不为0，表示不确定度
% m(空集)肯定是0
*/
void DS_fusion::solve(std::vector<double> &x, std::vector<double> &y)
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
	temp = temp == 0 ? temp : 0.00000001;

	for (int i = 0; i < size - 1; ++i)
	{
		x[i] = x[i] / temp;
	}
	x[size - 1] = 0.0;
}