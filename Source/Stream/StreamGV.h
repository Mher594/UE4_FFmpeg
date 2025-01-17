// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include <string>
#include "FFHeader.h"
#include "FFMuxer.h"

#include "Runtime/Core/Public/Misc/Paths.h"
#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "Runtime/Core/Public/Containers/Queue.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "StreamGV.generated.h"


/**
 * 
 */
UCLASS()
class STREAM_API UStreamGV : public UGameViewportClient
{
	GENERATED_BODY()

		void Draw(FViewport* Viewport, FCanvas* SceneCanvas) override;
	void BeginDestroy() override;
	bool isValidScreenSizes(FViewport *Viewport);


	// Adds single frame rgba data to queue
	void ReadAndSendFrame(FViewport* Viewport);

	int32 FrameIndex = 0;

	bool CanStream = false;
	bool StreamOver = false;

	// hold RGB data about single frame
	//TArray<FColor> ColorBuffer;
	TArray<uint8> SingleFrameBuffer;

	//std::string output_url = "C:/screen/test.flv";
	std::string output_url = "rtmp://stream-eu1hz.betconstruct.com:1935/virtual_sports/football";

	// FFMPEG stuff
	AVFormatContext* ofmt_ctx = nullptr;
	AVFormatContext* ifmt_ctx_audio = nullptr;
	AVFormatContext* ofmt_ctx_audio = nullptr;


	AVCodec* out_codec = nullptr;
	AVStream* out_stream = nullptr;
	AVCodecContext* out_codec_ctx = nullptr;
	SwsContext* swsctx = nullptr;
	AVFrame* frame = nullptr;
	bool ff_initialized = false;


	void ff_error_log(int ret_err);
	// main init func , only this must be called
	void ff_init(FViewport *Viewport);
	void ff_init_avformat_context();
	void ff_init_io_context();
	void ff_init_codec_stream();
	void ff_set_codec_params(int width, int height);
	void ff_init_sample_scaler(int width, int height);
	void ff_alloc_frame_buffer(int width, int height);
	void ff_write_frame();
	void ff_encode_and_write_frame(FViewport* Viewport);
	void ff_release_resources();

	void ff_audio_init();

private:
	FFMuxer* Muxer = nullptr;
};