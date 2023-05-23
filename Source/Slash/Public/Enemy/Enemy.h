// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class UPawnSensingComponent;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	// <AActor>
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;
	// </AActor>

	// <IHitInterFace>
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	// </IHitInterFace>


protected:
	// <AActor>
	virtual void BeginPlay() override;
	// </AActor>

	// <ABaseCharacter>
	virtual void Attack() override;
	virtual void Die_Implementation() override;
	void SpawnSoul();
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void AttackEnd() override;
	// </ABaseCharacter>

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		EEnemyState EnemyState = EEnemyState::EES_Patrolling;

private:
	// AI Behavior
	void InitializeEnemy();
	void CheckPatrolTarget();
	void CheckCombatTarget();
	void PatrolTimerFinished();
	void HideHealthBar();
	void ShowHealthBar();
	void LooseInterest();
	void StartPatrolling();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool IsInsideAttackRadius();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	void ChaseTarget();
	void ClearPatrolTimer();
	void StartAttackTimer();
	void ClearAttackTimer();
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	void SpawnDefaultWeapon();

	UFUNCTION()
		void PawnSeen(APawn* SeenPawn);

	UPROPERTY()
		class AAIController* EnemyController;

	UPROPERTY(VisibleAnywhere)
		UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
		UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AWeapon> WeaponClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
		double CombatRadius = 1000.f;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
		AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
		TArray<AActor*> PatrolTargets;

	UPROPERTY()
		FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		float PatrolWaitMin{ 5.f };

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		float PatrolWaitMax{ 10.f };

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
		double PatrolRadius = 200.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float PatrollingSpeed = 125.f;

	UPROPERTY()
		FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		double AttackRadius = 250.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
		float DeathLifeSpan{ 5.f };

	UPROPERTY(EditAnywhere, Category = "Combat")
		float AcceptanceRadius{ 50.f };

	UPROPERTY(EditAnywhere, Category = "Combat")
		TSubclassOf<class ASoul> SoulClass;

};
