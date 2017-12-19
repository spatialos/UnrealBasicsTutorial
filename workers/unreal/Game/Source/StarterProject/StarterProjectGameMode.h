// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
#pragma once

#include "EntityId.h"
#include "EntityTemplate.h"
#include "SpatialOS.h"
#include "StarterProjectGameMode.generated.h"

UCLASS(minimalapi)
class AStarterProjectGameMode : public AGameModeBase
{
    GENERATED_BODY()

  public:
    AStarterProjectGameMode();

    UFUNCTION(BlueprintCallable, Category = "StarterProjectGameMode")
    FString GetSpatialOsWorkerType() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "StarterProjectGameMode")
    void OnSpatialOsConnected();

    UFUNCTION(BlueprintImplementableEvent, Category = "StarterProjectGameMode")
    void OnSpatialOsDisconnected();

    UFUNCTION(BlueprintImplementableEvent, Category = "StarterProjectGameMode")
    void OnSpatialOsFailedToConnect();

    UFUNCTION(BlueprintPure, Category = "StarterProjectGameMode")
    static UEntityTemplate* CreatePlayerEntityTemplate(FString clientWorkerId, const FVector& position);

    // clang-format off
    DECLARE_DYNAMIC_DELEGATE_ThreeParams(FGetSpawnerEntityIdResultDelegate, bool, success, FString, errorMessage, FEntityId, spawnerEntityId);
    // clang-format on    
    UFUNCTION(BlueprintCallable, Category = "StarterProjectGameMode")
    void GetSpawnerEntityId(const FGetSpawnerEntityIdResultDelegate& callback, int timeoutMs);

	void StartPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "StarterProjectGameMode")
	bool IsConnectedToSpatialOs() const;

	UFUNCTION(BlueprintPure, Category = "StarterProjectGameMode")
	UCommander* SendWorkerCommand();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, NoClear)
	FString WorkerTypeOverride;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, NoClear)
	FString WorkerIdOverride;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, NoClear)
	bool UseExternalIp;

  private:
    DECLARE_DELEGATE(FUnbindDelegate);

	USpatialOS* GetSpatialOS() const;

	UPROPERTY()
	UCommander* Commander;

    FGetSpawnerEntityIdResultDelegate* GetSpawnerEntityIdResultCallback;

    FUnbindDelegate UnbindEntityQueryDelegate;
    void UnbindEntityQueryCallback();
    std::uint64_t entityQueryCallback;
};