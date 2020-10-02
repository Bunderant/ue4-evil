// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NoiseDataAsset.generated.h"

class UTexture2D;

/**
 * 
 */
UCLASS(BlueprintType)
class EVIL_API UNoiseDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:

	/** Noise Texture can be of any size > 0, but must have its compression set to "VectorDisplacementMap". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures", meta = (AllowPrivateAccess = "true"))
	UTexture2D* NoiseTexture;

public:

	/**
	 * Samples the noise texture at the given UV coordinates, mapping the sample to the range [-1, 1]. 
	 * UV coords will wrap if outside the range [0, 1]. 
	 */
	UFUNCTION(BlueprintCallable)
	float TakeSample(float XCoordNormalized, float YCoordNormalized) const;
};
