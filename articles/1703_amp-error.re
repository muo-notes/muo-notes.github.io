= Google先生から「お前のサイトのAMP、エラーあるよ」と手紙が届いた

Google Search Consoleの管理者設定をおこなったアカウントにAMP関連の通知メールが来たので対応してみたという話です。

== 届いたメール

こんな感じでした(@<img>{google-email})。

//image[google-email][GoogleのSearch Consoleから届いたメール]{
//}

こういう通知が来るのかーと感心しつつ、少々腑に落ちない点がありました。

AMPについて学び、実際に自サイトへ導入する段階で、@<href>{https://validator.ampproject.org/}にあるAMPのスキーマチェックはかけていたからです。
今回のアラートに該当するチェックをおこなってくれるのは@<href>{https://search.google.com/structured-data/testing-tool/, 構造化データ テストツール}で、警告するエリアが違うのは当然といえます。

出ていた警告は@<table>{tbl-structured-data-warnings}のとおりです。

//table[tbl-structured-data-warnings][エラー・警告一覧]{
項目							警告内容
--------------------------------------------------------------------------------------------
author						「author」フィールドの値は必須です。
image						「image」フィールドの値は必須です。
publisher					「publisher」フィールドの値は必須です。
dateModified				「dateModified」は推奨フィールドです。値があれば指定してください。
mainEntityOfPage		「mainEntityOfPage」は推奨フィールドです。値があれば指定してください。
//}

== 対応方針

これを解消するのは少々厄介です。
執筆者情報は相応に書けば良いのですが、画像(image)が必須項目になっているのが少々痛いです。

私が書くエントリは図や参考画像類が少ないので、割と多くのエントリで参照すべき画像が一枚も存在しないということになります。
もちろん適当なダミー画像を指定しても良いのですが、それでいいのか??(構造化データ検証ツールを通すために、構造化データとして意味がほとんど無いものをダミーで入れるべきなのか)という悩ましさが残ります。

ともかく、この対応は本blogのインデックスページを作ってからですね…。
今は「It works!」ですからね…@<fn>{it-works}。

//footnote[it-works][ちなみにこれはApacheでもnginxでもなく、GitHub Pagesに@<href>{https://github.com/muo-notes/muo-notes.github.io/blob/master/index.html, それっぽい内容のファイル}を置いているだけです]

== まとめ

AMPでページを作る時は、@<href>{https://validator.ampproject.org/}と@<href>{https://search.google.com/structured-data/testing-tool/}の両方のバリデータを通しておいたほうが良い。