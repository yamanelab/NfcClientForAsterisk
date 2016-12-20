#include <iostream>  // for debug writing
#include <string>    // useful for reading and writing

#include <fstream>   // ifstream, ofstream
#include <sstream>   // istringstream

#include "CardManager.h"

int CardManager::Load(string _datapath) {
	this->datapath = _datapath;

	this->vid.clear();
	this->vIDm.clear();
	this->vPMm.clear();

	FILE* fp;
	if ((fp = fopen(this->datapath.c_str(), "r")) == NULL) return -1;

	fclose(fp);

	ifstream reading_file;
	reading_file.open(this->datapath, std::ios::in);

	std::string reading_line_buffer;
	while (!reading_file.eof())
	{
		std::getline(reading_file, reading_line_buffer);

		std::istringstream line_separater(reading_line_buffer);
		string s;
		line_separater >> s; this->vid.push_back(s);
		line_separater >> s; this->vIDm.push_back(s);
		line_separater >> s; this->vPMm.push_back(s);
	}

	return 0;
}

string CardManager::GetIdFromCard(string IDm, string PMm) {
	for (int i = 0; i < (int)this->vid.size(); i++) {
		if (this->vIDm[i] == IDm && this->vPMm[i] == PMm) return this->vid[i];
	}

	return "";
}

int CardManager::BindIdToCard(string id, string IDm, string PMm) {
	this->vid.push_back(id);
	this->vIDm.push_back(IDm);
	this->vPMm.push_back(PMm);

	this->WriteToDatapath();

	return 0;
}

void CardManager::WriteToDatapath() {
	std::ofstream writing_file;
	writing_file.open(datapath, std::ios::out);

	for (int i = 0; i < (int)this->vid.size(); i++)
	{
		writing_file << " " << this->vid[i] << " " << this->vIDm[i] << " " << this->vPMm[i] << std::endl;
	}
}