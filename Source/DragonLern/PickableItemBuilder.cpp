
// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItemBuilder.h"
#include <unordered_map>
#include "DragonLernCharacter.h"
#include "DralonLernActorComponent.h"
#include "SpeedBuffComponent.h"
#include "DecreaseSpeedBuffComponent.h"
#include "JumpBuffComponent.h"


template<typename BuffComponent>
struct BuffEfect : public PickableEfectBase
{
	void ApplyEfect(OverlapParams const& prams) override
	{
		BuffComponent* component = prams.OtherActor->FindComponentByClass<BuffComponent>();

		if (!component)
		{
			component = NewObject<BuffComponent>(prams.OtherActor, BuffComponent::StaticClass());
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
		{ItemEfectType::IncreaseSpeed, newItem<BuffEfect<USpeedBuffComponent>>},
		{ItemEfectType::DecreaseSpeed, newItem<BuffEfect<UDecreaseSpeedBuffComponent>>},
		{ItemEfectType::Jump, newItem<BuffEfect<UJumpBuffComponent>>}
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
		{ItemEfectType::IncreaseSpeed, FColor::Blue},
		{ItemEfectType::DecreaseSpeed, FColor::Yellow},
		{ItemEfectType::Jump, FColor::Purple}
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
	return ItemEfectType::Jump;// static_cast<ItemEfectType>(FMath::RandRange(0, (int32)ItemEfectType::COUNT - 1));
}


UPickableItemBuilder const& UPickableItemBuilder::GetInstance()
{
	static class UPickableItemBuilder* builder = NewObject<UPickableItemBuilder>();// = CreateDefaultSubobject<UPickableItemBuilder>(TEXT(""));
	return *builder;
}
