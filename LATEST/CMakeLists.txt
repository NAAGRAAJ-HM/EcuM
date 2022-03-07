add_library(
   BswAUTOSAR_Service_EcuM
   EcuM.cpp
)

include_directories(
   ../../common/LATEST
   ../../common/LATEST/Compiler_Abstraction_GNU/LATEST
   ../../SwcServiceEcuM/LATEST
   ../../SwcServiceOs/LATEST
   ../../BswAUTOSAR_McAL_Mcu/LATEST
   ../../BswAUTOSAR_Service_Os/LATEST
   ../../BswAUTOSAR_Service_StartUp/LATEST
   ../../BswAUTOSAR_Service_SchM/LATEST
)

