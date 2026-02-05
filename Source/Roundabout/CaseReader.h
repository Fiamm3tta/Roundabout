// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CaseSubsystem.h"
#include "CaseReader.generated.h"

/**
 * 
 */

class URichTextBlock;

UCLASS()
class ROUNDABOUT_API UCaseReader : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Make Body Text")
    void SetSentences(const TArray<FRuntimeSentence>& InSentences);
	
protected:
	UPROPERTY(meta=(BindWidget))
	URichTextBlock* RichText = nullptr;

	virtual void NativeConstruct() override;

private:
	FString BuildMarkup(const TArray<FRuntimeSentence>& InputSentences) const;

	static FString EscapeForRichText(const FString& Input);
};
