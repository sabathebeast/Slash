// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraComponent;
class UNiagaraSystem;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped
};

UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SpawnPickupSystem();
	virtual void SpawnPickupSound();

	UFUNCTION(BlueprintPure)
		float TransformedSin();
	UFUNCTION(BlueprintPure)
		float TransformedCos();

	template<typename T>
	T Avg(T First, T Second);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* Sphere;

	EItemState ItemState = EItemState::EIS_Hovering;

	UPROPERTY(EditAnywhere)
		UNiagaraComponent* ItemEffect;

	UPROPERTY(EditAnywhere)
		USoundBase* PickupSound;

private:
	float RunningTime{ 0.f };
	UPROPERTY(EditAnywhere, Category = "Movement")
		float Amplitude{ 0.25f };
	UPROPERTY(EditAnywhere, Category = "Movement")
		float TimeConstant{ 5.f };
	UPROPERTY(EditAnywhere, Category = "Movement")
		float RotationSpeed = 10.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
		bool ShouldTransform;

	UPROPERTY(EditAnywhere)
		UNiagaraSystem* PickupEffect;

};

template<typename T>
inline T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;
}
