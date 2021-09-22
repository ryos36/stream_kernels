# Vitis のサンプル
Vitis_Accel_Examples と Vitis_Libraries があることを前提としています。
次のように Vitis_Accel_Examples の下に展開され、Vitis_Libraries が
Vitis_Accel_Examples と同じ階層にあることを想定しています。
```
- Vitis_Accel_Examples
    |
    +-- stream_kernels
- Vitis_Libraries
```

- simple_add
  dataflow を使ったサンプル。これをベースに Vitis_Libraries の
  画像系のライブラリを組み込めるはず。
  
## json
description.json qor.json とかを適切に設定してません。
ちゃんと設定するとチェックが出来たり Makefile の自動生成が出来たり
するものと思われますが、やってません。
