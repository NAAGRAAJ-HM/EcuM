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

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

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
//TBD: static?
FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::GoDownHaltPoll(
   void
){
   ((NvM_BlocksRom_ServiceEcuM_Type*)lptrNvMBlocksRom)->ptrinfServiceSwcEcuM_ServiceEcuM->OffPreServiceOs(); // TBD: OOPS concepts
   ((NvM_BlocksRom_ServiceEcuM_Type*)lptrNvMBlocksRom)->ptrinfServiceOs_ServiceEcuM->Shutdown();
}

//TBD: static?
FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::Shutdown(
   void
){
   ((NvM_BlocksRom_ServiceEcuM_Type*)lptrNvMBlocksRom)->ptrinfServiceSwcEcuM_ServiceEcuM->OffPostServiceOs();
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
      CONSTP2CONST(ConstModule_TypeAbstract, SERVICEECUM_CONST,       SERVICEECUM_APPL_CONST) lptrNvMBlocksRomModule
   ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICEECUM_CONFIG_DATA, SERVICEECUM_APPL_CONST) lptrCfgModule
){
#if(STD_ON == ServiceDem_InitCheck)
   if(
         E_OK
      != IsInitDone
   ){
#endif
      if(
            (NULL_PTR != lptrNvMBlocksRomModule)
         && (NULL_PTR != lptrCfgModule)
      ){
         lptrNvMBlocksRom = lptrNvMBlocksRomModule;
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

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::InitFunction(
   void
){
   lptrNvMBlocksRom = &NvM_BlocksRom.NvM_BlocksRom_ServiceEcuM;
   ((NvM_BlocksRom_ServiceEcuM_Type*)lptrNvMBlocksRom)->ptrinfServiceSwcEcuM_ServiceEcuM->StartPreServiceOs();
   ((NvM_BlocksRom_ServiceEcuM_Type*)lptrNvMBlocksRom)->ptrinfServiceOs_ServiceEcuM->Start();
}

FUNC(void, SERVICEECUM_CODE) module_ServiceEcuM::StartupTwo(
   void
){
   ((NvM_BlocksRom_ServiceEcuM_Type*)lptrNvMBlocksRom)->ptrinfServiceSwcEcuM_ServiceEcuM->StartPostServiceOs();
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
   ((NvM_BlocksRom_ServiceEcuM_Type*)lptrNvMBlocksRom)->ptrinfMcalMcu_ServiceEcuM->GetResetReason();
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

