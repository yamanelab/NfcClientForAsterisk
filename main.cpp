#include <cstdio>
#include <cstdlib>

#include "FelicaWrapper.h"
#include "CardManager.h"
#include "HttpWrapper.h"
#include "Config.h"

FelicaWrapper felica;
CardManager cardManager;
HttpWrapper httpWrapper;

// カードによる入退室管理
void waitCardTouch() {
	string IDm = "", PMm = "";
	string pIDm = "", pPMm = "";
	while (1) {
		printf("Waiting Your Card Touch...\n");

		// カードタッチがあるまで待つ
		while (felica.GetResource(IDm, PMm, 100) < 0) continue;
		
		printf("Touched!!\n");
		pIDm = IDm;
		pPMm = PMm;

		// 状態変更処理
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

		// カードが離れるまで待つ
		while (1) {
			if (felica.GetResource(IDm, PMm, 100) < 0) break;
			if (pIDm == IDm && pPMm == PMm) continue;
		}

		pIDm = IDm;
		pPMm = PMm;

		// 誤爆防止のために1秒ほどインターバル
		_sleep(1000);
	}
}

// 新しいカードの登録
void registerNewCard() {
	// IDを確認
	char buf[256];
	printf("Tell me your ID : ");
	scanf("%s", buf);

	string id = buf;

	printf("Touch your card\n");

	// カードタッチがあるまで待つ
	string IDm, PMm;
	while (felica.GetResource(IDm, PMm, 100) < 0) continue;

	// 登録処理
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

	// コマンドライン引数に"reg"とあればカード登録へ
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
