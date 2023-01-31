#pragma once
/******************************************************************************/
/* File   : infServiceEcuM_ServiceNvM.hpp                                     */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "infMcalMcu_ServiceEcuM.hpp"
#include "infServiceOs_ServiceEcuM.hpp"
#include "infServiceSwcEcuM_ServiceEcuM.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/
#define NvM_InitBlocksRom_ServiceEcuM                                                                                \
   ,  {                                                                                                              \
            {SERVICEECUM_AR_RELEASE_VERSION_MAJOR, SERVICEECUM_AR_RELEASE_VERSION_MINOR, 0x00,0xFF,0x01,'0','1','0'} \
         ,  &McalMcu                                                                                                 \
         ,  &ServiceOs                                                                                               \
         ,  &ServiceSwcEcuM                                                                                          \
      }                                                                                                              \

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

