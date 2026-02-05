// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlockDecorator.h"
#include "SentenceDecorator.generated.h"

/**
 * 
 */
UCLASS()
class ROUNDABOUT_API USentenceDecorator : public URichTextBlockDecorator
{
	GENERATED_BODY()
	
public:
	virtual TSharedPtr<ITextDecorator> CreateDecorator(URichTextBlock* InOwner) override;
};
