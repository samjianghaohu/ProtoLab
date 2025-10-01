#pragma once

#include "DrawDebugHelpers.h"

#define DEBUG_SPHERE_SIZE 25.5f
#define DRAW_SPHERE_THIS_FRAME(LOCATION) if (GetWorld()) DrawDebugSphere(GetWorld(), LOCATION, DEBUG_SPHERE_SIZE, 24, FColor::Cyan, false, 0.f);
#define DRAW_LINE(START, END) if (GetWorld()) DrawDebugLine(GetWorld(), START, END, FColor::Yellow, true);
#define DRAW_POINT(LOCATION) if (GetWorld()) DrawDebugPoint(GetWorld(), LOCATION, 10.0f, FColor::Blue, true);
#define DRAW_VECTOR_THIS_FRAME(START, END) if (GetWorld()) { DrawDebugLine(GetWorld(), START, END, FColor::Yellow, false, 0.f); DrawDebugPoint(GetWorld(), END, 10.0f, FColor::Blue, false, 0.f); }