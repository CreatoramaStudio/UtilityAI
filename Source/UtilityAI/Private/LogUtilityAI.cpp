#include "LogUtilityAI.h"
#include "VisualLogger/VisualLogger.h"

DEFINE_LOG_CATEGORY(LogUtilityAI);

void FLogUtilityAI::ConsoleInfo(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogUtilityAI, Display, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::White, Description);
	}
}

void FLogUtilityAI::ConsoleWarning(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogUtilityAI, Warning, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Yellow, Description);
	}
}

void FLogUtilityAI::ConsoleError(const FString& Description, const bool bShowOnScreen, const float Time)
{
	UE_LOG(LogUtilityAI, Error, TEXT("%s"), *Description);

	if (bShowOnScreen && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Time, FColor::Red, Description);
	}
}

void FLogUtilityAI::VisLogString(const AActor* Actor, const FString& Description, const FColor Color)
{
	UE_VLOG(Actor, LogUtilityAI, Log, TEXT("%s"), *Description);
}

void FLogUtilityAI::VisLogLocation(const AActor* Actor, const FVector Location, const float Radius, const FString& Description, const FColor Color)
{
	UE_VLOG_LOCATION(Actor, LogUtilityAI, Log, Location, Radius, Color, TEXT("%s"), *Description);
}

void FLogUtilityAI::VisLogSegment(const AActor* Actor, const FVector Start, const FVector End, const float Thickness, const FString& Description, const FColor Color)
{
	UE_VLOG_SEGMENT_THICK(Actor, LogUtilityAI, Log, Start, End, Color, Thickness, TEXT("%s"), *Description);
}

void FLogUtilityAI::VisLogArrow(const AActor* Actor, const FVector Start, const FVector End, const FString& Description, const FColor Color)
{
	UE_VLOG_ARROW(Actor, LogUtilityAI, Log, Start, End, Color, TEXT("%s"), *Description);
}
