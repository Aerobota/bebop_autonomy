#ifndef BEBOP_VIDEO_DECODER_H
#define BEBOP_VIDEO_DECODER_H

extern "C"
{
  #include "libARSAL/ARSAL_Print.h"
  #include "libARController/ARCONTROLLER_Error.h"
  #include "libARController/ARCONTROLLER_Frame.h"
  #include <libavcodec/avcodec.h>
  #include <libavformat/avformat.h>
  #include <libavformat/avio.h>
  #include <libswscale/swscale.h>
}

#include <string>

namespace bebop_autonomy
{

class VideoDecoder
{
private:
  static const char* LOG_TAG;

  bool codec_initialized_;
  AVFormatContext* format_ctx_ptr_;
  AVCodecContext* codec_ctx_ptr_;
  AVCodec* codec_ptr_;
  AVFrame* frame_ptr_;
  AVFrame* frame_rgb_ptr_;
  AVPacket av_packet;
  SwsContext* img_convert_ctx_ptr_;
  AVInputFormat* input_format_ptr_;
  uint8_t *av_buffer_;

  static void ThrowOnCondition(const bool cond, const std::string& message);
  bool InitCodec(const uint32_t width, const uint32_t height);
  void Cleanup();

  void ConvertFrameToRGB();

public:
  VideoDecoder();
  ~VideoDecoder();

  bool Decode(const ARCONTROLLER_Frame_t* ar_frame_ptr_);
  inline uint32_t GetFrameWidth() const {return codec_initialized_ ? codec_ctx_ptr_->width : 0;}
  inline uint32_t GetFrameHeight() const {return codec_initialized_ ? codec_ctx_ptr_->height : 0;}

  inline const uint8_t* GetFrameRGB() const {return av_buffer_;}
};

}  // namespace bebop_autonomy

#endif  // BEBOP_VIDEO_DECODER_H
