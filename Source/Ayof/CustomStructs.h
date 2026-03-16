#pragma once

UENUM(BlueprintType)
enum class ETaskStatus : uint8
{
	Inactive = 0,
	Idle,
	Success,
	Failed,
	Cancelled
};

UENUM(BlueprintType)
enum class ETaskType : uint8
{
	Repair = 0,
	Refuel,
	MotorWinding
};