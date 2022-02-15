/*****************************************************/
/* File   : EcuM.cpp                                 */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "module.h"

#include "EcuM_Unused.h"

#include "Swc_EcuM.h"
#include "Os_EcuM.h"
#include "Mcu_EcuM.h"

/*****************************************************/
/* #DEFINES                                          */
/*****************************************************/

/*****************************************************/
/* MACROS                                            */
/*****************************************************/

/*****************************************************/
/* TYPEDEFS                                          */
/*****************************************************/
typedef enum{
      E_EcuM_Phase_UNKNOWN
   ,  E_EcuM_Phase_STARTUP
   ,  E_EcuM_Phase_UP
   ,  E_EcuM_Phase_SLEEP
   ,  E_EcuM_Phase_SHUTDOWN
}enum_EcuM_Phase;

class class_EcuM_Unused_Context{
   public:
      enum_EcuM_Phase ePhase;
};

class module_EcuM : public class_module{
   public:
      FUNC(void, ECUM_CODE) InitFunction   (void);
      FUNC(void, ECUM_CODE) DeInitFunction (void);
      FUNC(void, ECUM_CODE) MainFunction   (void);
};

/*****************************************************/
/* CONSTS                                            */
/*****************************************************/

/*****************************************************/
/* PARAMS                                            */
/*****************************************************/

/*****************************************************/
/* OBJECTS                                           */
/*****************************************************/
static class_EcuM_Unused_Context EcuM_Context;

module_EcuM EcuM;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
FUNC(void, ECUM_CODE) module_EcuM::InitFunction(void){
   EcuM_Context.ePhase = E_EcuM_Phase_STARTUP;
   EcuM_Client_ptr_Swc_EcuM->StartPreOs();
   EcuM_Client_ptr_Os->Start();
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::StartupTwo(void){
   EcuM_Client_ptr_Swc_EcuM->StartPostOs();
   EcuM_Context.ePhase = E_EcuM_Phase_UP;
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::DeterminePbConfiguration(void){
}

bool class_EcuM_Unused::GetPendingWakeupEvents(void){
   return true;
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::GetValidatedWakeupEvents(void){
   Mcu.GetResetReason();
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::LoopDetection(void){
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::SelectShutdownTarget(void){
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::GoDownHaltPoll(void){//TBD: static?
   Swc_EcuM.OffPreOs();
   Os.Shutdown();
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::Shutdown(void){//TBD: static?
   Swc_EcuM.OffPostOs();
}

FUNC(void, ECUM_CODE) class_EcuM_Unused::MainFunction(void){
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

/*****************************************************/
/* EOF                                               */
/*****************************************************/

