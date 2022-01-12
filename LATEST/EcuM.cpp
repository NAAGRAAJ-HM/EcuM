#include "EcuM.h"

#include "Swc_EcuM.h"
#include "Os.h"
#include "Mcu.h"

typedef enum{
      E_EcuM_Phase_UNKNOWN
   ,  E_EcuM_Phase_STARTUP
   ,  E_EcuM_Phase_UP
   ,  E_EcuM_Phase_SLEEP
   ,  E_EcuM_Phase_SHUTDOWN
}enum_EcuM_Phase;

class class_EcuM_Context{
   public:
      enum_EcuM_Phase ePhase;
};

static class_EcuM_Context EcuM_Context;

class_EcuM EcuM;

FUNC(void, ECUM_CODE) class_EcuM::InitFunction(void){
   EcuM_Context.ePhase = E_EcuM_Phase_STARTUP;
   Swc_EcuM.StartPreOs();
   Os.Start();
}

FUNC(void, ECUM_CODE) class_EcuM::StartupTwo(void){
   Swc_EcuM.StartPostOs();
   EcuM_Context.ePhase = E_EcuM_Phase_UP;
}

FUNC(void, ECUM_CODE) class_EcuM::DeterminePbConfiguration(void){
}

bool class_EcuM::GetPendingWakeupEvents(void){
   return true;
}

FUNC(void, ECUM_CODE) class_EcuM::GetValidatedWakeupEvents(void){
   Mcu.GetResetReason();
}

FUNC(void, ECUM_CODE) class_EcuM::LoopDetection(void){
}

FUNC(void, ECUM_CODE) class_EcuM::SelectShutdownTarget(void){
}

FUNC(void, ECUM_CODE) class_EcuM::GoDownHaltPoll(void){//TBD: static?
   Swc_EcuM.OffPreOs();
   Os.Shutdown();
}

FUNC(void, ECUM_CODE) class_EcuM::Shutdown(void){//TBD: static?
   Swc_EcuM.OffPostOs();
}

FUNC(void, ECUM_CODE) class_EcuM::MainFunction(void){
   switch(EcuM_Context.ePhase){
      case E_EcuM_Phase_UP:
         break;

      case E_EcuM_Phase_SLEEP:
         //...
         EcuM_Context.ePhase = E_EcuM_Phase_UP;
         break;

      case E_EcuM_Phase_SHUTDOWN:
         GoDownHaltPoll();
         Shutdown();
         break;

      default:
         EcuM_Context.ePhase = E_EcuM_Phase_UNKNOWN;
         break;
   }
}

