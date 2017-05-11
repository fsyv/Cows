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
% ���ܣ��ں�x,y��������(����Dempster-Shafer��Ϲ�ʽ)
% x,y�ĸ�ʽ����[m1 m2 m3, ... , mk, m(ȫ��), m(�ռ�)]
% Ҫ��m1 m2 m3 ...֮�以���޽���
% m(ȫ��)�ɲ�Ϊ0����ʾ��ȷ����
% m(�ռ�)�϶���0
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

	//�ų��쳣���
	//���temp����0��������ֵΪһ����С����
	temp = temp == 0 ? temp : 0.00000001;

	for (int i = 0; i < size - 1; ++i)
	{
		x[i] = x[i] / temp;
	}
	x[size - 1] = 0.0;
}