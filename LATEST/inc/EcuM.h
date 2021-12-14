#pragma once

class class_EcuM{
   public:
      void InitFunction             (void);
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

