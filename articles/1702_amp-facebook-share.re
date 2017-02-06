= AMPからFacebookへのシェア時に「Invalid App ID: 0」とエラーを吐く際の対応

== 現象

AMPのソーシャルシェアに関するドキュメント: @<href>{https://www.ampproject.org/docs/reference/components/amp-social-share}

これを読んで早速

//emlist{
<amp-social-share type="facebook"></amp-social-share>
//}

と書いたらボタンが表示されたので喜んだけれど、実際に飛んでみると@<img>{invalid-app-id}のエラー画面が表示される。

//image[invalid-app-id][App IDが0でまずいと言われる]{
//}

@<href>{https://developers.facebook.com/docs/sharing/reference/share-dialog, facebook側のドキュメント}を読むとapp_idに145634995501895を渡すのがデフォルトのシェア機能呼び出しらしい。

戻ってAMP側を読むと

//quote{
app_id: required, defaults to: none. This parameter is required for the Facebook Share dialog.
//}

と書かれていた。
ちゃんとドキュメントを読んでなかった。

そういうわけで、ささっと

//emlist{
<amp-social-share type="facebook" app_id=145634995501895></amp-social-share>
//}

のように変更してみる。
相変わらずダメで、これはパラメータの渡し方をミスってる雰囲気。

ちゃんと読み直すと、属性に@<code>{data-param-}とプリフィックスを付けるように書かれていた。

== 解決

結果、

//emlist{
<amp-social-share type="facebook" data-param-app_id=145634995501895></amp-social-share>
//}

とすると@<img>{app-id-filled}の通り、無事にシェア画面へ遷移した。

//image[app-id-filled][無事にシェア画面へ遷移した]{
//}

== 反省

Google+やTwitterがデフォルトのままで動作したので油断していました。
デフォルト値をいい感じにしてあるだろうと想像して雰囲気でマークアップやるとダメなパターンですね。