#include "EcuM.h"

#include "Swc_EcuM.h"
#include "Os.h"
//#include "Mcu.h"

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

void class_EcuM::InitFunction(void){
   EcuM_Context.ePhase = E_EcuM_Phase_STARTUP;
   Swc_EcuM.StartPreOs();
   Os.Start();
}

void class_EcuM::StartupTwo(void){
   Swc_EcuM.StartPostOs();
   EcuM_Context.ePhase = E_EcuM_Phase_UP;
}

void class_EcuM::MainFunction(void){
   switch(EcuM_Context.ePhase){
      case E_EcuM_Phase_UP:
         break;

      default:
         EcuM_Context.ePhase = E_EcuM_Phase_UNKNOWN;
         break;
   }
}

void class_EcuM::DeterminePbConfiguration(void){
}

bool class_EcuM::GetPendingWakeupEvents(void){
   return true;
}

void class_EcuM::GetValidatedWakeupEvents(void){
   //Mcu.GetResetReason();
}

void class_EcuM::LoopDetection(void){
}

void class_EcuM::SelectShutdownTarget(void){
}

void class_EcuM::GoDownHaltPoll(void){
   Swc_EcuM.OffPreOs();
   Os.Shutdown();
}

void class_EcuM::Shutdown(void){
   Swc_EcuM.OffPostOs();
}

