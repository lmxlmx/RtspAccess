#include "RtspFF.h"
extern "C"
{
    #include "libavcodec/avcodec.h"  
    #include "libavformat/avformat.h" 
    #include "libavutil/opt.h"
}

#include <string>
#include <iostream>
#include <unistd.h>
#include <time.h>

using namespace std;

//void exit_program(int ret);
//
//AVDictionary **setup_find_stream_info_opts(AVFormatContext *s,
//                                                   AVDictionary *codec_opts);
//int check_stream_specifier(AVFormatContext *s, AVStream *st, const char *spec);
//AVDictionary *filter_codec_opts(AVDictionary *opts, enum AVCodecID codec_id,
//                                AVFormatContext *s, AVStream *st, AVCodec *codec);
//
//void exit_program(int ret)
//{
//	exit(ret);
//}
//int check_stream_specifier(AVFormatContext *s, AVStream *st, const char *spec)
//{
//    int ret = avformat_match_stream_specifier(s, st, spec);
//    if (ret < 0)
//        av_log(s, AV_LOG_ERROR, "Invalid stream specifier: %s.\n", spec);
//    return ret;
//}
//
//AVDictionary *filter_codec_opts(AVDictionary *opts, enum AVCodecID codec_id,
//                                AVFormatContext *s, AVStream *st, AVCodec *codec)
//{
//    AVDictionary    *ret = NULL;
//    AVDictionaryEntry *t = NULL;
//    int            flags = s->oformat ? AV_OPT_FLAG_ENCODING_PARAM
//                                      : AV_OPT_FLAG_DECODING_PARAM;
//    char          prefix = 0;
//    const AVClass    *cc = avcodec_get_class();
//
//    if (!codec)
//        codec            = s->oformat ? avcodec_find_encoder(codec_id)
//                                      : avcodec_find_decoder(codec_id);
//
//    switch (st->codecpar->codec_type) {
//    case AVMEDIA_TYPE_VIDEO:
//        prefix  = 'v';
//        flags  |= AV_OPT_FLAG_VIDEO_PARAM;
//        break;
//    case AVMEDIA_TYPE_AUDIO:
//        prefix  = 'a';
//        flags  |= AV_OPT_FLAG_AUDIO_PARAM;
//        break;
//    case AVMEDIA_TYPE_SUBTITLE:
//        prefix  = 's';
//        flags  |= AV_OPT_FLAG_SUBTITLE_PARAM;
//        break;
//    }
//
//    while (t = av_dict_get(opts, "", t, AV_DICT_IGNORE_SUFFIX)) {
//        char *p = strchr(t->key, ':');
//
//        /* check stream specification in opt name */
//        if (p)
//            switch (check_stream_specifier(s, st, p + 1)) {
//            case  1: *p = 0; break;
//            case  0:         continue;
//            default:         exit_program(1);
//            }
//
//        if (av_opt_find(&cc, t->key, NULL, flags, AV_OPT_SEARCH_FAKE_OBJ) ||
//            !codec ||
//            (codec->priv_class &&
//             av_opt_find(&codec->priv_class, t->key, NULL, flags,
//                         AV_OPT_SEARCH_FAKE_OBJ)))
//            av_dict_set(&ret, t->key, t->value, 0);
//        else if (t->key[0] == prefix &&
//                 av_opt_find(&cc, t->key + 1, NULL, flags,
//                             AV_OPT_SEARCH_FAKE_OBJ))
//            av_dict_set(&ret, t->key + 1, t->value, 0);
//
//        if (p)
//            *p = ':';
//    }
//    return ret;
//}
//
//AVDictionary **setup_find_stream_info_opts(AVFormatContext *s,
//                                                   AVDictionary *codec_opts)
//{
//	int i;
//	AVDictionary **opts;
//
//	if (!s->nb_streams)
//		return NULL;
//	opts = (AVDictionary **)av_mallocz_array(s->nb_streams, sizeof(*opts));
//	if (!opts) {
//		av_log(NULL, AV_LOG_ERROR,
//			   "Could not alloc memory for stream options.\n");
//		return NULL;
//	}
//	for (i = 0; i < s->nb_streams; i++)
//		opts[i] = filter_codec_opts(codec_opts, s->streams[i]->codecpar->codec_id,
//									s, s->streams[i], NULL);
//	return opts;
//}
//
//static int interrupt_cb(void *timestamp)
//{
//    if (*(long*)timestamp == 0){
//        return 0;
//    }
//    else
//    {
//        long timestamp1 = time(0);
//        if (timestamp1 - *(long*)timestamp > 5)
//        {
//            return 1;
//        }
//    }
//    return 0;
//}


