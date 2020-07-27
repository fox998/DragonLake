
// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItemBuilder.h"
#include <unordered_map>
#include "DragonLernCharacter.h"
#include "DralonLernActorComponent.h"
#include "SpeedBuffComponent.h"


struct SpeedEfect : public PickableEfectBase
{
	void ApplyEfect(OverlapParams const& prams) override
	{
		USpeedBuffComponent* component = prams.OtherActor->FindComponentByClass<USpeedBuffComponent>();

		if (component)
		{
			GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString::Printf(TEXT("HealEfect FindComponentByClass<UDralonLernActorComponent>")));
		}
		else
		{
			component = NewObject<USpeedBuffComponent>(prams.OtherActor, USpeedBuffComponent::StaticClass());
			component->RegisterComponent();
			prams.OtherActor->AddOwnedComponent(component);
		}

		component->IncriaseBuffTime(3);
	}
};


struct HealEfect : public PickableEfectBase
{
	void ApplyEfect(OverlapParams const& prams) override
	{
		 auto* character = Cast<ADragonLernCharacter>(prams.OtherActor);
		 character->HPDeltaChange(UPickableItemBuilder::GetInstance().HealEfect);
		 
		 auto* component = character->FindComponentByClass<UDralonLernActorComponent>();

		 if (component)
		 {
			 GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Blue, FString::Printf(TEXT("HealEfect FindComponentByClass<UDralonLernActorComponent>")));
		 }
	}
};


struct DamageEfect : public PickableEfectBase
{
	void ApplyEfect(OverlapParams const& prams) override
	{
		auto* character = Cast<ADragonLernCharacter>(prams.OtherActor);
		character->HPDeltaChange(-UPickableItemBuilder::GetInstance().DamageEfect);
	}
};

template<typename T>
PickableEfectBase* newItem()
{
	static T itemEfect;
	return &itemEfect;
}

PickableEfectBase* getEfectFromEnum(ItemEfectType efectType)
{
	static const std::unordered_map<ItemEfectType, std::function<PickableEfectBase* (void)>> mapper = {
		{ItemEfectType::Heal, newItem<HealEfect>},
		{ItemEfectType::Damage, newItem<DamageEfect>},
		{ItemEfectType::Speed, newItem<SpeedEfect>}
	};

	auto efectIter = mapper.find(efectType);
	bool const isValid = (efectIter != mapper.cend());
	return isValid ? efectIter->second() : newItem<PickableEfectBase>();
}

FColor getColorFromEfectType(ItemEfectType efect)
{
	static const std::unordered_map<ItemEfectType, FColor> colorMapper = {
		{ItemEfectType::Heal, FColor::Green},
		{ItemEfectType::Damage, FColor::Red},
		{ItemEfectType::Speed, FColor::Blue}
	};

	auto colorIter = colorMapper.find(efect);
	bool const isValid = colorIter != colorMapper.cend();
	return isValid ? colorIter->second : FColor::Black;
}

void UPickableItemBuilder::AsamblePickableItem(APickableItem* asablingBase, ItemEfectType efectType)
{
	asablingBase->SetEfect(getEfectFromEnum(efectType));
	asablingBase->SetColor(getColorFromEfectType(efectType));
}

ItemEfectType UPickableItemBuilder::GetRandomEfect()
{
	return ItemEfectType::Speed;// static_cast<ItemEfectType>(FMath::RandRange(0, (int32)ItemEfectType::COUNT - 1));
}


UPickableItemBuilder const& UPickableItemBuilder::GetInstance()
{
	static class UPickableItemBuilder* builder = NewObject<UPickableItemBuilder>();// = CreateDefaultSubobject<UPickableItemBuilder>(TEXT(""));
	return *builder;
}
