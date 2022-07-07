/******************************************************************************/
/* File   : EcuM.cpp                                                          */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "EcuM.hpp"
#include "infEcuM_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define ECUM_AR_RELEASE_VERSION_MAJOR                                          4
#define ECUM_AR_RELEASE_VERSION_MINOR                                          3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(ECUM_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible ECUM_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(ECUM_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible ECUM_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
CONSTP2VAR(infEcuM_StartUp,        ECUM_VAR, ECUM_CONST) gptrinfEcuM_StartUp        = &EcuM;
CONSTP2VAR(infEcuM_Os,             ECUM_VAR, ECUM_CONST) gptrinfEcuM_Os             = &EcuM;
CONSTP2VAR(infEcuM_SwcServiceEcuM, ECUM_VAR, ECUM_CONST) gptrinfEcuM_SwcServiceEcuM = &EcuM;

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_EcuM, ECUM_VAR) EcuM;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#include "infMcu_EcuM.hpp"
#include "infOs_EcuM.hpp"
#include "infStartUp_EcuM.hpp"
#include "infSwcServiceEcuM_EcuM.hpp"

//TBD: static?
FUNC(void, ECUM_CODE) module_EcuM::GoDownHaltPoll(
   void
){
   gptrinfSwcServiceEcuM_EcuM->OffPreOs();
   gptrinfOs_EcuM->Shutdown();
}

//TBD: static?
FUNC(void, ECUM_CODE) module_EcuM::Shutdown(
   void
){
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

FUNC(void, ECUM_CODE) module_EcuM::InitFunction(
   CONSTP2CONST(CfgModule_TypeAbstract, ECUM_CONFIG_DATA, ECUM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == Dem_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(NULL_PTR != lptrCfgModule){
         lptrCfg = lptrCfgModule;
      }
      else{
#if(STD_ON == Dem_DevErrorDetect)
         Det_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
      EcuM_Context.ePhase = E_EcuM_Phase_STARTUP;
#if(STD_ON == Dem_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  ECUM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, ECUM_CODE) module_EcuM::DeInitFunction(
   void
){
#if(STD_ON == Dem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
      EcuM_Context.ePhase = E_EcuM_Phase_UNKNOWN;
#if(STD_ON == Dem_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  ECUM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, ECUM_CODE) module_EcuM::MainFunction(
   void
){
#if(STD_ON == Dem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
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
#if(STD_ON == Dem_InitCheck)
   }
   else{
#if(STD_ON == Dem_DevErrorDetect)
      Det_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  ECUM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, ECUM_CODE) module_EcuM::InitFunction(
   void
){
   gptrinfSwcServiceEcuM_EcuM->StartPreOs();
   gptrinfOs_EcuM->Start();
}

FUNC(void, ECUM_CODE) module_EcuM::StartupTwo(
   void
){
   gptrinfSwcServiceEcuM_EcuM->StartPostOs();
   EcuM_Context.ePhase = E_EcuM_Phase_UP;
}

FUNC(void, ECUM_CODE) module_EcuM::DeterminePbConfiguration(
   void
){
}

FUNC(bool, ECUM_CODE) module_EcuM::GetPendingWakeupEvents(
   void
){
   return true;
}

FUNC(void, ECUM_CODE) module_EcuM::GetValidatedWakeupEvents(
   void
){
   gptrinfMcu_EcuM->GetResetReason();
}

FUNC(void, ECUM_CODE) module_EcuM::LoopDetection(
   void
){
}

FUNC(void, ECUM_CODE) module_EcuM::SelectShutdownTarget(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

