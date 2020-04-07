// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "BullCowCartridge.h"
#include "HiddenWordsBank.h"
#include "CoreMinimal.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();
}

void UBullCowCartridge::InitGame()
{
    ClearScreen();
    bGameEnded = false;
    HiddenWord = GenerateRandomWord(); // Randomize word.
    Lives = pow(HiddenWord.Len(), 2);

    PrintLine(TEXT("Hi there! Welcome to the BullCowGame."));
    PrintLine(TEXT("In this game, you'll need to guess a chosen word.\n"));

    PrintLine(TEXT("Notice that you only have %i lives."), Lives);
    PrintLine(TEXT("Every mistake will cost you one life.\n"));

    PrintLine(TEXT("The length of the hidden word is %i"), HiddenWord.Len());
    PrintLine(TEXT("Do you have a guess in mind?"));
    PrintLine(TEXT("Press TAB to access the terminal:"));

    // PrintLine(TEXT("%s"), *HiddenWord); // DEBUG
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    HandleInput(Input);
}

void UBullCowCartridge::HandleInput(const FString &Input)
{
    FString Guess = Input.ToLower();

    if (bGameEnded)
    {
        if (Input == "")
        {
            InitGame();
        }
        else
        {
            PromptReplay();
        }
    }
    else
    {
        // Validate Guess
        if (HiddenWord.Len() != Guess.Len())
        {
            PrintLine(TEXT("The length of your word must be %i!"), HiddenWord.Len());
            return;
        }
        else if (!IsIsogram(Guess))
        {
            PrintLine(TEXT("Your guess must be an isogram!"));
            return;
        }

        if (Guess == HiddenWord)
        {
            PrintLine(TEXT("That is correct!"));
            PrintLine(TEXT("You Won!"));
            bGameEnded = true;

            PromptReplay();
        }
        else
        {
            const FBullCowCount BullCowCount = GetBullsAndCowsCount(Guess);

            PrintLine(TEXT("That is not correct, but you hit %i bulls and %i cows."), BullCowCount.Bulls, BullCowCount.Cows);
            PrintLine(TEXT("You have %i lives left."), --Lives);

            bGameEnded = Lives == 0;

            if (bGameEnded)
            {
                PrintLine(TEXT("The hidden word was - %s"), *HiddenWord);
                PromptReplay();
            }
            else
            {
                PrintLine(TEXT("Guess again:"));
            }
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString &Word) const
{

    // Validate isogram
    for (int32 i = 0; i < Word.Len(); i++)
    {
        for (int32 j = i + 1; j < Word.Len(); j++)
        {
            if (Word.GetCharArray()[i] == Word.GetCharArray()[j])
            {
                return false;
            }
        }
    }

    return true;
}

FBullCowCount UBullCowCartridge::GetBullsAndCowsCount(const FString &Guess) const
{
    FBullCowCount Count;

    for (int i = 0; i < Guess.Len(); i++)
    {
        if (Guess.GetCharArray()[i] == HiddenWord.GetCharArray()[i])
        {
            Count.Bulls++;
        }
        else if (HiddenWord.GetCharArray().Contains(Guess.GetCharArray()[i]))
        {
            Count.Cows++;
        }
    }

    return Count;
}

void UBullCowCartridge::PromptReplay() const
{
    PrintLine(TEXT("Press ENTER to play again"));
    PrintLine(TEXT("Press TAB to leave"));
}

FString UBullCowCartridge::GenerateRandomWord() const 
{
    FString Candidate;

    Candidate = HiddenWords[FMath::RandRange(0, HiddenWords.Num() - 1)];

    while (!IsIsogram(Candidate) || Candidate.Len() > 5)
    {
        HiddenWords.Remove(Candidate);
        Candidate = HiddenWords[FMath::RandRange(0, HiddenWords.Num() - 1)];
    }

    HiddenWords.Remove(Candidate);
    return Candidate;
}