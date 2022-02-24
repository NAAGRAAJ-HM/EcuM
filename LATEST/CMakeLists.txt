add_library(
   BswAUTOSAR_Service_EcuM
   EcuM.cpp
)

include_directories(
   ../../BswAUTOSAR_McAL_Mcu/LATEST
   ../../BswAUTOSAR_Service_Os/LATEST
   ../../BswAUTOSAR_Service_SchM/LATEST
   ../../common/LATEST
   ../../common/LATEST/Compiler_Abstraction_GNU/LATEST
   ../../SwcServiceEcuM/LATEST
   ../../SwcServiceOs/LATEST
)

