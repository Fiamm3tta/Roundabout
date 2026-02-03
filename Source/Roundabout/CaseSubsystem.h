// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "CaseSubsystem.generated.h"

/**
 * 
 */

class UCasePrimaryDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaseLoaded, const UCasePrimaryDataAsset*, LoadedCase);

USTRUCT(BlueprintType)
struct FRuntimeSentence
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGuid SentenceId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText Text;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FGameplayTagContainer Tags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    bool bCardSpawned = false;
};

UCLASS()
class ROUNDABOUT_API UCaseSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnCaseLoaded OnCaseLoaded;
	
	UFUNCTION(BlueprintCallable)
	void LoadCaseByName(FName CaseAssetName);

	UFUNCTION(BlueprintCallable)
	void LoadCaseById(const FPrimaryAssetId& CaseId);

	UFUNCTION(BlueprintPure)
	const TArray<FRuntimeSentence>& GetCurrentSentences() const;

	UFUNCTION(BlueprintPure)
	bool TryGetSentenceIndexById(FGuid SentenceId, int32& OutIndex) const;

private:
	UPROPERTY()
	const UCasePrimaryDataAsset* CurrentCase = nullptr;
	
	UPROPERTY()
	TArray<FRuntimeSentence> CurrentSentences;

	UPROPERTY()
	TMap<FGuid, int32> SentenceIndexById;

	FPrimaryAssetId PendingCaseId;

	void HandleCaseLoaded(FPrimaryAssetId CaseId);

	void InitializeRuntimeSentences();
};
