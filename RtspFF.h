#ifndef __RTSP_FF_H_
#define __RTSP_FF_H_

#include <string>
#include "time.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
	#include <libswscale/swscale.h>
}

typedef enum{
    FF_RTSP_RET_OK = 0,
    FF_RTSP_RET_INVILIDURL,
    FF_RTSP_RET_NOMEM,
    FF_RTSP_RET_OPENFAIL,
    FF_RTSP_RET_STREAMERR,
    FF_RTSP_RET_NOCODEC,
    FF_RTSP_RET_CODECERR
}FF_RTSP_RET;

typedef enum{
    FF_RTSP_STA_OPEN,
    FF_RTSP_STA_READY,
    FF_RTSP_STA_RUNNING,
    FF_RTSP_STA_CLOSED
}FF_RTSP_STATE;

enum {
    NAL_SLICE   =   1,
    NAL_DPA     =   2,
    NAL_DPB     =   3,
    NAL_DPC     =   4,
    NAL_IDR_SLICE = 5,
    NAL_SEI     =   6,
    NAL_SPS     =   7,
    NAL_PPS     =   8,
};

const unsigned char NAL_HEADER[4] = {0x00, 0x00, 0x00, 0x01};

struct AVInterruptCallbackMetadata
{
    timespec value;
    unsigned int timeout_after_ms;
    int timeout;
};

class RtspFF {
    public:
        RtspFF(const std::string &url, const std::string taskid="", const bool is_ivs = false):
        	_url(url),
        	_state(FF_RTSP_STA_CLOSED),
        	_vstrm(NULL),
        	_astrm(NULL),
        	_vdec(NULL),
        	_adec(NULL),
        	_is_ivs(is_ivs),
        	_task_id(taskid),
        	_frame(NULL),
        	_frame_bgr(NULL),
        	_width(1920),
        	_height(1080),
        	_sws_ctx(NULL)
        	{


        }
        ~RtspFF(){
            if (_state != FF_RTSP_STA_CLOSED) {
                close();
            }
        }
        int open(void);
        unsigned int get_video_frame(char *buf,const unsigned int &size);
        unsigned int get_video_frame_decode(char *buf,const unsigned int &size);
        int close(void);
        AVPixelFormat ConvertDeprecatedFormat(enum AVPixelFormat format);
        int get_width()
        {
        	return _width;
        }
        int get_height()
		{
			return _height;
		}

    private:
        bool _is_ivs;
        std::string _url;
        FF_RTSP_STATE _state;
        AVFormatContext *_rtsp_fmt;
        AVStream *_vstrm;
        AVStream *_astrm;
        AVCodec *_vdec;
        AVCodec *_adec;

        AVFrame *_frame;
        AVFrame *_frame_bgr;
        int _width;
        int _height;

        std::string _task_id;
        struct SwsContext *_sws_ctx;

    private:
        bool check_sps_pps(AVPacket &pkt);
        bool rtsp_url_valid(const std::string &url) { return true;}
        bool rtsp_open(void){return !(FF_RTSP_STA_CLOSED == _state);}
};

#endif
