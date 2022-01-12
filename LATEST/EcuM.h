#pragma once

#include "Std_Types.h"
#include "Compiler_Cfg_EcuM.h"

class class_EcuM{
   public:
      FUNC(void, ECUM_CODE) InitFunction             (void);
      FUNC(void, ECUM_CODE) MainFunction             (void);
      FUNC(void, ECUM_CODE) StartupTwo               (void);
      FUNC(void, ECUM_CODE) DeterminePbConfiguration (void);
      bool GetPendingWakeupEvents   (void);
      FUNC(void, ECUM_CODE) GetValidatedWakeupEvents (void);
      FUNC(void, ECUM_CODE) LoopDetection            (void);
      FUNC(void, ECUM_CODE) SelectShutdownTarget     (void);
      FUNC(void, ECUM_CODE) GoDownHaltPoll           (void);
      FUNC(void, ECUM_CODE) Shutdown                 (void);
};

extern class_EcuM EcuM;

