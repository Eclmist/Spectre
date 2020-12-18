#
#    This file is part of RTCore, an open-source physically based
#    renderer.
#   
#    Copyright (c) 2020-2021 Samuel Van Allen - All rights reserved.
#   
#    RTCore is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#   
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#   
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#   

# =========================================================================== #
#                        ADD SOURCE FILES TO PROJECT                          #
# =========================================================================== #

include_directories("googletest")

file(GLOB_RECURSE test_headers src/*.h)
file(GLOB_RECURSE test_cpps src/*.cpp)
set(all_files ${test_headers} ${test_cpps})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${all_files})

# =========================================================================== #
#                   SETUP THIRD PARTY/EXTERN DEPENDENCIES                     #
# =========================================================================== #

file(GLOB_RECURSE gtest googletest/*)
set(extern_files ${gtest})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${extern_files})

# =========================================================================== #
#                          SET COMPILATION TARGETS                            #
# =========================================================================== #

add_executable(UnitTests ${all_files} ${extern_files})
set_target_properties(UnitTests PROPERTIES RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}/bin/unittests>)

# =========================================================================== #
#                                LINK LIBRARIES                               #
# =========================================================================== #

target_link_libraries(UnitTests RTCore)