//static inline void get_monotonic_time(timespec *time)
//{
//	clock_gettime(CLOCK_MONOTONIC, time);
//}
//static inline timespec get_monotonic_time_diff(timespec start, timespec end)
//{
//    timespec temp;
//    if (end.tv_nsec - start.tv_nsec < 0)
//    {
//        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
//        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
//    }
//    else
//    {
//        temp.tv_sec = end.tv_sec - start.tv_sec;
//        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
//    }
//    return temp;
//}
//
//static inline double get_monotonic_time_diff_ms(timespec time1, timespec time2)
//{
//    timespec delta = get_monotonic_time_diff(time1, time2);
//    double milliseconds = delta.tv_sec * 1000 + (double)delta.tv_nsec / 1000000.0;
//
//    return milliseconds;
//}
//
//static inline int _opencv_ffmpeg_interrupt_callback(void *ptr)
//{
//    AVInterruptCallbackMetadata* metadata = (AVInterruptCallbackMetadata*)ptr;
//
//    if (metadata->timeout_after_ms == 0)
//    {
//        return 0; // timeout is disabled
//    }
//
//    timespec now;
//    get_monotonic_time(&now);
//
//    metadata->timeout = get_monotonic_time_diff_ms(metadata->value, now) > metadata->timeout_after_ms;
//
//    return metadata->timeout ? -1 : 0;
//}

//AVCodecContext * RtspFF::GetAVCodecContext(const AVCodecParameters *codecpar)
//{
//	AVCodecContext * enc = 	avcodec_alloc_context3(NULL);
//	if(enc == NULL)
//	{
//		return NULL;
//	}
//	if(avcodec_parameters_to_context(enc, codecpar) < 0)
//	{
//		cout << _task_id <<" fail to avcodec_parameters_to_context" << endl;
//		return NULL;
//	}
//	return enc;
//
//}

