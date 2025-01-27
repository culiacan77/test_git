// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLE_PROJECT_1_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

	UFUNCTION(BlueprintCallable)
	void Release();

private:

	UFUNCTION(BlueprintCallable)
	bool GetGrabbableInReach(FHitResult& OutHitResult) const;

	UPhysicsHandleComponent* GetPhysicsHandle() const;

	UPROPERTY(EditAnywhere)
	float HoldDistance = 280; 

	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400;	

	//void DamageDone(float& Damge);

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100;
};
