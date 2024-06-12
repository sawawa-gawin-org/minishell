# Documentation {#mainpage}

<p align="center">
Summary:<br>
This project is about creating a simple shell.<br>
Yes, your own little bash.<br>
You will learn a lot about processes and file descriptors.<br>
Version: 7.1<br>
</p>

## 1. Mandatory
### 1.1. 概要

プログラム名 : minishell  
提出ファイル : Makefile, *.h, *.c  
引数 : なし 

<details><summary>外部関数(折りたたみ)</summary>  

<details><summary>readline</summary>

Macのデフォルト環境に存在しないため、brew install readlineで入れる。  
promptをプロンプトとして、読み取った行のテキストを返す。
```
#include <treadline/readline.h>
#include <readline/history.h>

char	*readline(const char *prompt);
```
</details>
<details><summary>rl_clear_history</summary>

readline()が履歴に保存したデータを消す。
```
void  rl_clear_history(void);
```
</details>
<details><summary>rl_on_new_line</summary>

改行を出力した後、新しい行に移動したことを更新関数に伝える。
```
int  rl_on_new_line(void);
```
</details>
<details><summary>rl_replace_line</summary>

呼ぶ前の行の文字列を指定した文字列に置き換える。  
第二引数を0にすると置き換えた文字列を履歴に残さないが、1にすると残る。
```
void  rl_replace_line(const char *text, int clear_undo);
```
</details>
<details><summary>rl_redisplay</summary>

現在の行の状態を反映するために再描画する。
```
void  rl_redisplay(void);
```
</details>
<details><summary>add_history</summary>

履歴リストに現在の行を追加する。
```
void  add_history(const char *);
```
</details>

- printf  
- malloc  
- free  
- write  

<details><summary>access</summary>

pathのファイルの実ユーザーに対するアクセス権をチェックする。  
modeはチェック項目を設定する。R_OK(読取+ファイル存在)、W_OK(書込+ファイル存在)、X_OK(実行+ファイル存在)、F_OK(ファイル存在)がある。アクセス可能で0、不可またはエラーで-1を返し、errnoを設定する。
```
#include <unistd.h>

int  access(const char *path, int mode);
```
</details>


- open  
- read  
- close  
<details><summary>fork</summary>

呼び出し元プロセスを複製して新しいプロセス(子プロセス)を生成する。  
使用後、親プロセスのpid_tは0より大きい数に、子プロセスは0になる。エラー時は-1となる。
```
#include <unistd.h>

pid_t  fork(void);
```
</details>
<details><summary>wait</summary>

子プロセスの状態変化(終了やシグナルによる停止、再開)を待つ。statは子プロセスの終了ステータスを含む変数を指定する。exitの引数そのままではなく、ステータス & 0377である。不要ならNULLでもOK
```
#include <sys/wait.h>

pid_t  wait(int *stat);

//マクロ
WIFEXITED(status) //子プロセスが正常に終了したら真
```
</details>
<details><summary>waitpid</summary>


```
#include <sys/wait.h>

waitpid(pid_t pid, int *stat_loc, int options);

```
</details>

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
<details><summary>getenv</summary>

nameで指定された文字列に環境変数と一致するものがあれば環境変数名が格納された場所のポインタを返す。一致するものがなければNULLを返す。
```
#include <stdlib.h>

char  *getenv(const char *name);
```
</details>


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

> [!WARNING]
> このグローバル変数は受け取ったsignalの番号以外の情報やデータアクセスを提供することはできない。したがって、グローバルでnormタイプの構造体の使用は禁止される。  

- 閉じられていないクオートや、subjectに必要のないセミコロン、バックスラッシュのような特殊文字は解釈されない
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

- &&と||で優先順位をつける
- 「*」(ワイルドカード)
