#pragma once

#include "CoreMinimal.h"

#define LogLine() { CLog::Log(__FILE__, __FUNCTION__, __LINE__); }
#define PrintLine() { CLog::Print(__FILE__, __FUNCTION__, __LINE__); }

class LISTENSERVERPROJECT_API CLog
{
public:
	static void Log(int32 InValue);
	static void Log(uint32 InValue);
	static void Log(float InValue);
	static void Log(const FString& InValue);
	static void Log(const FVector& InValue);
	static void Log(const FRotator& InValue);
	static void Log(const UObject* InValue);
	static void Log(const FString& InFileName, const FString& InFuncName, int32 InLineNumber);

	static void Print(bool InValue, int32 InKey, float InDuration, FColor InColor = FColor::Red);
	static void Print(int32 InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	static void Print(uint32 InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	static void Print(float InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	static void Print(const FString& InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	static void Print(const FVector& InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	static void Print(const FRotator& InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	static void Print(const UObject* InValue, int32 InKey = -1, float InDuration = 10, FColor InColor = FColor::Blue);
	static void Print(const FString& InFileName, const FString& InFuncName, int32 InLineNumber);

	static void LogAndPrint(int32 InValue);
	static void LogAndPrint(uint32 InValue);
	static void LogAndPrint(float InValue);
	static void LogAndPrint(const FString& InValue);
	static void LogAndPrint(const FVector& InValue);
	static void LogAndPrint(const FRotator& InValue);
	static void LogAndPrint(const UObject* InValue);
	static void LogAndPrint(const FString& InFileName, const FString& InFuncName, int32 InLineNumber);
};