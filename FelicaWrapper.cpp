#include "FelicaWrapper.h"

FelicaWrapper::FelicaWrapper() { }

int FelicaWrapper::Initialize() {
	if (!initialize_library()) {
		fprintf(stderr, "Can't initialize library.\n");
		return -1;
	}

	if (!open_reader_writer_auto()) {
		fprintf(stderr, "Can't open reader writer.\n");
		return -2;
	}
	
	return 0;
}

int FelicaWrapper::Dispose() {
	if (!close_reader_writer()) {
		fprintf(stderr, "Can't close reader writer.\n");
		return -1;
	}

	if (!dispose_library()) {
		fprintf(stderr, "Can't dispose library.\n");
		return -2;
	}

	return 0;
}

string vectorToString(unsigned char* vector, int length) {
	string ret = "";
	char buf[8];
	for (int i = 0; i < length; i++) {
		sprintf(buf, "%02x", vector[i]);
		ret += buf;
	}
	return ret;
}

int FelicaWrapper::GetResource(string& IDm, string& PMm, unsigned int timeout = 1000) {
	structure_polling polling;
	unsigned char system_code[2] = { 0xFF, 0xFF };
	polling.system_code = system_code;
	polling.time_slot = 0x00;

	unsigned char number_of_cards = 0;

	structure_card_information card_information;
	unsigned char card_idm[8];
	unsigned char card_pmm[8];
	card_information.card_idm = card_idm;
	card_information.card_pmm = card_pmm;

	set_polling_timeout(timeout);

	IDm = "";
	PMm = "";

	bool ok = polling_and_get_card_information(&polling, &number_of_cards, &card_information);
	if (ok) {
		IDm = vectorToString(card_idm, sizeof(card_idm));
		PMm = vectorToString(card_pmm, sizeof(card_pmm));

		return 0;
	}

	return -1;
}