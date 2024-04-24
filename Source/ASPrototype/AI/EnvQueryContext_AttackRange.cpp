// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EnvQueryContext_AttackRange.h"
#include "ASAIController.h"
#include "EnvironmentQuery/EnvQueryTypes.h" //FEnvQueryInstance Æ÷ÇÔ
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h" 

void UEnvQueryContext_AttackRange::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const 
{	
	Super::ProvideContext(QueryInstance, ContextData);
	AASAIController * AIRef = Cast<AASAIController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (AIRef)
	{
		//Set the context SeeingPawn to the provided context data
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AIRef->GetPlayer());
	}

}

