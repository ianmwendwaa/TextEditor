# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TextEditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TextEditor_autogen.dir\\ParseCache.txt"
  "TextEditor_autogen"
  )
endif()
