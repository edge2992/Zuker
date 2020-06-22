# Zuker algorithm
CLL implementation of Zuker algorithm

## the way to use

```
mkdir build
cd build
cmake ..
make
src/demo
```

## sample case of tRNA
input
```
UGUGGUGUAGUGGUUAUCACGUUUGCCUUACACGCAAAAGGUCUCCAGUUCGAUCCUGGGCAGCACCA
```

output
```
..((((((((((.....)))........))))).))...(((((((((.......))))..)).))).
```
![trna](https://github.com/kaz-i-54/Zuker/blob/master/result/trna.png?raw=true)
## cmakeとgtestを勉強した(備忘録)

* [cmakeでgoogletestできる環境を作ってみる][https://www.jonki.net/entry/2016/06/15/220029]
ctestができるとこまで

* [(続) Google Testを導入してみた][https://qiita.com/y-vectorfield/items/f69464ee5d8cd80153bd]
gtestを外部プロジェクトとしてダウンロードする（DownloadProjectを使用）

https://rna.urmc.rochester.edu/NNDB/turner04/gu.html
>Note also that the motif 5'GG/3'UU is assigned a ∆G°37 of –0.5 kcal/mol to optimize structure prediction accurracy, whereas it is measured as +0.5 kcal/mol
