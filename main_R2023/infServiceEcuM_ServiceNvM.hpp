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
#define CONSTSERVICEECUM_AR_RELEASE_VERSION_MAJOR                              4
#define CONSTSERVICEECUM_AR_RELEASE_VERSION_MINOR                              3

#define Const_DefaultInit_ConstServiceEcuM                                                                                     \
   ,  {                                                                                                                        \
            {CONSTSERVICEECUM_AR_RELEASE_VERSION_MAJOR, CONSTSERVICEECUM_AR_RELEASE_VERSION_MINOR, 0x00,0xFF,0x01,'0','1','0'} \
         ,  &McalMcu                                                                                                           \
         ,  &ServiceOs                                                                                                         \
         ,  &ServiceSwcEcuM                                                                                                    \
      }                                                                                                                        \

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/
#if(CONSTSERVICEECUM_AR_RELEASE_VERSION_MAJOR != STD_AR_RELEASE_VERSION_MAJOR)
   #error "Incompatible CFGSERVICEECUM_AR_RELEASE_VERSION_MAJOR!"
#endif

#if(CONSTSERVICEECUM_AR_RELEASE_VERSION_MINOR != STD_AR_RELEASE_VERSION_MINOR)
   #error "Incompatible CFGSERVICEECUM_AR_RELEASE_VERSION_MINOR!"
#endif

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/

