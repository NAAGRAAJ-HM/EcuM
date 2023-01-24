#pragma once
/******************************************************************************/
/* File   : infServiceEcuM_ServiceNvM_Types.hpp                               */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class ConstServiceEcuM_Type:
      public ConstModule_TypeAbstract
{
/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/
   public:
      infMcalMcu_ServiceEcuM*        ptrinfMcalMcu_ServiceEcuM;
      infServiceOs_ServiceEcuM*      ptrinfServiceOs_ServiceEcuM;
      infServiceSwcEcuM_ServiceEcuM* ptrinfServiceSwcEcuM_ServiceEcuM;
};

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

