#include "EcuM.h"

#include "Swc_EcuM.h"
#include "Os.h"
//#include "Mcu.h"

class_EcuM EcuM;

void class_EcuM::InitFunction(void){
   Swc_EcuM.StartPreOs();
   Os.Start();
}

void class_EcuM::StartupTwo(void){
   Swc_EcuM.StartPostOs();
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

