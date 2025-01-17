// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

extern "C"
{
#ifndef __STDC_CONSTANT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavfilter/avfiltergraph.h"
#include "libavfilter/avfilter.h"
#include "libavutil/imgutils.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
#include "libavutil/opt.h"
#include "libavutil/error.h"
#include "libavutil/time.h"
#include "libswresample/swresample.h"
}
#include "Runtime/Engine/Classes/Sound/SoundWave.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioRecorder.generated.h"

USTRUCT(BlueprintType)
struct FSoundBufferEvent
{
	GENERATED_USTRUCT_BODY()
	
	USoundWave *TriggeredSoundWave;
	float StartTime;
	float EndTime;
};

UCLASS()
class STREAM_API AAudioRecorder : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioRecorder();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	void DecodeAudioFile();
	void ff_error_log(int);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	TArray<UAudioComponent *> AudioComponents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AudioRecord")
	TArray<USoundWave *> SoundWaves;

private:
	void DecodeSoundWave(USoundWave * PlayingSoundWave);

	UFUNCTION()
	void AudioPlayPercent(const USoundWave * PlayingSoundWave, const float PlayBackPercent);

	UFUNCTION()
	void AudioFinished();

	UFUNCTION()
	void AddNewEvent(USoundWave *SoundWave, float StartTime, float EndTime);

	TArray<FSoundBufferEvent> EventsBuffer;

	// TArray that holds all mixed audio information
	UPROPERTY()
	TArray<uint8> MainAudioBuffer;
};
