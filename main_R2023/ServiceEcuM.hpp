#pragma once
/******************************************************************************/
/* File   : ServiceEcuM.hpp                                                   */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "infServiceEcuM_ServiceNvM_Types.hpp"
#include "CfgServiceEcuM.hpp"
#include "ServiceEcuM_core.hpp"
#include "infServiceEcuM_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_ServiceEcuM:
      INTERFACES_EXPORTED_SERVICEECUM
   ,  public abstract_module
   ,  public class_ServiceEcuM_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstModule_TypeAbstract* lptrNvMBlocksRom = (ConstModule_TypeAbstract*)NULL_PTR;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, SERVICEECUM_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, SERVICEECUM_CONST,       SERVICEECUM_APPL_CONST) lptrNvMBlocksRomModule
         ,  CONSTP2CONST(CfgModule_TypeAbstract,   SERVICEECUM_CONFIG_DATA, SERVICEECUM_APPL_CONST) lptrCfgModule
      );
      FUNC(void, SERVICEECUM_CODE) DeInitFunction           (void);
      FUNC(void, SERVICEECUM_CODE) MainFunction             (void);
      SERVICEECUM_CORE_FUNCTIONALITIES

      FUNC(void, SERVICEECUM_CODE) InitFunction             (void);
      FUNC(void, SERVICEECUM_CODE) StartupTwo               (void);
      FUNC(void, SERVICEECUM_CODE) ServiceDeterminePbConfiguration (void);
      FUNC(bool, SERVICEECUM_CODE) GetPendingWakeupEvents   (void);
      FUNC(void, SERVICEECUM_CODE) GetValidatedWakeupEvents (void);
      FUNC(void, SERVICEECUM_CODE) LoopServiceDetection            (void);
      FUNC(void, SERVICEECUM_CODE) SelectShutdownTarget     (void);
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
extern VAR(module_ServiceEcuM, SERVICEECUM_VAR) ServiceEcuM;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

