/******************************************************************************/
/* File   : EcuM.cpp                                                          */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "module.h"
#include "CfgEcuM.h"
#include "infEcuM_StartUp.h"
#include "infEcuM_Dcm.h"
#include "infEcuM_SchM.h"
#include "infEcuM_Os.h"
#include "infEcuM_SwcServiceEcuM.h"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ECUM_AR_RELEASE_MAJOR_VERSION                                          4
#define ECUM_AR_RELEASE_MINOR_VERSION                                          3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(ECUM_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION)
   #error "Incompatible ECUM_AR_RELEASE_MAJOR_VERSION!"
#endif

#if(ECUM_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION)
   #error "Incompatible ECUM_AR_RELEASE_MINOR_VERSION!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_EcuM:
      public abstract_module
   ,  public infEcuM_Os
   ,  public infEcuM_SwcServiceEcuM
{
   public:
      FUNC(void, ECUM_CODE) InitFunction             (void);
      FUNC(void, ECUM_CODE) DeInitFunction           (void);
      FUNC(void, ECUM_CODE) GetVersionInfo           (void);
      FUNC(void, ECUM_CODE) MainFunction             (void);
      FUNC(void, ECUM_CODE) StartupTwo               (void);
      FUNC(void, ECUM_CODE) DeterminePbConfiguration (void);
      FUNC(bool, ECUM_CODE) GetPendingWakeupEvents   (void);
      FUNC(void, ECUM_CODE) GetValidatedWakeupEvents (void);
      FUNC(void, ECUM_CODE) LoopDetection            (void);
      FUNC(void, ECUM_CODE) SelectShutdownTarget     (void);

   private:
      CONST(Std_TypeVersionInfo, ECUM_CONST) VersionInfo = {
            0x0000
         ,  0xFFFF
         ,  0x01
         ,  '0'
         ,  '1'
         ,  '0'
      };
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_EcuM, ECUM_VAR) EcuM;
CONSTP2VAR(infEcuMClient, ECUM_VAR, ECUM_CONST) gptrinfEcuMClient_EcuM = &EcuM;
CONSTP2VAR(infDcmClient,  ECUM_VAR, ECUM_CONST) gptrinfDcmClient_EcuM  = &EcuM;
CONSTP2VAR(infSchMClient, ECUM_VAR, ECUM_CONST) gptrinfSchMClient_EcuM = &EcuM;
CONSTP2VAR(infEcuM_Os,             ECUM_VAR, ECUM_CONST) gptrinfEcuM_Os             = &EcuM;
CONSTP2VAR(infEcuM_SwcServiceEcuM, ECUM_VAR, ECUM_CONST) gptrinfEcuM_SwcServiceEcuM = &EcuM;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#include "infMcu_EcuM.h"
#include "infOs_EcuM.h"
#include "infStartUp_EcuM.h"
#include "infSwcServiceEcuM_EcuM.h"

//TBD: static?
//FUNC(void, ECUM_CODE) class_EcuM_Unused::GoDownHaltPoll(void){
static void GoDownHaltPoll(void){
   gptrinfSwcServiceEcuM_EcuM->OffPreOs();
   gptrinfOs_EcuM->Shutdown();
}

//TBD: static?
//FUNC(void, ECUM_CODE) class_EcuM_Unused::Shutdown(void){
static void Shutdown(void){
   gptrinfSwcServiceEcuM_EcuM->OffPostOs();
}

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

FUNC(void, ECUM_CODE) module_EcuM::InitFunction(void){
   gptrinfSwcServiceEcuM_EcuM->StartPreOs();
   gptrinfOs_EcuM->Start();

   EcuM_Context.ePhase = E_EcuM_Phase_STARTUP;
   EcuM.IsInitDone     = E_OK;
}

FUNC(void, ECUM_CODE) module_EcuM::DeInitFunction(void){
   EcuM_Context.ePhase = E_EcuM_Phase_UNKNOWN;
   EcuM.IsInitDone     = E_NOT_OK;
}

FUNC(void, ECUM_CODE) module_EcuM::GetVersionInfo(void){
#if(STD_ON == EcuM_DevErrorDetect)
//TBD: API parameter check
   Det_ReportError(
   );
#endif
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
   gptrinfSwcServiceEcuM_EcuM->StartPostOs();
   EcuM_Context.ePhase = E_EcuM_Phase_UP;
}

FUNC(void, ECUM_CODE) module_EcuM::DeterminePbConfiguration(void){
}

FUNC(bool, ECUM_CODE) module_EcuM::GetPendingWakeupEvents(void){
   return true;
}

FUNC(void, ECUM_CODE) module_EcuM::GetValidatedWakeupEvents(void){
   gptrinfMcu_EcuM->GetResetReason();
}

FUNC(void, ECUM_CODE) module_EcuM::LoopDetection(void){
}

FUNC(void, ECUM_CODE) module_EcuM::SelectShutdownTarget(void){
}

#include "EcuM_Unused.h"

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

