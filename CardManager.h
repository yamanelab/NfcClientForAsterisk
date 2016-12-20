#pragma once

#include <string>
#include <vector>
using namespace std;

class CardManager {
public:
	/**
	* �o�^�J�[�h�������[�h����
	* @param (_datapath) �o�^�J�[�h����ێ����Ă����t�@�C���p�X
	* @return =0 ����, <0 ���s
	*/
	int Load(string _datapath);
	
	/**
	* �J�[�h��񂩂�ID�𓾂�
	* @param (IDm) �J�[�hID�ԍ�
	* @param (PMm) �J�[�hPM�ԍ�
	* @return ID(����0�Ȃ疢�o�^)
	*/
	string GetIdFromCard(string IDm, string PMm);

	/**
	* �J�[�h����ID��o�^����
	* @param (id) ID
	* @param (IDm) �J�[�hID�ԍ�
	* @param (PMm) �J�[�hPM�ԍ�
	* @return =0 ����, <0 ���s
	*/
	int BindIdToCard(string id, string IDm, string PMm);
private:
	void WriteToDatapath();

	vector<string> vid, vIDm, vPMm;
	string datapath;
};