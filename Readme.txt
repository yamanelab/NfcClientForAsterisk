NfcClientForAsterisk
====================

概要
----

NFCを使ったAsteriskの入退室システムの操作用ツール。  
コマンドライン専門でwindows(.NET)向け。

For compile
-----------

[SDK for NFC Starter Kit](http://www.sony.co.jp/Products/felica/business/products/ICS-D004_002_003.html)が必要となります。  
このSDKのfelica向けライブラリの.hへのパスを指定するのと、felica.dllの参照をした上でビルドしてください。  
開発時SDKバージョン Ver.2.0.3  

設定
----

Config.hに設定項目があるので、設定してから使用する。

謝辞
----

HTTP通信周りは、[びんずめ堂](http://www.binzume.net/software/cppfl/http.html)を使用しました