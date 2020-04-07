// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Console/Cartridge.h"
#include "CoreMinimal.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount 
{	
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	private:
	virtual void InitGame();
	virtual void HandleInput(const FString& Input);

	virtual bool IsIsogram(const FString& Word) const;
	virtual FBullCowCount GetBullsAndCowsCount(const FString& Guess) const;
	
	virtual void PromptReplay() const;
	virtual FString GenerateRandomWord() const;

	FString HiddenWord;
	int32 Lives;
	
	bool bGameEnded;
};
