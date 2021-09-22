#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <cmath>
#include <utility>

#include "ap_axi_sdata.h"
#include "hls_stream.h"

#include "common/xf_common.hpp"
#include "common/xf_infra.hpp"
#include "common/xf_utility.hpp"

namespace {
void
my_add(xf::cv::Mat <XF_8UC1, 480, 640, XF_NPPC1> &frame_in, xf::cv::Mat <XF_8UC1, 480, 640, XF_NPPC1> &frame_out)
{
    int read_pointer = 0, write_pointer = 0;
    XF_TNAME(XF_8UC1, XF_NPPC1) s;

    loop_height:
    for( unsigned int y = 0 ; y < 480 ; y++ ) {
        #pragma HLS LOOP_FLATTEN OFF
        loop_width:
        for( unsigned int x = 0 ; x < 640 ; x++ ) {
            #pragma HLS LOOP_FLATTEN OFF
            #pragma HLS PIPELINE II=1
            s = frame_in.read(read_pointer++);

            s += 1;

            frame_out.write(write_pointer++, s);
        }
    }
}
}

extern "C"
void
simple_add(hls::stream<ap_axiu<8, 1, 1, 1> > &video_in, hls::stream<ap_axiu<8, 1, 1, 1> > &video_out)
{
#pragma HLS INTERFACE ap_ctrl_none port=return

#if 0
increment:
    /*
    while (1) {
        ap_axiu<8, 1, 1, 1> v = video_in.read();
        v.data = v.data + 1;
        video_out.write(v);
        if (v.last) {
            break;
        }
    }
    */

#else
#pragma HLS dataflow
	xf::cv::Mat <XF_8UC1, 480, 640, XF_NPPC1> frame_in;
	xf::cv::Mat <XF_8UC1, 480, 640, XF_NPPC1> frame_out;

	xf::cv::AXIvideo2xfMat<XF_DTPIXELDEPTH(XF_8UC1, XF_NPPC1), XF_8UC1, 480, 640, XF_NPPC1>(video_in, frame_in);
    my_add(frame_in, frame_out);
	xf::cv::xfMat2AXIvideo<XF_DTPIXELDEPTH(XF_8UC1, XF_NPPC1), XF_8UC1, 480, 640, XF_NPPC1>(frame_out, video_out);
#endif
}