int RtspFF::open(void)
{
    close();
    int ret = 0;
    int err = 0;
    AVDictionary * opts = NULL;
    int videoStream_index = -1;
    int scan_all_pmts_set = 0;
    do {
        if(!rtsp_url_valid(_url))
        {
            _state = FF_RTSP_STA_CLOSED;
            ret = FF_RTSP_RET_INVILIDURL;
            break;
        }

        if(_state != FF_RTSP_STA_CLOSED)
        {
            ret = FF_RTSP_RET_OK;
            break;
        }
        cout << _task_id<<" av_register_all"<< endl;
        av_register_all();
        cout << _task_id<<" avformat_network_init"<< endl;
        avformat_network_init();
        cout << _task_id<<" avformat_alloc_context"<< endl;
        AVFormatContext *formatCtx = avformat_alloc_context();
        if (!formatCtx){
            ret = FF_RTSP_RET_NOMEM;
            break;
        }
        cout << _task_id << " av_dict_set"<< endl;
        cout << _task_id<<" stimeout"<< endl;
        av_dict_set(&opts, "stimeout", "5000000", 0);
        cout << _task_id<<" buffer_size"<< endl;
        av_dict_set(&opts, "buffer_size", "10240000", 0);
        cout << _task_id<<" max_delay"<< endl;
        av_dict_set(&opts, "max_delay", "3000000", 0);
        cout << _task_id<<" rtsp_transport"<< endl;
        av_dict_set(&opts, "rtsp_transport", "tcp", 0);
        cout << _task_id<<" threads"<< endl;
        av_dict_set(&opts, "threads", "auto", 0);

        cout << _task_id<<" avformat_open_input"<< endl;
        err = avformat_open_input(&formatCtx, _url.c_str(), NULL, &opts);
        cout << _task_id<<" avformat_open_input ret:"<< err << endl;
        if (err < 0) {
            if (formatCtx){
                avformat_close_input(&formatCtx);
                avformat_free_context(formatCtx);
            }
            _state = FF_RTSP_STA_CLOSED;
            ret = FF_RTSP_RET_OPENFAIL;
            break;
        }
        cout << _task_id<<" avformat_find_stream_info"<< endl;
        err = avformat_find_stream_info(formatCtx, NULL);
        cout << _task_id<<" avformat_find_stream_info ret"<< err << endl;
        if ( err < 0) {
			avformat_close_input(&formatCtx);
			avformat_free_context(formatCtx);
			_state = FF_RTSP_STA_CLOSED;
			ret = FF_RTSP_RET_OPENFAIL;
			break;
		}

        cout << _task_id << " formatCtx->nb_streams"<< formatCtx->nb_streams << endl;
        AVStream *strm = NULL;
        for (int i = 0; i < formatCtx->nb_streams; i++)
        {
            strm = formatCtx->streams[i];
            cout <<_task_id << " stream:" <<i << " codec_type:"<< strm->codec->codec_type << endl;
            switch (strm->codec->codec_type)
            {
            case AVMEDIA_TYPE_AUDIO :
                _astrm = strm;
                break;
            case AVMEDIA_TYPE_VIDEO :
                _vstrm = strm;
                break;
            default :
                break;
            }
        }

        if(_vstrm)
        {
        	cout << _task_id <<" vstrm avcodec_find_decoder"<< endl;
            _vdec = avcodec_find_decoder (_vstrm->codec->codec_id);
            if(_vdec == NULL)
            {
                cout << _task_id <<" fail to find decoder for codec id:" <<  _vstrm->codec->codec_id << endl;
                avformat_close_input(&formatCtx);
                avformat_free_context(formatCtx);
                _state = FF_RTSP_STA_CLOSED;
                ret = FF_RTSP_RET_NOCODEC;
                break;
            }
            cout << _task_id <<" vstrm avcodec_open2 "<< _url << endl;
            ret = avcodec_open2(_vstrm->codec,_vdec,NULL);
            if( ret  <0)
            {
                cout << _task_id <<" fail to open decoder" << string(_vdec->name) << endl;
                avformat_close_input(&formatCtx);
                avformat_free_context(formatCtx);
                _state = FF_RTSP_STA_CLOSED;
                ret = FF_RTSP_RET_CODECERR;
                break;
            }
            _width = _vstrm->codec->width;
            _height = _vstrm->codec->height;
            _frame_bgr = av_frame_alloc();
            _frame = av_frame_alloc();
        }

        if(_astrm)
        {
        	cout << _task_id << " astrm avcodec_find_decoder " << endl;
            _adec = avcodec_find_decoder (_astrm->codec->codec_id);
            if(_adec == NULL)
            {
                cout << _task_id << " fail to find decoder for codec id:" <<  _astrm->codec->codec_id << endl;
                avformat_close_input(&formatCtx);
                avformat_free_context(formatCtx);

                if(_vdec)
                {
                    avcodec_close(_vstrm->codec);
                }
                _state = FF_RTSP_STA_CLOSED;
                ret = FF_RTSP_RET_NOCODEC;
                break;
            }
            cout << _task_id << " astrm avcodec_open2 "<< _url << endl;
            ret = avcodec_open2(_astrm->codec,_adec,NULL);
            if(ret < 0)
            {
                cout << _task_id << " fail to open decoder" << string(_adec->name) << endl;
                avformat_close_input(&formatCtx);
                avformat_free_context(formatCtx);

                if(_vdec)
                {
                    avcodec_close(_vstrm->codec);
                }
                _state = FF_RTSP_STA_CLOSED;
                ret = FF_RTSP_RET_CODECERR;
                break;
            }
        }
        _rtsp_fmt = formatCtx;
        _state = FF_RTSP_STA_OPEN;
        ret = FF_RTSP_RET_OK;
    } while(0);

    av_dict_free(&opts);
    return ret;
}

bool RtspFF::check_sps_pps(AVPacket &pkt)
{
    bool need_sps_pps = false;
    // I-Frame SPS PPS checking
    if (pkt.flags & AV_PKT_FLAG_KEY)
    {
        // 仅仅关键帧需要SPS PPS
        if (_vstrm->codec->codec_id == AV_CODEC_ID_H264)
        {
            // NAL TYPE
            // forbidden_zero   1bit
            // nal_ref_idc      2bit
            // nal_unit_type    5bit
            // CHECK NAL Header
            if ((pkt.data[0] == NAL_HEADER[0])
                    && (pkt.data[1] == NAL_HEADER[1])
                    && (pkt.data[2] == NAL_HEADER[2])
                    && (pkt.data[3] == NAL_HEADER[3]) )
            {
                if (pkt.data[4] & 0x1F != NAL_SPS
                        && pkt.data[4] & 0x1F != NAL_PPS)
                {
                    need_sps_pps = true;
                }
            }
        }
        else if (_vstrm->codec->codec_id == AV_CODEC_ID_H265)
        {
            // TODO H265 support
        	if ((pkt.data[0] == NAL_HEADER[0])
					&& (pkt.data[1] == NAL_HEADER[1])
					&& (pkt.data[2] == NAL_HEADER[2])
					&& (pkt.data[3] == NAL_HEADER[3]))
			{
        		uint8_t nalu_type = (pkt.data[4] & 0x7E) >> 1;
        		switch(nalu_type)
        		{
        			case 32: //vps
        				break;
        			case 33: //sps
        				break;
        			case 34: //pps
        				break;
//        			case 39: //prefix sei
//        				break;
//        			case 40: //suffix sei
//        				break;
        			default:
        				need_sps_pps = true;
        				break;
        		}

			}
        }
    }

    return need_sps_pps;
}


