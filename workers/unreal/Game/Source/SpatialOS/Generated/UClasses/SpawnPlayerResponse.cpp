// ===========
// DO NOT EDIT - this file is automatically regenerated.
// =========== 

#include "SpawnPlayerResponse.h"

USpawnPlayerResponse::USpawnPlayerResponse()
{
	Underlying.Reset(new improbable::spawner::SpawnPlayerResponse(false, "", worker::EntityId(0)));
}

USpawnPlayerResponse* USpawnPlayerResponse::Init(const improbable::spawner::SpawnPlayerResponse& underlying)
{
    Underlying.Reset(new improbable::spawner::SpawnPlayerResponse(underlying));
	return this;
}

bool USpawnPlayerResponse::GetSuccess()
{
    return Underlying->success();
}
USpawnPlayerResponse* USpawnPlayerResponse::SetSuccess(bool success)
{
    Underlying->set_success(success);
	return this;
}

FString USpawnPlayerResponse::GetErrorMessage()
{
    return FString(Underlying->error_message().c_str());
}
USpawnPlayerResponse* USpawnPlayerResponse::SetErrorMessage(FString error_message)
{
    Underlying->set_error_message(TCHAR_TO_UTF8(*error_message));
	return this;
}

FEntityId USpawnPlayerResponse::GetCreatedEntityId()
{
    return FEntityId(Underlying->created_entity_id());
}
USpawnPlayerResponse* USpawnPlayerResponse::SetCreatedEntityId(FEntityId created_entity_id)
{
    Underlying->set_created_entity_id((created_entity_id).ToSpatialEntityId());
	return this;
}


improbable::spawner::SpawnPlayerResponse USpawnPlayerResponse::GetUnderlying()
{
	return *Underlying.Get();
}
