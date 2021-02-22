# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\matrixCalculator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\matrixCalculator_autogen.dir\\ParseCache.txt"
  "matrixCalculator_autogen"
  )
endif()
