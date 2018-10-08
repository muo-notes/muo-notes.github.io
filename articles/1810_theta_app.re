= THETA用の非公式写真転送・シャッターアプリを作ってる

週末にやっていたメモがてら。

== THETA（S）と私

以前某氏から譲っていただいたTHETA Sを愛用している。
一時期は旅行へ行ってひたすらTHETAだけで写真を撮るという時期もあった。
最近は自分の中でコンデジが復権してきたので出番が少なかったのだけど、遠出する時には旅行鞄へ入れておこうかな、という程度には気持ちが高まってきた。

矢先のことである。

== THETAのAndroidアプリ

THETAシリーズはスマフォとの連携を前提とするユースケースが多く、撮影した写真は基本的にWi-Fi経由でスマフォへ転送して加工・SNS類へという流れ。

この役目はTHETAアプリとTHETA+アプリのふたつが分担する。

前者がTHETA本体内の写真をWi-Fi経由で転送したりリモートシャッターとしてライブプレビューを見ながらISO値や露出時間を設定して撮影したりという機能を持つ。

後者は転送済み写真を加工するアプリで、様々な効果を加えたり連続した制止画を動画にまとめる機能もある。

== THETAアプリがAndroid 9.0でカメラへ接続できない

スマフォをEssential PH-1へ買い替えたので一応接続テストをしておくか、と試してみると全然THETAへつながらない。

手持ちの古い端末にはつながるので、差分はOSバージョンだろうと当たりをつけて得た結論はこれ。

