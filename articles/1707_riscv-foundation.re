= RISC-V Foundationを中心とするアーキテクチャ管理体制 #RISC-V

RISC-Vはカリフォルニア大学バークレー校の研究プロジェクトとして始まり、同校発のRISC-V特化ベンチャー企業である@<href>{https://www.sifive.com/, SiFive}やチップ製造プロジェクトの@<href>{http://hwacha.org/, Hwacha}からデバッグ用の仕様やベクター拡張命令セットのベース提案などを受けつつ発展してきました。

他にもケンブリッジ大学の@<href>{http://www.lowrisc.org/, lowRISC}プロジェクト、スイスのチューリッヒ工科大学とイタリアのボローニャ大学が中心となって進めている@<href>{http://iis-projects.ee.ethz.ch/index.php/PULP, PULPプロジェクト}、マサチューセッツ工科大学とプリンストン大学を中心とするISA検証系のプロジェクトなどが各種実装の提供やアーキテクチャへの提案の中心的役割を果たしてきました。

2010年のプロジェクト開始から約7年が経過したRISC-Vは、その拡大とともに中核たるアーキテクチャの議論や管理をRISC-V Foundationへと移しつつあります。
これはカリフォルニア大学バークレー校からRISC-Vを離陸させてオープンな委員会と議論に基づく策定体制を確立する目的と共に、初期のRISC-V立ち上げに携わった学生が卒業(修了)していくことで失われる継続性をFoundation側である程度吸収するという思惑もあります@<fn>{out-of-berkeley}。

//footnote[out-of-berkeley][このあたりの事情はRISC-Vワークショップの講演内でもたびたび言及されますが、簡単なまとめとしては第3回ワークショップでの@<href>{https://riscv.org/wp-content/uploads/2016/01/Tues1000-RISCV-20160105-Updates.pdf, RISC-V Updates}(PDF) p.9が分かりやすいです]

== RISC-V Foundationの役割

@<href>{https://riscv.org/, RISC-V Foundation}の主な役割は、ISAに関するさまざまな委員会・タスクグループのホスト、ISAと周辺ドキュメントのメンテナンス、ワークショップの開催、そしてRISC-Vブランドの管理です@<fn>{foundation-roles}。

//footnote[foundation-roles][直近のミッションや委員会/タスクグループ一覧については、2017年5月に開催された第6回RISC-Vワークショップでの@<href>{https://riscv.org/wp-content/uploads/2017/05/Mon1145-RISC-V-Foundation-Update.pdf, Foundation Update}(PDF)を読むのが手っ取り早いです]

== RISC-V名称/ロゴの商用利用に必要な手続き

RISC-VはオープンでロイヤリティーフリーのISAですが、商用製品においてRISC-Vの名称やロゴといったブランドを利用したい場合には手続きが必要です。

まず、当該企業はRISC-V Foundationのスポンサー企業になり、Foundationとの良好な関係を維持する必要があります。
スポンサーのグレードによってRISC-V Foundationへ行使できる影響力が異なりますが、RISC-Vの名称やロゴを商用利用する上では最低レベルのSilver会員(年会費$5,000)で問題ありません。

そして、対象製品についてRISC-V FoundationがメンテナンスするオープンソースのRISC-V互換性テストツールでRISC-VのISAに準拠していることを確認できたら、その製品についてRISC-Vという名称と関連する商標を利用できます。

この手続きはあくまでも商用製品に関するもので、RISC-Vを教育目的や研究・OSS利用など非商用利用する場合には、RISC-V Foundationへの参加すら必須ではありません。

== 各種委員会の状況

RISC-V Foundationのメンバー(スポンサー企業、大学類、個人)のみが各委員会の委員になれます。
2016年以降は各委員会がアクティブに活動しており、多くのトピックが並列進行しています。

各委員会とそのサブ委員会の長は、前述のスポンサーレベルのうち、Gold(年会費$10,000)以上の会員企業から就任できることになっています。
このため、企業としてはそれぞれが影響力を確保したいエリアの委員会やその下部のタスクグループに参加し、議論を推進していくことになります。

=== マーケティング委員会

RISC-Vのマインドシェアを高めることと、コミュニティを育てることが目的です。
チュートリアルや年数回のワークショップを主導する役割も持ちます。

=== テクニカル委員会

ISAの議論やオペコード空間の管理、デバッグ仕様などRISC-Vに関する技術的な領域を幅広く扱うものです。

この委員会では5個の中間ゴールが示されています。

 * ISAロードマップのメンテナンス
 * ISAのゴールデンシミュレータの提供とメンテナンス
 * ISAと拡張を検証・バリデートするテストの提供とメンテナンス
 * ソフトウェア開発ツールのアップストリーム化
 * アーキテクチャのハードウェア実装一覧のメンテナンスと更新

各課題はそれぞれさらに細分化されたタスクグループ(2017年5月時点で9つ)が推進します。

== RISC-Vへの拡張命令セット提案

=== ベクター拡張命令セット

RISC-Vをハイパフォーマンス領域で利用する上では、スカラー命令群に加えてベクター命令群のサポートが望まれています。

ここでは"V"命令群として提案されているベクター拡張命令セットについて述べます。

x86系やARM系など近年の主力CPUアーキテクチャではpacked-SIMD命令セットによるベクタ処理が主流です。
RISC-Vの"V"命令セット提案ではpacked-SIMDを採用せず、Crayスタイルの伝統的なベクターISAを提案しています。
これはカリフォルニア大学バークレー校発のRISC-VプロジェクトであるHwachaが実装したベクターアーキテクチャを拡張したものです。

packed-SIMDを実装する"P"命令群の提案ドラフトも存在しますが、基本的に"V"命令群を主流として補完的な利用をすることが想定されています。

====[column] packed-SIMD(SSE/AVX/NEON系のSIMD)、ほんとにやるの?

完全に個人的な感覚ですが、packed-SIMDについてIntelやARMが保有する特許群を避けながらまともに実装するのはほぼ無理なのでは・・・と思っています。
とりわけ、「おう、やれるならやってみろよ 死屍累々のエリアだけどな!」というパワーあふれる姿勢を鮮明にしているIntel(参考: @<href>{http://www.itmedia.co.jp/news/articles/1706/11/news014.html, Intel、「x86のエミュレーションは特許侵害」とARM版Windows 10に牽制}, @<href>{http://www.atmarkit.co.jp/ait/articles/1706/28/news025.html, 頭脳放談：第205回 Intelと互換プロセッサとの戦いの歴史を振り返る})の前で本当にやるの?? という気持ちが強いです。
もちろん命令互換なんてバカなことはしないはずですが、数々の特許を吟味して回避策を立てつつ現代的な命令セット設計をできるのか、さらにそれらが特許侵害を避けつつマイクロアーキテクチャに落とせるのか疑問です。

RISC-V Foundationの役割内にも「maintains a directory of public-domain instruction set architecture and micro-architectural techniques, culled from publications and expired patents」@<fn>{dir-isa}というのがあって、本来的に失効済み特許と出版物からの抜粋で明示できない要素の積極的な情報整理はおこなわないはずなんですよね。

//footnote[dir-isa][@<href>{https://riscv.org/wp-content/uploads/2017/05/Mon1145-RISC-V-Foundation-Update.pdf, p.9 Foundation Function}]

そういうわけで、packed-SIMDに関しては特許面の強力なスポンサーが現れでもしない限りそっとしておくのが無難で、「他アーキテクチャにあるものがRISC-Vにも一式ないとヤダヤダ!!」という人々は放っておけばいいのに…というぐらいの気持ちで眺めています。

====[/column]

=== 特権アーキテクチャの提案

スーパーバイザーを利用するマシンの仮想化についても@<href>{https://riscv.org/specifications/privileged-isa/, ドラフト仕様}(執筆時点の最新版は1.10)が提出されています。

=== メモリモデルについて

アトミックなメモリの読み書きとコヒーレンシの確保は頭の痛い問題です。
この点について、RISC-V Foundation内のメモリモデルタスクグループで活発に議論が続いています。

まずPOWERやARMのものにならわない理由として、これらはマイクロアーキテクチャ上の細かな点がISA側に露出しているから、ということです。
つまり、ブランチ投機やアウトオブオーダー実行、ロールバック類がメモリモデル仕様に絡んでくるのは避けたいということです。

これをひきはがしつつ、設計上の柔軟性を十分に確保できるメモリモデルを策定するべく努力が続けられています(@<fn>{memory-model-proposal})。

//footnote[memory-model-proposal][Sizhuo Zhangら, A Memory Model for RISC-V, @<href>{https://riscv.org/wp-content/uploads/2016/12/Tue1130-RISC-V-memory-model-Vijayaraghavan-MIT-V2.pdf}]
