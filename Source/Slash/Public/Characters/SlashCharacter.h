// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
#include "Interfaces/PickupInterface.h"
#include "SlashCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UGroomComponent;
class AItem;
class UAnimMontage;
class USlashOverlay;
class ASoul;
class ATreasure;


UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime);
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGold(ATreasure* Treasure) override;

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }

protected:
	virtual void BeginPlay() override;

	// Calls for Input Actions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Dodge();

	bool IsOccupied();

	bool HasEnoughStamina();

	// Combat
	void EquipWeapon(AWeapon* Weapon);
	virtual void Attack() override;
	virtual void AttackEnd() override;
	virtual void DodgeEnd() override;
	virtual bool CanAttack() override;
	bool CanDisarm();
	bool CanArm();
	void DisArm();
	void Arm();

	virtual void Die_Implementation() override;

	void PlayEquipMontage(const FName& SectionName);
	void EKeyPressed();

	UFUNCTION(BlueprintCallable)
		void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
		void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
		void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();


private:
	void SetHUDHealth(float DamageAmount);
	void InitializeSlashCharacter();
	bool IsUnoccupied();

	UPROPERTY()
	USlashOverlay* SlashOverlay;

	UPROPERTY(VisibleInstanceOnly)
		AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
		UAnimMontage* EquipMontage;
	
	// Character components
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* ViewCamera;

	UPROPERTY(EditAnywhere)
		UGroomComponent* Hair;

	UPROPERTY(EditAnywhere)
		UGroomComponent* Eyebrows;

	 // Input Actions
	UPROPERTY(EditAnywhere, Category = "Input Actions")
		UInputMappingContext* SlashContext;

	UPROPERTY(EditAnywhere, Category = "Input Actions")
		UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input Actions")
		UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input Actions")
		UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input Actions")
		UInputAction* EquipAction;
	UPROPERTY(EditAnywhere, Category = "Input Actions")
		UInputAction* AttackAction;
	UPROPERTY(EditAnywhere, Category = "Input Actions")
		UInputAction* DodgeAction;

	// Enum States
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		EActionState ActionState = EActionState::EAS_Unoccupied;
};