@<raw>{|html|<blockquote class="twitter-tweet" data-lang="ja"><p lang="ja" dir="ltr">挙動を観察してると、THETA公式アプリはClearText Trafficの許可処理をサボっていてAndroid 9.0では哀れなことにWi-Fi経由のTHETA(192.168.1.1)へのHTTPトラフィックが遮断されてる模様。<br>アプリページでの告知は無し、同様の不具合を訴えてる人は居る <a href="https://t.co/BzihzbzlND">https://t.co/BzihzbzlND</a> <a href="https://twitter.com/hashtag/THETA?src=hash&amp;ref_src=twsrc%5Etfw">#THETA</a> <a href="https://t.co/xFS4LlrPB9">https://t.co/xFS4LlrPB9</a></p>&mdash; Kei Nakazawa (@muo_jp) <a href="https://twitter.com/muo_jp/status/1048363420741853184?ref_src=twsrc%5Etfw">2018年10月6日</a></blockquote><script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>}

Cleartext Traffic対応は@<href>{https://developer.android.com/reference/android/security/NetworkSecurityPolicy, NetworkSecurityPolicy}のapplication属性とXMLで処理するのだけど、まだRICOH内で対応してない模様@<fn>{cleartext-attr}。

//footnote[cleartext-attr][usesCleartextTraffic属性の一発指定でもなんとかなりそうではある]

また、Wi-Fiからインターネットに出られるか怪しい際にトラフィックを自動的にLTEや3Gといったモバイル回線へと振り向ける機能とも相性が悪そう。
これに関してはTHETAのWi-Fi APへつながった直後に@<href>{https://developer.android.com/reference/android/net/ConnectivityManager.html#bindProcessToNetwork(android.net.Network), bindProcessToNetwork}でアプリのデフォルト経路を設定してやるのが無難だろう。

適切にこの処理をするためには何かしらの方法で接続先Wi-FiのNetworkインスタンスを取得する必要がある。
@<href>{https://developer.android.com/reference/android/net/ConnectivityManager, ConnectivityManager}に用意されているネットワーク絞り込み用の定数類は明らかにこの用途を満たさないため、自力でNetworkインスタンスを得ることになる。
APIをいくらか掘った限りでは残念ながらdeprecatedな要素を利用するしかなかった。
WifiInfoあたりにNetworkインスタンスを取得するAPIが生えていればstraightforwardだと思うのだけど。

該当箇所：@<href>{https://github.com/muojp/oscsync/blob/5d46fe223cbb3892df444257697f76b655a4ac3d/app/src/main/java/jp/muo/oscsync/OSCConnection.kt#L49}

== OSC APIを調べつつアプリ化

下調べをできたので、前述のようなネットワーク接続まわりの厄介を一定カバーするようにコードへ落としていった。
現状は @<href>{https://github.com/muojp/oscsync/}。

THETAがサポートしているOpen Spherical Camera APIを利用すると、プレビュー取得や写真撮影・各種撮影用設定までWi-Fi経由のHTTPリクエストで完結できる@<fn>{is-it-restful}。

//footnote[is-it-restful][APIがRESTfulかというとまあHTTP APIという表現のほうが無難だろう]

Googleが公開している公式ドキュメント：@<href>{https://developers.google.com/streetview/open-spherical-camera/?hl=ja}優れているのでほぼ迷わない。

OSC APIはLevel 1とLevel 2が定義されており、THETA SはLevel 2対応だと自称するレスポンスを返すのだけど、実際にはLevel 1のみサポートしている（試した範囲では）ところにちょっとハマった。

@<raw>{|html|<blockquote class="twitter-tweet" data-lang="ja"><p lang="ja" dir="ltr">やはりTHETA SはAPI Level 1のみ実装しているようなので、撮影はcamera.startSession → camera.takePictureの手順。<br>Wi-Fi接続直後の状態で/osc/stateを叩くとSID_0000が見えるけど、そのまま使うとエラーが戻ってくるのでstartSession必須。<br>しかしcurlだけでﾋﾟﾋｮﾝと鳴らせたので実際勝てる</p>&mdash; Kei Nakazawa (@muo_jp) <a href="https://twitter.com/muo_jp/status/1047662303594741760?ref_src=twsrc%5Etfw">2018年10月4日</a></blockquote><script async src="https://platform.twitter.com/widgets.js" charset="utf-8"></script>}

初期調査の段階でここまで試行錯誤できたところでまあ大丈夫だろうと思うに至った。

あとはGenericsを利用するクラスに対して::class.javaを叩きたいとか、suspend functionはasyncキーワードというよりはyieldに近い印象とか、暗黙のitは便利とか、coroutinesの起動用launchは現行仕様だとDispatcherをプログラマに意識させるようになってる（少なくともAndroid Studioは暗黙のlaunch { }に対して文句を言う）のかーとか、最終引数のラムダは引数リスト外へ出す慣習らしい（Swiftもそうらしい）とか、主にKotlinへ馴染みが薄いのをカバーする時間だった。

===[column] マイコンとの相性

ESP8266でリモートシャッターを作るぐらいなら簡単にできる。
ESP8266はESP32と比べてメインメモリの少なさが問題になりがちだが、THETA SのAPIは完全にHTTPであり、撮影までに必要なコール回数もかなり少ないため、メモリ上で最低限のJSON処理ができれば十分だろう。

===[/column]

== 先々やりたいこと

現時点でOSC API Level 1デバイスへの接続・セッション開始・撮影機能はつけたので最低限のリモートシャッターとしては動作する状態になっている。

しかしRICOH THETAは本当に面白いハードウェアで、ついついソフト側でもやりたいことが増えてしまう。

=== 撮影プロファイルのクイック切り替え

setOptionというAPIでISO値や露出時間は設定できる。

これ自体は公式のTHETAアプリでもライブプレビューを見ながらできるものだが、個人的には「暗所用の高ISO・短時間露光」「暗所用の低ISO・長時間露光」「日中の低ISO・短時間露光」あたりを自分の好みで数種類用意しておいて撮影時にｼｭｯと設定したいものである。

調べ損なっていたが、一脚とあわせてセルフタイマー撮影も結構楽しいのでアプリ上から楽にモード設定できるとよい（公式THETAアプリではメニュー階層が深くて不便）。

=== 適切なルールにもとづく写真取り込み

THETA本体内の写真をいい感じのルールで取り込む仕組みは必要だと思っている。
とりわけ、THETAから日々生み出される巨大なJPEGファイルをAndroid端末内にずっと置いておくわけにはいかないので、選別あるいはなんらかのクラウドサービスへと同期してローカル分を削除するのが一般的だろう。

=== USB（MTP）経由のクイック取り込み

個人的には写真枚数が多い場合の高速転送にはUSB（MTP）を使うのが好きで、USBホストアダプタは常時持ち歩いてる族。

THETA Sに関してもAndroid端末へUSB接続してAndroid組み込みのファイルエクスプローラから/Pictures/RICOH THETA/以下へ写真をコピーすることでそれなりの高速・低ストレスを実現できることは確認してある。
