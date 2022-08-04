#pragma once
/******************************************************************************/
/* File   : ServiceEcuM.hpp                                                          */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ConstServiceEcuM.hpp"
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
      INTERFACES_EXPORTED_ECUM
   ,  public abstract_module
   ,  public class_ServiceEcuM_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstServiceEcuM_Type* lptrConst = (ConstServiceEcuM_Type*)NULL_PTR;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, ECUM_CODE) InitFunction(
            CONSTP2CONST(ConstModule_TypeAbstract, ECUM_CONST,       ECUM_APPL_CONST) lptrConstModule
         ,  CONSTP2CONST(CfgModule_TypeAbstract,   ECUM_CONFIG_DATA, ECUM_APPL_CONST) lptrCfgModule
      );
      FUNC(void, ECUM_CODE) DeInitFunction           (void);
      FUNC(void, ECUM_CODE) MainFunction             (void);
      ECUM_CORE_FUNCTIONALITIES

      FUNC(void, ECUM_CODE) InitFunction             (void);
      FUNC(void, ECUM_CODE) StartupTwo               (void);
      FUNC(void, ECUM_CODE) ServiceDeterminePbConfiguration (void);
      FUNC(bool, ECUM_CODE) GetPendingWakeupEvents   (void);
      FUNC(void, ECUM_CODE) GetValidatedWakeupEvents (void);
      FUNC(void, ECUM_CODE) LoopServiceDetection            (void);
      FUNC(void, ECUM_CODE) SelectShutdownTarget     (void);
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
extern VAR(module_ServiceEcuM, ECUM_VAR) ServiceEcuM;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

