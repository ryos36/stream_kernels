/**
* Copyright (C) 2019-2021 Xilinx, Inc
*
* Licensed under the Apache License, Version 2.0 (the "License"). You may
* not use this file except in compliance with the License. A copy of the
* License is located at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
* License for the specific language governing permissions and limitations
* under the License.
*/
#include <ap_axi_sdata.h>
#include <ap_int.h>
#include <hls_stream.h>

#define SRC_HEIGHT 480
#define SRC_WIDTH 640

extern "C" {
void mem_read(int* mem, hls::stream<ap_axiu<8, 1, 1, 1> >& stream, int size) {
mem_read:
    /*
    for (int i = 0; i < size; i++) {
        unsigned int a = mem[i];
        ap_axiu<8, 1, 1, 1> v;
        v.data = a;
        stream.write(v);
    }
    */
    bool sof = 1;
    ap_axiu<8, 1, 1, 1> v;
    unsigned int rpos = 0;

    for( unsigned int src_y = 0; src_y < SRC_HEIGHT; src_y++) {
        for( unsigned int src_x = 0; src_x < SRC_WIDTH; src_x++) {
            if ( sof ) {
                v.user = 1;
                sof = 0;
            } else {
                v.user = 0;
            }
            v.data = mem[rpos++];
            v.last = (src_x == (SRC_WIDTH - 1))?1:0;
            stream.write(v);
        }
    }
}
}
