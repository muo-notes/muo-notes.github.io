= フルAMPで作っている新blogのTODOメモ

@<raw>{|html|<blockquote class="twitter-tweet" data-lang="ja"><p lang="ja" dir="ltr">Bloggerさすがに面倒が多い(絵文字どころか一部Unicode文字が通らない、画像アップロードAPIが無い、APIをhackyに使わないと記事URL指定ができない、テンプレ内にCSSべた書き流石に厳しい)ので新記事置き予定地作った<a href="https://t.co/b7LB6m3OYy">https://t.co/b7LB6m3OYy</a></p>&mdash; Kei Nakazawa (@muo_jp) <a href="https://twitter.com/muo_jp/status/828093681114583040">2017年2月5日</a></blockquote><script async src="//platform.twitter.com/widgets.js" charset="utf-8"></script>}

Bloggerがさすがに厳しかったのでGitHub Pages系のyet another blog構築ツールを自分用に書き始めたのが2/5ぐらい。

@<href>{https://github.com/muo-notes/muo-notes.github.io}でせっせと作っているけれど、まだまだ先が長い。

== 現状できているもの

 * 最低限のAMPドキュメントとしての体裁
 * 手動でもりもり書けば一応コンテンツを増やしていける程度

== まだインデックスページを作ってない

 * サイトのいわゆるメタデータは基本的にデータディレクトリ内のJSONの山で管理する
 ** SQLiteやRealmを使えば良いのでは、という気はするけれど
 *** こういうことを考えるフェーズよりだいぶ手前に居ると思っているので今は内部表現ママでok

== 記事ごとのカテゴリ紐付けをどうやってやるかという問題

 * Re:VIEW側のコメントに書いておいてビルド時に拾う形か、ビルドコマンドのオプションに渡す形、はたまた空っぽのJSONを生成しておくから自分で勝手に書く形
 ** この方針が決まっていないので、今は完全に決め打ちの意味ないカテゴリ情報を生成してる。一通り揃ったら既存の記事は生成しなおす(この手間がつらくなる前にケリをつける必要がある)
 * JSONを編集後に再度最低限のビルドコマンドを叩く必要が生じるのでちょっと面倒感ある
 * CMSめいたものはなるべく用意したくない

== 指定日時公開系のものを作れるようにするかという問題

 * GitHub Pagesでこれを実現するためには、決まったタイミングで指定ブランチへのpushやマージ指示を出すサービスが必要ということになる
 * ちょっと問題のスコープを絞るのが厄介なので後回し

== PC環境など、横幅に余裕があればサイドメニューを出す構造にしたい

 * 現状、やりかけて力尽きた状態になっていて大変格好悪い
 ** @<href>{https://www.ampproject.org/docs/get_started/create}のサイトはAMPでありつつこの構造を実現しているので、どうするのか調べていけばなんとかなりそう
 ** なんとなくだけど、ServiceWorkerを使ってApp Shell提供しているような気がしないでもない
 ** 最近立てた@<href>{https://github.com/ampproject/amphtml/issues/7449}というissue経由でこのサイトが@<href>{https://github.com/ampproject/docs}から生成されていると知ったので多少掘っていく
