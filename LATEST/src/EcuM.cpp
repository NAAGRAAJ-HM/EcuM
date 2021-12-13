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

void class_EcuM::GetValidatedWakeupEvents(void){
   //Mcu.GetResetReason();
}

void class_EcuM::LoopDetection(void){
}

