// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseDataAsset.h"
#include "Engine/Texture2D.h"

float UNoiseDataAsset::TakeSample(const float XCoordNormalized, const float YCoordNormalized) const 
{
	// Get a read only pointer to the data at mip level 0, the original texture
	FTexture2DMipMap Mip{ NoiseTexture->PlatformData->Mips[0] };
	const FColor* Pixels{ static_cast<const FColor*>(Mip.BulkData.LockReadOnly()) };

	const int32 SizeX{ NoiseTexture->GetSizeX() };
	const int32 SizeY{ NoiseTexture->GetSizeY() };

	int32 SampleX{ FMath::FloorToInt(SizeX * XCoordNormalized) % SizeX };
	int32 SampleY{ FMath::FloorToInt(SizeY * YCoordNormalized) % SizeY };

	FColor SampledColor{ Pixels[SampleY * SizeX + SampleX] };

	// Now that the color has been sampled, we no longer need access to the texture data
	Mip.BulkData.Unlock();

	return FMath::GetMappedRangeValueClamped(
		FVector2D{ 0, 255 },
		FVector2D{ -1.0f, 1.0f },
		(SampledColor.R + SampledColor.G + SampledColor.B) / 3.0f
	);
}
