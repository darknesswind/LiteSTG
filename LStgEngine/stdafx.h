// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// std
#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <deque>
#include <cmath>
#include <array>

#include "gsl/gsl"
// DxLibEngine
#include "typedef.h"
#include "base/LHandle.h"
#include "tools/LLogger.h"
#include "tools/LString.h"
#include "render/LPainter.h"

// LStgEngine
#include "LStgEngine.h"