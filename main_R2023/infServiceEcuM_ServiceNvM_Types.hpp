#pragma once
/******************************************************************************/
/* File   : infServiceEcuM_ServiceNvM_Types.hpp                               */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "infMcalMcu_ServiceEcuM.hpp"
#include "infServiceOs_ServiceEcuM.hpp"
#include "infServiceSwcEcuM_ServiceEcuM.hpp"

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class NvM_BlocksRom_ServiceEcuM_Type:
      public ConstModule_TypeAbstract
{
   public:
      infMcalMcu_ServiceEcuM*        ptrinfMcalMcu_ServiceEcuM;
      infServiceOs_ServiceEcuM*      ptrinfServiceOs_ServiceEcuM;
      infServiceSwcEcuM_ServiceEcuM* ptrinfServiceSwcEcuM_ServiceEcuM;
};

class NvM_BlocksNv_ServiceEcuM_Type:
      public CfgModule_TypeAbstract
{
};

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

