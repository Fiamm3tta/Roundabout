// Fill out your copyright notice in the Description page of Project Settings.


#include "SentenceDecorator.h"
#include "Components/RichTextBlock.h"
#include "Framework/Text/RichTextMarkupProcessing.h"
#include "Framework/Text/SlateTextRun.h"
#include "Framework/Text/SlateWidgetRun.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Text/STextBlock.h"
#include "Styling/CoreStyle.h"

class FSentenceDecorator : public FRichTextDecorator
{
public:
    explicit FSentenceDecorator(URichTextBlock* InOwner) : FRichTextDecorator(InOwner) {}
    
    virtual bool Supports(const FTextRunParseResults& RunParseResult, const FString& Text) const override
    {
        // UE_LOG(LogTemp, Warning, TEXT("[Decorator] Tag: %s"), *RunParseResult.Name);
        return RunParseResult.Name == TEXT("s");
    }

    virtual TSharedPtr<SWidget> CreateDecoratorWidget(
        const FTextRunInfo& RunInfo,
        const FTextBlockStyle& DefaultTextStyle) const override
    {
        // UE_LOG(LogTemp, Warning, TEXT("[Decorator] Widget for tag, idx=%s, content=%s"),
        // RunInfo.MetaData.Contains(TEXT("idx")) ? *(*RunInfo.MetaData.Find(TEXT("idx"))) : TEXT("none"),
        // *RunInfo.Content.ToString());

        const FText& ContentText = RunInfo.Content;

        int32 SentenceIdx = INDEX_NONE;
        if (const FString* IdxStr = RunInfo.MetaData.Find(TEXT("idx")))
        {
            SentenceIdx = FCString::Atoi(**IdxStr);
        }

        return SNew(SButton)
            .ButtonStyle(FCoreStyle::Get(), "NoBorder")
            .ContentPadding(FMargin(0.f))
            .OnClicked_Lambda([SentenceIdx]()
            {
                UE_LOG(LogTemp, Log, TEXT("Sentence clicked: %d"), SentenceIdx);
                return FReply::Handled();
            })
        [
            SNew(SBox)
            .HAlign(HAlign_Fill)
            [
                SNew(STextBlock)
                    .Text(ContentText)
                    .TextStyle(&DefaultTextStyle)
                    .AutoWrapText(true)
            ]
        ];
    }
};

TSharedPtr<ITextDecorator> USentenceDecorator::CreateDecorator(URichTextBlock* InOwner)
{
    return MakeShared<FSentenceDecorator>(InOwner);
}