#pragma once

#include "Std_Types.h"

class class_EcuM{
   public:
      void InitFunction             (void);
      void MainFunction             (void);
      void StartupTwo               (void);
      void DeterminePbConfiguration (void);
      bool GetPendingWakeupEvents   (void);
      void GetValidatedWakeupEvents (void);
      void LoopDetection            (void);
      void SelectShutdownTarget     (void);
      void GoDownHaltPoll           (void);
      void Shutdown                 (void);
};

extern class_EcuM EcuM;

