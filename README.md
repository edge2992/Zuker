# Zuker algorithmの実装


## cmakeとgtestを勉強した(備忘録)


### 参考にしたサイト

[cmakeでgoogletestできる環境を作ってみる https://www.jonki.net/entry/2016/06/15/220029]
ctestができるとこまで

[(続) Google Testを導入してみた https://qiita.com/y-vectorfield/items/f69464ee5d8cd80153bd]
gtestを外部プロジェクトとしてダウンロードする（DownloadProjectを使用）

### コマンド例

```
mkdir build
cd build
cmake ..
make
make test or ctest --verbose
```
