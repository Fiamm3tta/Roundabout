// Fill out your copyright notice in the Description page of Project Settings.


#include "CasePrimaryDataAsset.h"

#if WITH_EDITOR
static FString NormalizeLine(const FString& In)
{
    return In.TrimStartAndEnd();
}
void UCasePrimaryDataAsset::SplitFullText()
{
    Modify();
    Sentences.Reset();

    FString Text = FullText.ToString();

    Text.ReplaceInline(TEXT("\r\n"), TEXT("\n"));
    Text.ReplaceInline(TEXT("\r"), TEXT("\n"));

    TArray<FString> Lines;
    Text.ParseIntoArrayLines(Lines, false);

    TArray<FCaseSentenceData> NewSentenceData;
    NewSentenceData.Reserve(Lines.Num());

    for(FString& Line : Lines)
    {
        FString Normalized = NormalizeLine(Line);
        FGuid NewSentenceId = FGuid::NewGuid();
        FCaseSentenceData NewSentence;

        NewSentence.Text = FText::FromString(Normalized);
        NewSentence.SentenceId = NewSentenceId;

        NewSentenceData.Add(MoveTemp(NewSentence));
    }
    
    Sentences = MoveTemp(NewSentenceData);
    MarkPackageDirty();
}
#endif