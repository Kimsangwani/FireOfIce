// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(Rhythm, Log, All);
#define LOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define LOG_S(Verbosity) UE_LOG(Rhythm, Verbosity, TEXT("%s"), *LOG_CALLINFO)
#define LOG(Verbosity, Format, ...) UE_LOG(Rhythm, Verbosity, TEXT("%s %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define CHECK(Expr, ...) {if(!(Expr)) {LOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}

