= RISC-V ISAの基本構造 #RISC-V

RISC-Vの仕様は@<href>{https://riscv.org/specifications/}で入手できます。
ここでは本稿執筆時点の最新版であるユーザレベルISA 2.2に基づいて解説します。
特権アーキテクチャに関するドラフト仕様書も別途公開されていますが、今回は扱いません。

RISC-Vは比較的新しいISAで、まだ策定途中の仕様も多く存在します。
仕様書の冒頭、Preface部分に各仕様のバージョンとフリーズ状態(後方互換性を確保する段階まで到達しているか否か)の記載がありますので、参考にしてください。

== モジュラーなアーキテクチャゆえの読み方

RISC-VのISAを構成する要素は多岐にわたります。
これらはコアの設計者が必要に応じて取捨選択できるため、RISC-V ISAにもとづくチップには多くのバリエーションが考えられます。
RISC-V互換のコアではその実装するISAを表現するために「RV」につづけてビット幅、その後に標準拡張と独自拡張情報を記載します。

たとえば、@<href>{https://bellard.org/riscvemu/, RISCVEMU}というエミュレータはRV128IMAFDQCアーキテクチャをサポートします。
これは128-bitアーキテクチャであり、128-bit整数に対する加減算類の基本演算と制御フロー用の基本命令群に加え、乗算除算、アトミックなメモリアクセス、単精度浮動小数点演算、倍精度浮動小数点演算、4倍精度浮動小数点演算、そして圧縮命令セットをサポートするという意味です。

== 整数ISA(RV32I/RV64I/RV128I)

基本的な整数ISAとしてはRV32I、RV64I、RV128Iがあります。
末尾がIの命令セットに含まれるのは基本的なコントロールフローにレジスタとメモリ間・レジスタ同士のメモリ転送や整数の加減算と論理演算のみです。

== 標準拡張ISA

これだけ絞り込まれているとFPGA上およびASIC上での実装面積を低減できますが、汎用プロセッサとしてRISC-Vを利用したい場合にはもう少し幅広い命令群を利用したいケースが多いです。
ハードウェアでの乗算・除算をおこなうM命令群、アトミックなメモリアクセスをおこなうA命令群、そして浮動小数点演算として単精度のF命令群、倍精度のD命令群、4倍精度のQ命令群があります。

ここまでで出てきた「IMAFD」が汎用スカラー命令セットとしてよく使われるので、これらを組み合わせてGと呼べることになっています。

標準拡張って標準なのか、拡張なのか、と気になるところですが、標準として定められている拡張ISA(Standard Extensions)の意です。

== 圧縮命令拡張(C命令群)

RISC-Vの命令はいずれも32-bit長です。
しかし圧縮命令拡張(C命令群)という、16-bit命令長の拡張命令セットもあります。

これは典型的なプログラム中で頻発する命令列に16-bitの短縮命令を割り当て、コア内で元の32-bit命令へと展開して実行するものです。
短縮命令とフル命令は単純な一対一対応であり、かなり小さなチップ実装面積のオーバーヘッドで大幅なプログラムサイズの削減が可能です。
プログラムサイズの削減は、組み込み向けなどプアな環境での必要リソース削減のみならず、ハイエンドな環境の命令キャッシュの容量節約にも役立ちます。

圧縮命令の利用により、SPECint2006ベンチマークの場合は約25%ものプログラムサイズを削減できるとしています。

具体的にどのような頻出命令を圧縮対象としたのか、他アーキテクチャと比較してどの程度小さくなるのか、といった点については第2回RISC-VワークショップでのUCBチームによる資料: @<href>{https://riscv.org/wp-content/uploads/2015/06/riscv-compressed-workshop-june2015.pdf, RISC-V Compressed Extension}(PDF)を参照してください。

== 組み込み環境向け命令セット

RISC-Vは32-bitから128-bitまでの幅広いアーキテクチャをサポートしますが、マイクロコントローラー用途に64-bitや128-bitのアーキテクチャを定義する意味はさすがにほとんどありません。

RV32Eは32-bitアドレス空間向けのみで標準化されている組み込み向け命令セットです。
具体的にはRV32Iの持つ32のレジスタを16まで削り(これにより25%のコア面積とそれに伴う消費電力を削減できるとしている)、ハードウェアタイマーやカウンタの擬似命令を必須から外したものです。
この場合、50個未満の命令でマイクロコントローラーを実装できます。
RV32EにはM,A,C命令群を実装することもできるので、実装面積に余裕があれば実行速度やプログラムサイズの削減に役立てられます。
しかしハードウェアでの浮動小数点演算(F/D/Q)はサポートせず、Unix系のOSをフルに実行できることを目指すものでもないため、あくまでもマイクロコントローラ向けの用途といえます。

RISC-VのユーザモードISAの中で頻出するものを概説しました。
ここで挙げた以外の拡張命令と拡張提案についても機会を改めて書きたいところですが、気になる方は前述のISA仕様書を確認してみてください。