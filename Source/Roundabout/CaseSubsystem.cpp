// Fill out your copyright notice in the Description page of Project Settings.


#include "CaseSubsystem.h"
#include "CasePrimaryDataAsset.h"
#include "Engine/AssetManager.h"

void UCaseSubsystem::LoadCaseByName(FName CaseAssetName)
{
    const FPrimaryAssetId CaseId(TEXT("Case"), CaseAssetName);
    LoadCaseById(CaseId);
}

void UCaseSubsystem::LoadCaseById(const FPrimaryAssetId& CaseId)
{
    if (!CaseId.IsValid()) return;

    PendingCaseId = CaseId;
	UAssetManager& AM = UAssetManager::Get();

    CurrentCase = nullptr;
    CurrentSentences.Empty();
    SentenceIndexById.Empty();

	if (UObject* Obj = AM.GetPrimaryAssetObject(CaseId))
	{
        if (UCasePrimaryDataAsset* Case = Cast<UCasePrimaryDataAsset>(Obj))
        {
            CurrentCase = Case;
            InitializeRuntimeSentences();
            OnCaseLoaded.Broadcast(CurrentCase);
            return;
        }
	}

	FStreamableDelegate Done = FStreamableDelegate::CreateUObject(this, &UCaseSubsystem::HandleCaseLoaded, CaseId);

	AM.LoadPrimaryAsset(CaseId, TArray<FName>{}, Done);
}

void UCaseSubsystem::HandleCaseLoaded(FPrimaryAssetId CaseId)
{
    if (CaseId != PendingCaseId) return;
    
    UAssetManager& AM = UAssetManager::Get();
	UObject* Obj = AM.GetPrimaryAssetObject(CaseId);
    CurrentCase = Cast<UCasePrimaryDataAsset>(Obj);

    if(!CurrentCase) 
    {
        UE_LOG(LogTemp, Warning, TEXT("[Case] HandleCaseLoaded: object null or cast failed. Id=%s"), *CaseId.ToString());
        return;
    }

    InitializeRuntimeSentences();

    OnCaseLoaded.Broadcast(CurrentCase);
}

void UCaseSubsystem::InitializeRuntimeSentences()
{
    CurrentSentences.Empty();
    SentenceIndexById.Empty();
    if(!CurrentCase) return;
    
    const TArray<FCaseSentenceData>& Src = CurrentCase->Sentences;
    CurrentSentences.Reserve(Src.Num());
    SentenceIndexById.Reserve(Src.Num());
    
    for (int32 i = 0; i < Src.Num(); ++i)
    {   
        const FCaseSentenceData& S = Src[i];
        FRuntimeSentence R;

        R.SentenceId = S.SentenceId;
        R.Text = S.Text;
        R.Tags = S.Tags;
        
        const int32 NewIndex = CurrentSentences.Add(MoveTemp(R));
        SentenceIndexById.Add(S.SentenceId, NewIndex);
    }
}

const TArray<FRuntimeSentence>& UCaseSubsystem::GetCurrentSentences() const
{
    return CurrentSentences;
}

bool UCaseSubsystem::TryGetSentenceIndexById(FGuid SentenceId, int32& OutIndex) const
{
    if(const int32* Found = SentenceIndexById.Find(SentenceId))
    {
        OutIndex = *Found;
        return true;
    }

    return false;
}