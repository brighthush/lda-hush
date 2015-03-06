CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(gibbs-lda-cpp)

# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g" )
# set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")


# SET DIRECTORIES
set( PROJ_DIR ${CMAKE_SOURCE_DIR} )
set( SRC_DIR ${PROJ_DIR}/src)
set( RUN_DIR ${PROJ_DIR}/runtime )

# SET OUTPUT DIRECTORIES
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJ_DIR}/bin/lib )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJ_DIR}/bin/lib )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJ_DIR}/bin )

# MAIN PART
# main to train word to vector
add_executable( main ${SRC_DIR}/main.cpp ${SRC_DIR}/comm.cpp ${SRC_DIR}/GibbsLda.cpp )

# distance calculate the k nearest word to the input word
# add_executable( distance ${SRC_DIR}/distance.cpp ${SRC_DIR}/WordTable.cpp )

# analogy calculate word0 - word1 = word2 - x, get the list for x
# add_executable( analogy ${SRC_DIR}/analogy.cpp ${SRC_DIR}/WordTable.cpp )

# calculate precision for trained word vectors
# add_executable( measure ${SRC_DIR}/Measure.cpp ${SRC_DIR}/WordTable.cpp )

