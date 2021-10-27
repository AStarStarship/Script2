/* Script2 (TM) @version 0.x
@link    https://github.com/KabukiStarship/Script2.git
@file    /_Seams/01.RNG.inl
@author  Cale McCollough <https://cookingwithcale.org>
@license Copyright (C) 2015-20 Cale McCollough
<<cookingwithcale.org>>; all right reserved (R). This Source Code
Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of
the MPL was not distributed with this file, You can obtain one at
<https://mozilla.org/MPL/2.0/>. */

#if SEAM >= SCRIPT2_RNG
#include "../RNG.h"
using namespace _;
#if SEAM == SCRIPT2_RNG
#include "../_Debug.inl"
#else
#include "../_Release.inl"
#endif
#endif

namespace Script2 {
static const CHA* RNG(const CHA* args) {
#if SEAM >= SCRIPT2_RNG
  A_TEST_BEGIN;

#if SEAM == SCRIPT2_RNG
  enum { cPrintCount = 256 };
#else
  enum { cPrintCount = 1 };
#endif

  for (ISN i = 0; i < cPrintCount; ++i)
    D_COUT('\n' << i << ".) " << Random(TSignedMin<ISN>(), TSignedMax<ISN>()));

#endif
  return nullptr;
}
}  //< namespace Script2