unsigned int RtspFF::get_video_frame(char *buf,const unsigned int &size)
{
	cout << _task_id <<" get_video_frame " << endl;
    int ret = FF_RTSP_RET_OK;
    if(!rtsp_open())
    {
        ret = open();
        if(ret != FF_RTSP_RET_OK)
        {
            return 0;
        }
    }

    if(NULL == _vstrm)
    {
        return 0;
    }

    AVPacket avPacket;
	av_init_packet(&avPacket);
	avPacket.size = 0;
	avPacket.data = NULL;

    unsigned int size_rd = size;
    while(1)
    {
    	cout <<_task_id <<" av_read_frame"<< endl;
        int ret = av_read_frame(_rtsp_fmt, &avPacket);
        std::cout << _task_id <<" av read frame ret:" << ret << std::endl;
        if(ret < 0)
        {
            char errorbuf[1024] = {0};
            av_strerror(ret, errorbuf, sizeof(errorbuf));
            std::cout << _task_id <<" av read frame failure: " << errorbuf << std::endl;
            return ret;
        }
        std::cout << _task_id <<" _vstrm->index:"<<_vstrm->index<<" avPacket.stream_index:" << avPacket.stream_index << std::endl;
        if(_vstrm->index == avPacket.stream_index)
        {
            size_rd = avPacket.size > size ? size : avPacket.size;

            bool need_sps_pps = check_sps_pps(avPacket);
            if (need_sps_pps) {
                memcpy(buf, _vstrm->codec->extradata, _vstrm->codec->extradata_size);
                memcpy(buf + _vstrm->codec->extradata_size, avPacket.data, size_rd);
                size_rd += _vstrm->codec->extradata_size;
            } else {
                memcpy(buf, avPacket.data, size_rd);
            }
            //printf("AvFrame Dts: %ld, Pts: %ld, time_base: %f, flag: 0x%x, duration: %ld\n", avPacket.dts, avPacket.pts,
            //                (double)_vstrm->time_base.num / (double)_vstrm->time_base.den,
            //                avPacket.flags, avPacket.duration);
            break;
        }
        else
        {
            usleep(1000);
            av_packet_unref(&avPacket);
            continue;
        }
    }
    av_packet_unref(&avPacket);
    return size_rd;
}

AVPixelFormat RtspFF::ConvertDeprecatedFormat(enum AVPixelFormat format)
{
    switch (format)
    {
    case AV_PIX_FMT_YUVJ420P:
        return AV_PIX_FMT_YUV420P;
        break;
    case AV_PIX_FMT_YUVJ422P:
        return AV_PIX_FMT_YUV422P;
        break;
    case AV_PIX_FMT_YUVJ444P:
        return AV_PIX_FMT_YUV444P;
        break;
    case AV_PIX_FMT_YUVJ440P:
        return AV_PIX_FMT_YUV440P;
        break;
    default:
        return format;
        break;
    }
}

