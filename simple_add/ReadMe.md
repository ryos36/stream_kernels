AXI Stream Simple Add Sample Kernel (HLS C/C++)
===============================================

このサンプルは Vitis HLS C/C++ の AXI Stream と HLS dataflow を使った
サンプルです。 xf::cv::AXIvideo2xfMat を使うため Vitis_Libraries を
必要とします。

host/streaming_free_running_k2k をベースにしています。


# EXCLUDED PLATFORMS
U50 でしか試してません。

streaming_free_running_k2k をそのまま持ってきているので
次のプラットフォームははじくようになっています。

   2018
   qep
   aws-vu9p-f1
   samsung
   zc702
   nodma

# DESIGN FILES

   src/host.cpp
   src/mem_read.cpp
   src/mem_write.cpp
   src/simple_add.cpp
   
# COMMAND LINE ARGUMENTS

U50 の実機があるなら
```
   ./simple_add <krnl_simple_add XCLBIN>
```
で実行できますが、hw_emu や sw_emu の場合環境変数の設定が
あるので、簡便に実行したいときは make run としてください。

```
    make run TARGET=hw_emu DEVICE=xilinx_u50_gen3x16_xdma_201920_3
```

# DETAILS
streaming_free_running_k2k から持ってきているので
streaming_free_running_k2k の DETAILS も読んでください。

simple_add.cpp の simple_add 関数はカーネルではありますが
stream の引数と ap_ctrl_none が設定されているので、
スタートの合図なしに勝手に走ります(free run!)。
ホスト側から simple_add だけは enqueueTask する必要がありません。

mem_read.cpp と mem_write.cpp に HLS interface を明示的に使ってませんが
勝手に m_axi と同じ扱いになるようです。

krnl_simple_add.cfg に次のように stream の接続が書かれています。
```
   [connectivity]
   stream_connect=mem_read_1.stream:simple_add_1.input
   stream_connect=simple_add_1.output:mem_write_1.stream
```

これだけなら streaming_free_running_k2k と変わらないのですが
simple_add の中では xf::cv::AXIvideo2xfMat を使っています。
これで user と last を見るようになります。
更に 
```
#pragma HLS dataflow
```
としているので dataflow 化されます。dataflow は癖があってそうコンパイル
されるように書かないといけません。関数化して中身を外に出してしまうのが
一番簡単そうです。プログラムでは my_add として外に出しました。
