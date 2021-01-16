//
// Created by ldesp on 10/01/2021.
//

#if HW == LBAN
#include "hw/LBAND.h"
#elif HW == x86
#include "hw/x86.h"
#else
#include "hw/common.h"
#endif