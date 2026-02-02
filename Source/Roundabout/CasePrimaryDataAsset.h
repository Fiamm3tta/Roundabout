// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CasePrimaryDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FCaseSentenceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (NoResetToDefault))
	FGuid SentenceId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (NoResetToDefault))
	FText Text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (NoResetToDefault))
	FGameplayTagContainer Tags;
};

UCLASS()
class ROUNDABOUT_API UCasePrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId(FPrimaryAssetType(TEXT("Case")), GetFName());
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text")
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Text", meta = (MultiLine = "true"))
	FText FullText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Case")
	TArray<FCaseSentenceData> Sentences;
	
	UFUNCTION(CallInEditor, BlueprintCallable, Category = "Case")
	void SplitFullText();
};
