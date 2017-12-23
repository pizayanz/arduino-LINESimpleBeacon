# LINE Simple Beacon with BBC micro:bit

みんな大好き、 micro:bit を LINE Simple Beacon 化するライブラリをつくってみました。

  - http://microbit.org/
  - https://www.switch-science.com/catalog/3380/


BBC micro:bit を、LINE Simple Beacon 化するためのライブラリになります

## Install (開発環境設定) と サンプルプログラムの実行方法

### micro:bit を arduino として使います

1. Arduino IDE をインストールし、起動します (1.8.5で試しました)
  - 環境によっての設定は、Arduino のサイトを参考にしてください
2. メニュー [ファイル] > [環境設定] で "追加のボードマネージャの URL" に次のURLを追加してください
  - https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json
3. メニュー [ツール] > [ボード] > [ボードマネーシャ] を選んでください
4. Nordic Semiconductor nRF5 based boards を探してインストールしてください

### 依存するライブラリ の追加

1. [スケッチ] > [ライブラリをインクルード] > [ライブラリを管理] を選ぶ
2. [検索をフィルタ] に "BLEPeripheral" と入力してください
3. BLEPeripheral by Sandeep Mistry が表示されたら、それを選んでインストールをクリックしてください

### SoftDevice の書き込み

micro:bit は、Nordic の nRF5x シリーズの BLEチップが搭載されています。
このチップのBLE機能を利用するには SoftDevice というファームウェアのようなイメージを書き込む必要があります。

1. Arduino IDE のスケッチブックの標準の保存フォルダを Explorer(PC) や Finder(Mac) で開きます 
  - [ファイル] > [環境設定] にあります。
2. そこに tools\nRF5FlashSoftDevice\tool\ というフォルダを作ります 
  - 三階層分作ってください。tools, nRF5FlashSoftDevice, tool
3. nRF5FlashSoftDevice.jar をダウンロードし、作った tool フォルダにコピーします
  - https://github.com/sandeepmistry/arduino-nRF5/releases/download/tools/nRF5FlashSoftDevice.jar
4. Arduino IDE を再起動します
5. micro:bit を USBケーブルで PC/Mac と接続します。
6. [ツール] > [SoftDevice] で "S130" を選択します (S110 でも ビーコンは動くようです)
7. [ツール] > [書き込み装置] で "CMSIS-DAP" を選択します
8. [ツール] > [シリアルポート] で "BBC micro:bit" っぽいものを選択します
9. [ツール] > [nRF5 Flash SoftDevice] を選択し、SoftDevice を micro:bit に書き込みます

### このレポジトリを、Arduino IDE のライブラリに追加

1. スケッチブックの保存フォルダを Explorer や Finder で開きます [ファイル] > [環境設定] にあります。
2. そこの Library フォルダに、このレポジトリを zip ダウンロードするなどし、解凍して保存します
3. Arduino IDE を再起動します

## サンプルプログラムの実行

1. 次のURLを開いて、LINE から SimpleBeacon の HWID を払い出します
  - https://admin-official.line.me/beacon/register#/
  - 詳しくは、LINE Beacon のページを確認してください
    - https://developers.line.me/ja/docs/messaging-api/using-beacons/
2. Arduino IDE で [ファイル] > [スケッチ例] > [LINESimpleBeacon] > [LINESimpleBeacon] を開きます
3. ソースの 8行目あたりの 5つの16進数の数字を、LINE から 払い出した HWID に設定します
  ```c++
  unsigned char hwid[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
  # を、HWIDが 1A2B3C4D5E の場合は
  unsigned char hwid[5] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E};
  # と書き換えます
  ```
3. [ファイル] > [名前をつけて保存] で、任意の場所に保存します
4. S130を書き込み済みの、micro:bit を USBケーブルで PC/Mac と接続します
5. [スケッチ] > [マイコンボードに書き込み] します

これで、LINE Beacon として動くはずです 

