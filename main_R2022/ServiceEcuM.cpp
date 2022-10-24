/******************************************************************************/
/* File   : ServiceEcuM.cpp                                                   */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "Module.hpp"
#include "ServiceEcuM.hpp"
#include "infServiceEcuM_Imp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define SERVICEECUM_AR_RELEASE_VERSION_MAJOR                                   4
#define SERVICEECUM_AR_RELEASE_VERSION_MINOR                                   3

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(SERVICEECUM_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible SERVICEECUM_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(SERVICEECUM_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible SERVICEECUM_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
VAR(module_ServiceEcuM, SERVICEECUM_VAR) ServiceEcuM;

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
#include "infMcalMcu_ServiceEcuM.hpp"
#include "infServiceOs_ServiceEcuM.hpp"
#include "infServiceSwcEcuM_ServiceEcuM.hpp"

//TBD: static?
FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::GoDownHaltPoll(
   void
){
   lptrConst->ptrinfServiceSwcEcuM_ServiceEcuM->OffPreServiceOs();
   lptrConst->ptrinfServiceOs_ServiceEcuM->Shutdown();
}

//TBD: static?
FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::Shutdown(
   void
){
   lptrConst->ptrinfServiceSwcEcuM_ServiceEcuM->OffPostServiceOs();
}

typedef enum{
      E_ServiceEcuM_Phase_UNKNOWN
   ,  E_ServiceEcuM_Phase_SERVICESTARTUP
   ,  E_ServiceEcuM_Phase_UP
   ,  E_ServiceEcuM_Phase_SLMCALEEP
   ,  E_ServiceEcuM_Phase_SHUTDOWN
}enum_ServiceEcuM_Phase;

class class_ServiceEcuM_Context{
   public:
      enum_ServiceEcuM_Phase ePhase;
};

static class_ServiceEcuM_Context ServiceEcuM_Context;

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::InitFunction(
      CONSTP2CONST(ConstModule_TypeAbstract, SERVICEECUM_CONST,       SERVICEECUM_APPL_CONST) lptrConstModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICEECUM_CONFIG_DATA, SERVICEECUM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrConstModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrConst = (const ConstServiceEcuM_Type*)lptrConstModule;
         lptrCfg   = lptrCfgModule;
      }
      else{
#if(STD_ON == ServiceDem_DevErrorDetect)
         ServiceDet_ReportError(
               0 //TBD: IdModule
            ,  0 //TBD: IdInstance
            ,  0 //TBD: IdApi
            ,  0 //TBD: IdError
         );
#endif
      }
      ServiceEcuM_Context.ePhase = E_ServiceEcuM_Phase_SERVICESTARTUP;
#if(STD_ON == ServiceDem_InitCheck)
      IsInitDone = E_OK;
   }
   else{
#if(STD_ON == ServiceDem_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEECUM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::DeInitFunction(
   void
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
      ServiceEcuM_Context.ePhase = E_ServiceEcuM_Phase_UNKNOWN;
#if(STD_ON == ServiceDem_InitCheck)
      IsInitDone = E_NOT_OK;
   }
   else{
#if(STD_ON == ServiceDem_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEECUM_E_UNINIT
      );
#endif
   }
#endif
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::MainFunction(
   void
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      == IsInitDone
   ){
#endif
      switch(ServiceEcuM_Context.ePhase){
         case E_ServiceEcuM_Phase_UP:
            break;

         case E_ServiceEcuM_Phase_SLMCALEEP:
            //...
            ServiceEcuM_Context.ePhase = E_ServiceEcuM_Phase_UP;
            break;

         case E_ServiceEcuM_Phase_SHUTDOWN:
            GoDownHaltPoll();
            Shutdown();
            break;

         default:
            ServiceEcuM_Context.ePhase = E_ServiceEcuM_Phase_UNKNOWN;
            break;
      }
#if(STD_ON == ServiceDem_InitCheck)
   }
   else{
#if(STD_ON == ServiceDem_DevErrorDetect)
      ServiceDet_ReportError(
            0 //TBD: IdModule
         ,  0 //TBD: IdInstance
         ,  0 //TBD: IdApi
         ,  SERVICEECUM_E_UNINIT
      );
#endif
   }
#endif
}

#include "Const.hpp"
FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::InitFunction(
   void
){
   lptrConst = &Const.ConstServiceEcuM;
   lptrConst->ptrinfServiceSwcEcuM_ServiceEcuM->StartPreServiceOs();
   lptrConst->ptrinfServiceOs_ServiceEcuM->Start();
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::StartupTwo(
   void
){
   lptrConst->ptrinfServiceSwcEcuM_ServiceEcuM->StartPostServiceOs();
   ServiceEcuM_Context.ePhase = E_ServiceEcuM_Phase_UP;
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::ServiceDeterminePbConfiguration(
   void
){
}

FUNC(bool, SERVICEECUM_CODE) module_ServiceEcuM::GetPendingWakeupEvents(
   void
){
   return true;
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::GetValidatedWakeupEvents(
   void
){
   lptrConst->ptrinfMcalMcu_ServiceEcuM->GetResetReason();
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::LoopServiceDetection(
   void
){
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::SelectShutdownTarget(
   void
){
}

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

