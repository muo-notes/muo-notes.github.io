= #技術書典 で入手した本: Network Maniacs vol.7 高速トランスポート Aeron

2017/4/9(日)に開催された@<href>{https://techbookfest.org/event/tbf02, 技術書典2}で買ってきた本を読んでいくシリーズ。
一覧は@<chapref>{1704_tbf2-booklist}。

アーロンチェア好きなのでタイトルで気になって購入した本です。
もちろん嘘です。

自社の内部ネットワークで極限までパフォーマンスを出したいと思ったときに採れる策のひとつ、というところで大変参考になりました。

== 読書メモ

 * Aeronについて
 ** TCP fairness?しらんぞい というパワある解法 for ローカルネットワーク(あるいはDC内)
 *** Akkaでも使ってるんだそうな
 ** 「標準から離れるのならば徹底的に、ですね」パワー～～～
 ** 通信路としてはUDP, InfiniBand, PCIe-3.0をサポート
 *** なるほど強い
 * サンプルがうまく動作しない時の疎通確認(トラブルシュート)手順も書いてあるので参考になる
 * それぞれ本家のドキュメントへのリンクを書いてあってとてもよかった。次のステップとして深められるの良い
 * Media Driverの共有パターン、ロガーをアタッチして異常追跡するような使い方に結構良さそう
 * 経路にUDPを使う場合、到達データの整合性検証はどうやってるんだろう（調べてみないと分からない）

== typo類

 * p.9
 ** Subsctiption → Subscription
 * p.10
 ** FlagmentHandler → FragmentHandler
 * p.17
 ** offser → offer
 *** @<href>{https://github.com/akka/akka/blob/6c70852/akka-remote/src/main/scala/akka/remote/artery/AeronSink.scala#L58, ソースを読みに行った}感じ、ここは間違いと解釈してよいと思う
