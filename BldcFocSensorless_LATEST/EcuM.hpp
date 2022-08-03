#pragma once
/******************************************************************************/
/* File   : EcuM.hpp                                                          */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ConstEcuM.hpp"
#include "CfgEcuM.hpp"
#include "EcuM_core.hpp"
#include "infEcuM_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_EcuM:
      INTERFACES_EXPORTED_ECUM
   ,  public abstract_module
   ,  public class_EcuM_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstEcuM_Type* lptrConst = (ConstEcuM_Type*)NULL_PTR;

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
      FUNC(void, ECUM_CODE) DeterminePbConfiguration (void);
      FUNC(bool, ECUM_CODE) GetPendingWakeupEvents   (void);
      FUNC(void, ECUM_CODE) GetValidatedWakeupEvents (void);
      FUNC(void, ECUM_CODE) LoopDetection            (void);
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
extern VAR(module_EcuM, ECUM_VAR) EcuM;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

