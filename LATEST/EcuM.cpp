/*****************************************************/
/* File   : EcuM.cpp                                 */
/* Author : Naagraaj HM                              */
/*****************************************************/

/*****************************************************/
/* #INCLUDES                                         */
/*****************************************************/
#include "module.h"
#include "EcuM_StartUp.h"
#include "EcuM_SchM.h"
#include "EcuM_Os.h"
#include "EcuM_SwcServiceEcuM.h"
#include "EcuM_Unused.h"

#include "SwcServiceEcuM_EcuM.h"
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

class class_EcuM_Context{
   public:
      enum_EcuM_Phase ePhase;
};

class module_EcuM:
      public abstract_module
   ,  public interface_EcuM_StartUp
   ,  public interface_EcuM_SchM
   ,  public interface_EcuM_Os
   ,  public interface_EcuM_SwcServiceEcuM
{
   public:
      FUNC(void, ECUM_CODE) InitFunction             (void);
      FUNC(void, ECUM_CODE) DeInitFunction           (void);
      FUNC(void, ECUM_CODE) MainFunction             (void);
      FUNC(void, ECUM_CODE) StartupTwo               (void);
      FUNC(void, ECUM_CODE) DeterminePbConfiguration (void);
      bool GetPendingWakeupEvents   (void);
      FUNC(void, ECUM_CODE) GetValidatedWakeupEvents (void);
      FUNC(void, ECUM_CODE) LoopDetection            (void);
      FUNC(void, ECUM_CODE) SelectShutdownTarget     (void);
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
static class_EcuM_Context EcuM_Context;

module_EcuM EcuM;

interface_EcuM_StartUp *StartUp_Client_ptr_EcuM = &EcuM;
interface_EcuM_SchM *SchM_Client_ptr_EcuM = &EcuM;

/*****************************************************/
/* FUNCTIONS                                         */
/*****************************************************/
//TBD: static?
//FUNC(void, ECUM_CODE) class_EcuM_Unused::GoDownHaltPoll(void){
static void GoDownHaltPoll(void){
   EcuM_Client_ptr_SwcServiceEcuM->OffPreOs();
   EcuM_Client_ptr_Os->Shutdown();
}

//TBD: static?
//FUNC(void, ECUM_CODE) class_EcuM_Unused::Shutdown(void){
static void Shutdown(void){
   EcuM_Client_ptr_SwcServiceEcuM->OffPostOs();
}

FUNC(void, ECUM_CODE) module_EcuM::InitFunction(void){
   EcuM_Context.ePhase = E_EcuM_Phase_STARTUP;
   EcuM_Client_ptr_SwcServiceEcuM->StartPreOs();
   EcuM_Client_ptr_Os->Start();
}

FUNC(void, ECUM_CODE) module_EcuM::DeInitFunction(void){
}

FUNC(void, ECUM_CODE) module_EcuM::MainFunction(void){
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

FUNC(void, ECUM_CODE) module_EcuM::StartupTwo(void){
   EcuM_Client_ptr_SwcServiceEcuM->StartPostOs();
   EcuM_Context.ePhase = E_EcuM_Phase_UP;
}

FUNC(void, ECUM_CODE) module_EcuM::DeterminePbConfiguration(void){
}

FUNC(bool, ECUM_CODE) module_EcuM::GetPendingWakeupEvents(void){
   return true;
}

FUNC(void, ECUM_CODE) module_EcuM::GetValidatedWakeupEvents(void){
   EcuM_Client_ptr_Mcu->GetResetReason();
}

FUNC(void, ECUM_CODE) module_EcuM::LoopDetection(void){
}

FUNC(void, ECUM_CODE) module_EcuM::SelectShutdownTarget(void){
}

/*****************************************************/
/* EOF                                               */
/*****************************************************/

