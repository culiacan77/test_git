// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();



	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if (PhysicsHandle == nullptr) {
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr) {
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}



//	FRotator MyRotation = GetComponentRotation();
//	FString RotationString = MyRotation.ToCompactString();
//	UE_LOG(LogTemp, Display, TEXT("Component rotation: %s"), *RotationString);
//
//	UWorld* World = GetWorld();
//	float CurrentTime = World->GetTimeSeconds();
//	UE_LOG(LogTemp, Display, TEXT("Time elapsed in sec: %f"), CurrentTime);
	

	

	

	//float MyDamage = 5;
	//DamageDone(MyDamage);
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const {



	FVector Start = GetComponentLocation() + GetForwardVector();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;
	DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 5.0f, 0, 5.0f);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);

	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 2);

	return GetWorld()->SweepSingleByChannel(OutHitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, Sphere);

	

}

void UGrabber::Grab() {
	
	UE_LOG(LogTemp, Display, TEXT("Grab"));
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();

	if(PhysicsHandle == nullptr) {
		return;
	}
	
	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	if (HasHit) {
		
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		//this is debug to see the geometry sweep hit result and get name of object (if it has grabber colision enable)
		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Red, false, 2);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Green, false, 2);
		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("Hit object name: %s"), *HitActor->GetActorNameOrLabel());

		//there is a lot of argument in this function so we write it in column
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}	
}

	UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const{
		UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
		if(Result == nullptr) {
			UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
		}
		return Result;
	}
	
	void UGrabber::Release() {

			UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
			if(PhysicsHandle == nullptr) {
				return;
		}

		if(PhysicsHandle->GetGrabbedComponent() != nullptr) {
			PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
			PhysicsHandle->ReleaseComponent();
		}
	}




//  !! wont work for now cause the grab function is not present in the bp third person blueprint yet, just drag it from the grab node :)  !!

//void UGrabber::DamageDone(float& Damage) {
	//Damage ++;
	//UE_LOG(LogTemp, Display, TEXT("Damage done: %f"), Damage);
//}

//can pointer change the variable value ? *ActorPTR = Actor
//what if we don't declare a variable in header ? cause pointer are not declared there and arguments of function neither.
//when using a pointer:			   MySpeed = *Speed means the value of Speed (not the adress)
//					  		float* MySpeed =  Speed means the adress
//When using a reference:	       MySpeed = &Speed means Adress of Speed
//							float &MySpeed =  Speed means 
//							float& MySpeed = reference to whatever we put on right of = sign

//			what about		float* MySpeed = &Speed

//all possible stuf on left of the "=" sign 
//											float MySpeed
//											float* MySpeed
//											float* &MySpeed
//											float &MySpeed

//all possible stuf on right of the "=" sign 		(once assign to a pointer or reference)
	//											 Speed		--> 	Accessing the Adress if it is a pointer // the value if it is a reference
	//											 *Speed		--> 	Accessing the value. It is a pointer 	//		------
	//											 &Speed		--> 	Accessing 			------				   the adress, it is a Reference