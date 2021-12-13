#pragma once

class class_EcuM{
   public:
      void InitFunction             (void);
      void StartupTwo               (void);
      void DeterminePbConfiguration (void);
      void GetValidatedWakeupEvents (void);
      void LoopDetection            (void);
};

extern class_EcuM EcuM;

