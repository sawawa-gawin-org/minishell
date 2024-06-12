# minishell {#mainpage}

<p align="center">
Summary:<br>
This project is about creating a simple shell.<br>
Yes, your own little bash.<br>
You will learn a lot about processes and file descriptors.<br>
Version: 7.1<br>
</p>

## 実装する機能  
- 入力と履歴(readline)
- 絶対パスや環境変数$PATHを用いた実行可能ファイルの実行
- ビルトインコマンド(外部の実行可能ファイルではなくshellに組み込まれたコマンド)
  - echo (-n)
  - cd (相対パスか絶対パスのみ)
  - pwd (オプションなし)
  - export (オプションなし)
  - unset (オプションなし)
  - env (オプション、引数なし)
  - exit (オプションなし)
- シングルクオートとダブルクオート
- 入出力リダイレクト (<, >, >>)、ヒアドキュメント (<<)
- パイプ (|)
- 環境変数と$?(直前に実行したコマンドの終了ステータス)
- signal
  - Ctrl+C (SIGINT) : 新しい行に新しいプロンプト (bash-3.2$みたいな)
  - Ctrl+D (SIGEOF) : shellの終了
  - Ctrl+\ (SIGQUIT) : 何も起きないようにする (通常、shellが終了するので無効化する)
