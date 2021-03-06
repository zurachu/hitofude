# hitofude
P/ECEヒトフデ

## 概要
P/ECEヒトフデは、[ニンテンドーDS『直感ヒトフデ』](https://www.nintendo.co.jp/ds/asnj/)（Nintendo / MITCHELL）の
「チェックメイト」モードに良く似たゲームです。

一筆書きでルートを決めると、選択したパネルが白黒反転して、
横一列が同じ色になると、パネルが消えます。
１回の一筆書きで全てのパネルを消すことができたら「クリアー」です。

## インストール
* “hitofude.pex”
* “hitofude.fpk”

を P/ECE に転送して下さい。

“hitofude.pfs”を使うと、P/ECEコミュニケータで
これらのファイルをまとめて転送することができます。

## 操作方法

### 問題選択
↑・↓で問題ファイルを選択し、Ａ・STARTで決定し、ゲームを始めます。
SELECTボタンで終了します。

### ゲーム
回転しているフリーカーソルを動かして、Aボタンで一筆書きの始点を決定します。
一筆書きカーソルで一筆書きして終点でAボタンを押すと、
通ったパネルが白黒反転し、クリアー判定が行われます。

各状態はBボタンでキャンセル、SELECTボタンで問題選択に戻れます。

## 問題作成方法
QUESTION フォルダに問題データが入っています。
これを参考にして、オリジナルの問題を作ることができます。
ファイルフォーマットは、以下のようになっています。

    幅 高さ （外枠部分を除く、最大 14 9）
    以下、パネルデータ（0＝黒、1＝白 の羅列。外枠部分は不要）

“mkq.bat”をクリックして実行すると、QUESTION フォルダ内の
全ファイルを“hitofude.fpk”にパックします。

問題ファイルは、拡張子が“.txt”でなければならないということはありません。
“hitofude.fpk”に格納された全てのファイルを問題ファイルとみなします。
ファイル名は fpk ファイルの制約上、半角英数字記号のみ、最大15文字です。
また、特にファイルのエラーチェックはしていないので、注意して下さい。
fpk ファイル内の問題ファイルは、1024個まで使うことができます。

作成したオリジナル問題を送っていただければ、
本家の“hitofude.fpk”に収録させていただきます。
