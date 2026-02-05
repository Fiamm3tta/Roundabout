// Fill out your copyright notice in the Description page of Project Settings.


#include "CaseReader.h"
#include "Components/RichTextBlock.h"
#include "SentenceDecorator.h"

void UCaseReader::SetSentences(const TArray<FRuntimeSentence>& InputSentences)
{
    if (!RichText) return;

    const FString Markup = BuildMarkup(InputSentences);
    RichText->SetText(FText::FromString(Markup));
}

FString UCaseReader::BuildMarkup(const TArray<FRuntimeSentence>& InputSentences) const
{
    FString Output;
    Output.Reserve(InputSentences.Num() * 32);

    for(int32 i = 0; i < InputSentences.Num(); i++)
    {
        FString Sentence = InputSentences[i].Text.ToString();
        Sentence = EscapeForRichText(Sentence);

        if (Sentence.IsEmpty())
        {
            Output += TEXT("\n\n");
            continue;
        }

        Output += TEXT("<s idx=\"");
        Output += FString::FromInt(i);
        Output += TEXT("\">");
        Output += Sentence;
        Output += TEXT("</>");

        if(i + 1 < InputSentences.Num())
        {
            Output += TEXT(" ");
        }
    }

    return Output;
}

FString UCaseReader::EscapeForRichText(const FString& Input)
{
    FString String = Input;
    String.ReplaceInline(TEXT("&"), TEXT("&amp;"));
    String.ReplaceInline(TEXT("<"), TEXT("&lt;"));
    String.ReplaceInline(TEXT(">"), TEXT("&gt;"));
    return String;
}

void UCaseReader::NativeConstruct()
{
    Super::NativeConstruct();

    if (!RichText) return;

}