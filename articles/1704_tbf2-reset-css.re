= #技術書典 で入手した本: Reset CSS フレンズ🐧🐧🐧🐧🐧

4/9(日)に開催された@<href>{https://techbookfest.org/event/tbf02, 技術書典2}で買ってきた本を読んでいくシリーズ。
一覧は@<chapref>{1704_tbf2-booklist}。

今回は「@<href>{http://friends.o2p.jp/, Reset CSS フレンズ}」（@<href>{http://o2p.jp, O2 Project}刊）です。

//image[cover][表紙]{
//}

本の内容は@<href>{https://github.com/o2project/reset-css-friends/}で公開されています。

== やばさ

本書の内容を前書き部分からそのまま引用します。

 * 1. Reset CSS とは何か（かばんちゃんとサーバルによる解説）
 * 2. Reset CSS の特色（アメリカビーバーとオグロプレーリードッグによる解説）
 * 3. Reset CSS でどのような宣言がされているか（アフリカオオコノハズクとワシミミズクによる解説）

まさか全編このノリでいくとは思わなかった。
やばい。

== 全体的に

 * 自分が書くと、このノリへ変換する部分にめちゃくちゃ時間を費やして挫けそう
 ** 技術書よむぞーと構えて読み始めると、読んでいて違和感しかないので普段本を読んでいる時のような自動typoセンサーが全く機能しない
 ** やるおで学ぶとか、毒舌な妹シリーズとか書けるひとだ...!と思った
 * それもこれも@<href>{https://github.com/o2project/reset-css-friends/pull/13, サンドスターが当たったんじゃあ仕方ない}
 * 脚注でがっつりと出典補足されていてガチ感にじんでいるのが尊くて好き

== プレーリーーーーー！！

 * "ちょっと眠くなったので、ここからはビーバー殿にまかせてわたしは寝るであります。"
 
 このあたりで脳からのドーパミン分泌が最高潮に達して一旦クールダウンを挟んだ。

== 内容について

 * Reset CSSといえば完全にHard resetしか使ったことなかったので、この方面が進化していることにまず驚いた
 ** 考えてみたら、あの頃と比較するとスマフォも増えたしHTML5時代になっているし、カバーできないものが増えてるには違いない。本文で書かれているとおり
 * 使うReset CSSを乗り換えると、結構大幅にサイトのCSS定義をいじることになるのでは…?(特にinput要素)という気持ちでﾋｪｯとなった
 * しかし相変わらずブラウザ(レンダリングエンジン。たとえばWebKit)のバグ回避のためにこの記述を入れる、みたいなのあるのか…と暗澹たる気持ちにもなった
 ** バージョン上がって2-3ヶ月耐えれば余裕、みたいな世界にさっさとなってほしい
 ** CSS定義中のコメントを読む限り、Android 4系で使われているWebKitのためということだから、4.4以上かつアプリ側のtargetSdkVersion指定によってはそろそろ不要なはずだけど、こういうのって次なる"リセット"の流れが来るまで「念のため」で維持されるのかな…

== まとめ部分

 * 最終的なまとめが博士でよかった。ありがたい
 * ざっくり用途ごとにReset CSSの選び方を書いてくれているのも良い