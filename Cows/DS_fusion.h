#pragma once

class DS_fusion
{
public:
	DS_fusion();
	~DS_fusion();
	/*
	% ���ܣ��ں�x,y��������(����Dempster-Shafer��Ϲ�ʽ)
	% x,y�ĸ�ʽ����[m1 m2 m3, ... , mk, m(ȫ��), m(�ռ�)]
	% Ҫ��m1 m2 m3 ...֮�以���޽���
	% m(ȫ��)�ɲ�Ϊ0����ʾ��ȷ����
	% m(�ռ�)�϶���0
	*/
	//nxΪx����ĳ���
	static void solve(std::vector<double> &x, std::vector<double> &y);
};

