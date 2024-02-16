# minishell

## 1. Mandatory

### 1.1. 概要

プログラム名 : minishell  
提出ファイル : Makefile, *.h, *.c  
引数 : なし  
<details>
<summary>外部関数(折りたたみ)</summary>  

- readline  
- rl_clear_history  
- rl_on_new_line  
- rl_replace_line  
- rl_redisplay  
- add_history  
- printf  
- malloc  
- free  
- write  
- access  
- open  
- read  
- close  
- fork  
- wait  
- waitpid  
- wait3  
- wait4  
- signal  
- sigaction  
- sigemptyset  
- sigaddset  
- kill  
- exit  
- getcwd  
- chdir  
- stat  
- lstat  
- fstat  
- unlink  
- execve  
- dup  
- dup2  
- pipe  
- opendir  
- readdir  
- closedir  
- strerror  
- perror  
- isatty  
- ttyname  
- ttyslot  
- ioctl  
- getenv  
- tcsetattr  
- tcgetattr  
- tgetent  
- tgetflag  
- tgetnum  
- tgetstr  
- tgoto  
- tputs  
</details>  

Libft許可 : OK  
説明 : shellを書く  

### 1.2. shellが行うべきこと
 
- 新しいコマンドの待機時に**プロンプト**を表示する
- コマンドの**実行履歴**を持つこと
- 適切な実行可能ファイルを検索して開始する(環境変数PATHや相対パス、絶対パスに基づく)
- 受け取ったsignalを示すために1つ以上のグローバル変数を使用することは避けてください。<br>このアプローチにより、シグナルハンドラがメインのデータ構造にアクセスしないことが保証される。  

<span style="color: red; ">注意</span> : このグローバル変数は受け取ったsignalの番号以外の情報やデータアクセスを提供することはできない。したがって、グローバルでnormタイプの構造体の使用は禁止される。  

- 閉じられていないクオートや、subject(対象?)に必要のないセミコロン、バックスラッシュのような特殊文字は解釈されない
- 「'」(シングルクオート)を用いることでshellがクオートで囲まれたシーケンス内のメタキャラクタを解釈するのを防ぐ  
```
VAR=hoge
echo $VAR -> hoge
echo '$VAR' -> $VAR

//全てのメタキャラクタを無視して文字列として扱う
```
- 「"」(ダブルクオート)を用いることでshellが「$」記号を除くクオートで囲まれたシーケンス内のメタキャラクタを解釈するのを防ぐ  
```
echo "$VAR is hoge, '$VAR'" -> hoge is hoge, 'hoge'

//ダブルクオート内の変数($)を展開、メタキャラクタ(')を無視
```
- **リダイレクト**を実装する  
  - 「<」は入力をリダイレクトする
  - 「>」は出力をリダイレクトする
  - 「<<」には区切り文字を指定し、区切り文字を含む行が表示されるまで入力を受け取る。ただし、コマンド実行履歴を更新する必要はない。  
  ```
  bash-3.2$ cat << EOF
  > 42
  > Tokyo
  > EOF
  42
  Tokyo
  bash-3.2$

  //コマンド実行履歴には42TokyoやEOFは記載しない
  ```
  - 「>>」は出力を追記でリダイレクトする  
- 「|」(パイプ)を実装する。各コマンドの出力は、パイプを介して次のコマンドの入力に接続される。
- 値に展開される環境変数($の後に文字が続く)を処理する
- 「$?」で最後に実行されたコマンドの終了ステータスを展開する
- bashと同様に動作するctrl+D、ctrl+C、ctrl+\を実装する
- 対話モードの場合:
  - Ctrl+Cを押すと、新しい行に新しいプロンプトが表示される
  - Ctrl+Dを押すと、shellを終了する
  - Ctrl+\は何もしない。
- shellは次の組み込み関数を実装する
  - echo(と-nオプション)
  - 相対パスか絶対パスのみを指定したcd
  - pwd(オプションなし)
  - export(オプションなし)
  - unset(オプションなし)
  - env(オプションや引数なし)
  - exit(オプションなし)  

### 1.3. 補足説明

readline()関数はメモリリークを起こす可能性があり、修正する必要はない。しかし、自分が書いたコードにメモリリークする可能性があってはならない。  

課題説明に限定する必要があり、求められていないものは不要です。要件について疑問がある場合、bashを参考にしてください。

## 2. Bonus part

これらを実装する:

- &&と||と優先順位の括弧
- 「*」(ワイルドカード)