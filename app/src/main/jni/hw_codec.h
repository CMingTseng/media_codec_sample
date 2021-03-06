/////////////////////////////////////////////////////////////////////////////////////
#ifndef __HW_CODEC_H__
#define __HW_CODEC_H__

#include "assert.h"
#include "ctype.h"
#include "codec_app_def.h"
//#include <new>
#include "inttypes.h"


#define SYSTEM_MEMORY              0
#define D3D9_MEMORY                1
#define D3D11_MEMORY               2

#define MCODEC_SUCCEED             0
#define MCODEC_ERROR              -1

#define VIDEO_CODEC_TYPE_AVC       0
#define VIDEO_CODEC_TYPE_MJPEG     1
#define VIDEO_CODEC_TYPE_HEVC      2
#define VIDEO_CODEC_TYPE_VC1       3


//the Intel MSDK encoder single pipeline interface parameters.
typedef struct
{
    uint32_t  InStreamType;      // Input color format
    uint32_t  InFrameRate;       // Input Target encoding framerate
    uint32_t  InWidth;           // Input picture width
    uint32_t  InHeight;          // Input picture height
    
    uint32_t  nFrameRate;        // Target encoding framerate
    uint32_t  nWidth;            // Input picture width
    uint32_t  nHeight;           // Input picture height
    uint32_t  nTargetKbps;       // Target encoding bitrate
    uint32_t  nTemporalLayers;   // The number of temporal layers
    uint32_t  nSpatialId;        // the output spatial_id, 0~3.
    uint32_t  nMemType;          // the memory type for frame surface
    
    uint32_t  SpsLength;         // The incoming SPS nal_unit length
    uint32_t  PpsLength;         // The incoming PPS nal_unit length
    uint8_t   SpsNalUnit[200];   // The incoming SPS nal_unit data.
    uint8_t   PpsNalUnit[200];   // The incoming PPS nal_unit data.
    
}MSdkInputParam;

/////////////////////////////////////////////////////////////////////////////////////
    
    //Create the Intel MSDK encoder pipeline, and configure it.
    int32_t OpenEncoder(MSdkInputParam *InputParam);
    
    //Delete the Intel MSDK encoder and release memory.
    int32_t CloseEncoder(void);
    
    //Encode a frame asynchronously, without outputing bitstream.
    int32_t EncodeFrame(SSourcePicture* pSrcPic, SLayerBSInfo* pBsLayer);
    
    //Synchronize the encoder and output bitstream data.
    int32_t GetBitstream(SLayerBSInfo* pBsLayer);
    
    //Update the target bitrate online of specified pipeline.
    int32_t UpdateBitrate(uint32_t Bitrate, uint32_t Framerate);
    
    //Request to encoder the current frame as IDR frame.
    int32_t InsertKeyFrame(void);
    

   

#endif  // End of __GPU_MSDK_CODEC_H__

/////////////////////////////////////////////////////////////////////////////////////
