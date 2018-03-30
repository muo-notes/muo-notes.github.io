= AndroidとJota+でRe:VIEW原稿を書く

春です。
技術書執筆の季節ですね。

Androidには@<href>{Jota+, https://play.google.com/store/apps/details?id=jp.sblo.pandora.jota.plus}という優れたテキストエディタがあります。

先日、Jota+を使って雑誌記事を執筆する機会があり、結構快適に原稿を書き進められたので気に入りました。

Jota+は当初Re:VIEW記法を標準サポートしていませんでしたが、公式ドキュメントを軽く読んだところシンタックスハイライト対応は比較的簡単そうだったのでやってみました（@<img>{jota-plus-review}）。

//image[jota-plus-review][Jota+でRe:VIEW文書を開いたところ]{
//}

その後に本家へ取り込んでもらっています（感謝!）。

== Jota+の良いところ

本題へ入る前に、Jota+の良いところというか、気に入っているところをいくつか挙げてみます。

 * 物理キーボードの接続も考慮して設計されている
 ** キーボードショートカットが充実している
 * シンタックスハイライト定義ファイルを自前で用意して利用できる
 * 文字コードの自動認識を含めて一通りの機能が揃っている
 ** 全角スペースの可視化や文字サイズ設定なども地味に揃っている
 * エディタがバックグラウンドへ回ったタイミングで自動セーブするなど、モバイルアプリとしての出来がきっちり良い
 * ファイル作成系はかなり弱い（たとえば.txt以外の新規ファイル作成が困難。つまり.reも）けれどアプリのフォーカスを編集機能に絞っているので問題ない
 ** MGitでファイル管理、Jota+で編集という分担が至高
 * 2018年3月時点でも積極的にメンテナンスされている

少し使ってみると、このどれもが大変尊いことだと分かります。

== Jota+の拡張性

先代であるJotaの時代から、ユーザが自前でシンタックスハイライト設定を増やせるようになっています。

@<href>{Jota Text Editor‎(日本語) > シンタックスハイライト, https://sites.google.com/site/aquamarinepandora/home/jota-text-editor-ja/shintakkusuhairaito}

仕様面では色定義を言語独自に追加できず、colors.confというグローバルなファイルをいじる必要がある点が少々惜しいところです。
シンタックスハイライト設定を書く際にはなるべく論理面に近い色指定をしたいのですが、これはconfファイルのコメントで補完するのが無難でしょう。

== 最低限のRe:VIEW用シンタックスハイライト設定を書いた

なんと既に標準バンドルして配布してくださっています。
ありがたい限りです。

Re:VIEWサポートにあたっては結構割り切った部分が多く、設定エントリ数は少なめで正規表現も比較的単純なものを利用しました。

次に設定ファイルの全文を掲載します。

//list[re.conf][Jota+のRe:VIEW用キーワード定義]{
#
# Re:VIEW keyword file for Jota Text Editor.
#
# This file is in the Public Domain and distributed on "AS IS" basis.

author=Kei Nakazawa
version=0.01
red=={1,5} [^\n]*
statement= \*+ [^\n]*
statement2=//\w*[^\n]*[\{\}]*
string=@<\w+>\{[^\}]+\}
linecomment=#@#[^\n]*
//}

Re:VIEWの見出し、ブロック記法、インライン記法、コメントをカバーしていることが分かります。

== シンタックスハイライト指定のクセ

正規表現をこねていく上ではいくらかの試行錯誤がありました。
Jota+本体の特性を把握しておいたほうがスムースに作業を進められるので、ここでいくつか指定上のクセを紹介します。

重要な原則として、Jota+ではおそらく画面表示時の演算コストを減らすために「複数のパターンに対する同時マッチ」をしていません。

たとえば本エントリ冒頭の

//emlist{
Androidには@<href>{Jota+, https://play.google.com/store/apps/details?id=jp.sblo.pandora.jota.plus}という優れたテキストエディタがあります。
//}

という部分は、Re:VIEW記法としてはインライン要素のhrefを書いています。
つまり@<code>{string=@<\w+>\{[^\}]+\}}に該当します。
しかしこの指定はJota+が内部に持つURIハイライト機能と競合するようで、意図した表示にはなりません（@<img>{inline-and-uri}）。

//image[inline-and-uri][インライン記法+URIの表示]{
//}

//emlist{
Androidには@<href>{Jota+, https/play.google.com/store/apps/details?id=jp.sblo.pandora.jota.plus}という優れたテキストエディタがあります。
//}

//image[inline-only][インライン記法内のURIを除去]{
//}

@<img>{inline-only}のように削ってみると意図通りhref要素全体がカラーリングされるので、やはり内部の正規表現処理順による事情のように見えます。

ちなみに、似た現象はfootprintでも発生します。

//emlist{
//footnote[foo][ちなみにfooは@<href>{https://foo.example.com/foobar.htm}でアクセスできます。]
//}

このとき、footnote内のhref要素は別途ハイライトされてほしいところですが、内蔵のURIハイライトを除く行全体がfootnote側のカラーリングに統一されます（@<img>{inline-in-footnote}）。

//image[inline-in-footnote][footnote内にインライン要素を配置した場合]{
//}

正規表現の適用順によってhref向けの指定が上書きされているのか、と気になるところなので少し試してみます。

//emlist{
@<href>{/ /footnote[foo][ちなみにfoo]は}
@<href>{//footnote[foo][ちなみにfoo]は}
@<href>{foobar} //footnote[foo][ちなみにfoo]
//footnote[foo][ちなみにfoo] @<href>{foobar}
//}

Re:VIEWの構文としてはおかしいのですが、Jota+の実装を推測する上では十分です。

//image[regexp-tests][正規表現適用挙動を観測するためのテスト]{
//}

@<img>{regexp-tests}の結果からは、行単位でマッチングを実施し、先にfootnote側でマッチしたら、当該マッチ範囲を含むhref側のマッチングを打ち切る挙動に見えます。
4番目を見ての通り、footnoteについて行末まで指定のマッチングをかけているためかもしれません。

この先は、少し他の言語用設定ファイルを熟読してもう少し改善してみたいところです。

マルチラインマッチング条件を指定するとまた別ムーブをしそうですが、基本的にマルチライン指定を多用すると大きめのドキュメントを扱う際にパフォーマンス面の問題があるかも、と思ってRe:VIEW設定ファイルを書く際には避けました。

Re:VIEW構文に合わせた厳密な処理のためにはきちんとした構文解析が必須で、その筋を頑張るよりはRe:VIEW文書をモバイル環境で簡単にプレビューできるようにしたほうが筋良さそうです。
