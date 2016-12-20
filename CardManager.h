#pragma once

#include <string>
#include <vector>
using namespace std;

class CardManager {
public:
	/**
	* 登録カード情報をロードする
	* @param (_datapath) 登録カード情報を保持しておくファイルパス
	* @return =0 成功, <0 失敗
	*/
	int Load(string _datapath);
	
	/**
	* カード情報からIDを得る
	* @param (IDm) カードID番号
	* @param (PMm) カードPM番号
	* @return ID(長さ0なら未登録)
	*/
	string GetIdFromCard(string IDm, string PMm);

	/**
	* カード情報にIDを登録する
	* @param (id) ID
	* @param (IDm) カードID番号
	* @param (PMm) カードPM番号
	* @return =0 成功, <0 失敗
	*/
	int BindIdToCard(string id, string IDm, string PMm);
private:
	void WriteToDatapath();

	vector<string> vid, vIDm, vPMm;
	string datapath;
};