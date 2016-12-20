#include <cstdio>
#include <cstdlib>

#include "FelicaWrapper.h"
#include "CardManager.h"
#include "HttpWrapper.h"
#include "Config.h"

FelicaWrapper felica;
CardManager cardManager;
HttpWrapper httpWrapper;

// �J�[�h�ɂ����ގ��Ǘ�
void waitCardTouch() {
	string IDm = "", PMm = "";
	string pIDm = "", pPMm = "";
	while (1) {
		printf("Waiting Your Card Touch...\n");

		// �J�[�h�^�b�`������܂ő҂�
		while (felica.GetResource(IDm, PMm, 100) < 0) continue;
		
		printf("Touched!!\n");
		pIDm = IDm;
		pPMm = PMm;

		// ��ԕύX����
		string id = cardManager.GetIdFromCard(IDm, PMm);
		if (id != "") {
			printf("Hi, %s\n", id.c_str());
			string url = ASTERISK_URL;
			url += "api/update/nfc.php?id=";
			url += id;
			httpWrapper.HttpRequest(url);
		}
		else {
			printf("Sorry... I don't you.\n");
		}

		// �J�[�h�������܂ő҂�
		while (1) {
			if (felica.GetResource(IDm, PMm, 100) < 0) break;
			if (pIDm == IDm && pPMm == PMm) continue;
		}

		pIDm = IDm;
		pPMm = PMm;

		// �딚�h�~�̂��߂�1�b�قǃC���^�[�o��
		_sleep(1000);
	}
}

// �V�����J�[�h�̓o�^
void registerNewCard() {
	// ID���m�F
	char buf[256];
	printf("Tell me your ID : ");
	scanf("%s", buf);

	string id = buf;

	printf("Touch your card\n");

	// �J�[�h�^�b�`������܂ő҂�
	string IDm, PMm;
	while (felica.GetResource(IDm, PMm, 100) < 0) continue;

	// �o�^����
	cardManager.BindIdToCard(id, IDm, PMm);

	printf("Complete! Welcome to our labo, %s!\n", id.c_str());
}

int main(int argc, char *argv[])
{
	cardManager.Load(CARD_DATA_PATH);

	if (felica.Initialize() < 0) {
		printf("Can't initialize Felica.\n");
		return -1;
	}

	// �R�}���h���C��������"reg"�Ƃ���΃J�[�h�o�^��
	if (argc == 1) {
		waitCardTouch();
	}
	else if (strcmp(argv[1], "reg")) {
		registerNewCard();
	}
	else {
		waitCardTouch();
	}

	if (felica.Dispose() < 0) {
		printf("Can't dispose Felica.\n");
		return -1;
	}

	return 0;
}
