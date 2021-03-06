= #技術書典 で入手した本: A-FrameではじめるWebVR 【導入編】

4/9(日)に開催された@<href>{https://techbookfest.org/event/tbf02, 技術書典2}で買ってきた本を読んでいくシリーズ。
一覧は@<chapref>{1704_tbf2-booklist}。

今回は@ikkouさんの「A-FrameではじめるWebVR 【導入編】」です。

A-Frameは簡易的なWeb向けのVR体験構築策としてGoogle I/O 2017のDaydream in the Classroom: Immersive Learningというセッション(@<href>{https://www.youtube.com/watch?v=a824fnWE5S0, YouTubeのビデオ})でも紹介されていました(動画27分40秒あたりから: @<href>{https://youtu.be/a824fnWE5S0?t=1660})。

時系列としては逆順ですが、この動画で興味を持って、実際に手を動かしながら試してみる素材が欲しいなーと思ったところにあるのがこの本です@<fn>{school}。

//footnote[school][本書の第3章でも言及されていますが、本家の@<href>{https://aframe.io/aframe-school/}というコンテンツも割と分かりやすいので良いです]

== 全体的な印象

全体的に出典をちゃんと書いていて良いなと思いました。

「はじめに」の部分に

//quote{
全体的に初心者向き、とても甘口の仕様となっています。本書で満足できない方は、今後発行予定の【開発編】をお待ちください。
//}

とあるとおり、丁寧な作りで間口の広さを感じました。

オブジェクトの貼り付けからアニメーションまでを扱いますが、JSコードは(A-Frameの読み込み部分以外)まったく出てきません。

== 序盤

第1章はVRに関する定番のまとめとWebVRの概要です。

== 第2章

第2章がA-Frameのハンズオンです。
座標系およびroll/pitch/yawをちゃんと説明しているので、この方面に慣れていなくても割とサクサク読めると思います。

ありがちなリモート画像読み込みについてもフォローしていて良いです(file:///... でのローカルファイルアクセス制限によって画像類の読み込みハマリ、というのはハンズオン経験者に割とあるのではないでしょうか)。