unsigned int RtspFF::get_video_frame_decode(char *buf,const unsigned int &size)
{
    int ret = FF_RTSP_RET_OK;
    if(!rtsp_open())
    {
        ret = open();
        if(ret != FF_RTSP_RET_OK)
        {
            return 0;
        }
    }

    if(NULL == _vstrm)
    {
        return 0;
    }

    AVPacket avPacket;
    av_init_packet(&avPacket);

    unsigned int size_rd = size;
    while(1)
    {
        int pic_get = 0;
        ret = av_read_frame(_rtsp_fmt, &avPacket);
        if(ret < 0){
        	char errorbuf[1024] = {0};
			av_strerror(ret, errorbuf, sizeof(errorbuf));
			std::cout << _task_id <<" av read frame failure: " << errorbuf << std::endl;
			return ret;
        }

        if(_vstrm->index == avPacket.stream_index)
        {
            // decode the frame and then copy the YUV to user
            ret = avcodec_decode_video2(_vstrm->codec, _frame, &pic_get, &avPacket);
            if(ret <= 0)
            {
                cout << "fail to decode one frame,size[" << avPacket.size << "]" << endl;
                av_packet_unref(&avPacket);
                return 0;
            }

            if(pic_get == 0)
            {
                continue;
            }

            if( _sws_ctx == NULL)
			{
				// Some sws_scale optimizations have some assumptions about alignment of data/step/width/height
				// Also we use coded_width/height to workaround problem with legacy ffmpeg versions (like n0.8)
				int buffer_width = _vstrm->codec->coded_width, buffer_height = _vstrm->codec->coded_height;

				_sws_ctx = sws_getCachedContext(
						_sws_ctx,
						buffer_width, buffer_height,
						ConvertDeprecatedFormat(_vstrm->codec->pix_fmt),
						buffer_width, buffer_height,
						AV_PIX_FMT_BGR24,
						SWS_BICUBIC,
						NULL, NULL, NULL
						);
				if(_sws_ctx == NULL)
				{
					cout << "fail to get sws context" << endl;
					av_packet_unref(&avPacket);
					size_rd = 0;
					break;
				}
				av_frame_unref(_frame_bgr);
				_frame_bgr->format = AV_PIX_FMT_BGR24;
				_frame_bgr->width = buffer_width;
				_frame_bgr->height = buffer_height;
				if (0 != av_frame_get_buffer(_frame_bgr, 0))
				{
					cout << "fail to get sws context" << endl;
					av_packet_unref(&avPacket);
					size_rd = 0;
					break;
				}
			}
            sws_scale(
				_sws_ctx,
				_frame->data,
				_frame->linesize,
				0, _vstrm->codec->coded_height,
				_frame_bgr->data,
				_frame_bgr->linesize
			);
            memcpy(buf, &_frame_bgr->data[0][0], _width*_height*3);
            size_rd = _width*_height*3;
			break;

//            if(AV_PIX_FMT_YUV420P == avFrame->format)
//            {
//
//                for(int i = 0;i < avFrame->height;i++)
//                    memcpy(buf + avFrame->width * i, avFrame->data[0]  + avFrame->linesize[0] * i, avFrame->width);
//                for(int i = 0;i < avFrame->height / 2;i++)
//                    memcpy(buf + avFrame->height * avFrame->linesize[0] + i * avFrame->linesize[1], \
//                    avFrame->data[1]  + avFrame->linesize[1] * i, avFrame->linesize[1]);
//                for(int i = 0;i < avFrame->height / 2 ;i++)
//                    memcpy(buf + avFrame->height * avFrame->linesize[0] + avFrame->height / 2 *avFrame->linesize[1] + i * avFrame->linesize[2], \
//                    avFrame->data[2]  + avFrame->linesize[2] * i, avFrame->linesize[2]);
//
//                size_rd = avFrame->height * avFrame->linesize[0] + avFrame->height / 2 *avFrame->linesize[1] + avFrame->height / 2  * avFrame->linesize[2];
//            }
//            else
//            {
//                cout << "YUV format not support,ID[" <<  avFrame->format << "]" <<endl;
//                size_rd = 0;
//            }
//            break;
        }
        else
        {
//            usleep(1000);
            continue;
        }
    }
//    av_free(avFrame);
    av_packet_unref(&avPacket);
    return size_rd;
}

int RtspFF::close(void)
{
    if(_state == FF_RTSP_STA_CLOSED)
    {
        return FF_RTSP_RET_OK;
    }

    if( _sws_ctx )
	{
    	sws_freeContext(_sws_ctx);
		_sws_ctx = NULL;
	}

    if( _frame )
    {
    	av_frame_free(&_frame);
    }
    if( _frame_bgr )
	{
		av_frame_free(&_frame_bgr);
	}

    if(_adec)
	{
		avcodec_close(_astrm->codec);
	}

	if(_vdec)
	{
		avcodec_close(_vstrm->codec);
	}

	if(_rtsp_fmt != NULL)
	{
		avformat_close_input(&_rtsp_fmt);
		avformat_free_context(_rtsp_fmt);
	}
	_state = FF_RTSP_STA_CLOSED;
	return FF_RTSP_RET_OK;
}
