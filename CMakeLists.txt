cmake_minimum_required(VERSION 3.9)
project(HPC_Project
	DESCRIPTION "Tarjan implementation with MPICH"
	VERSION 0.1
	LANGUAGES C
	)

enable_testing()

add_executable(program_seq_O3 src/main_seq.c src/Tarjan.c src/Grafo.c src/SCCNode.c src/NodeStack.c src/NodeArray.c src/SCCStack.c src/utils.c src/SCCArray.c src/Node.c src/TList.c src/TInfoList.c)
add_executable(program_par_O3 src/main_par.c src/Tarjan.c src/Grafo.c src/SCCNode.c src/NodeStack.c src/NodeArray.c src/SCCStack.c src/utils.c src/SCCArray.c src/Node.c src/TList.c src/TInfoList.c src/TArray.c)
add_executable(graph_generator_O3 src/graph_generator.c src/utils.c src/Grafo.c src/Node.c src/TList.c src/TInfoList.c)


target_include_directories(program_seq_O3 PRIVATE include)
target_include_directories(program_par_O3 PRIVATE include)
target_include_directories(graph_generator_O3 PRIVATE include)


find_package(MPI REQUIRED)
if(MPI_C_FOUND)
	message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
	target_link_libraries(program_par_O3 PUBLIC MPI::MPI_C)
endif()

target_compile_options(program_seq_O3 PRIVATE -O3)
target_compile_options(program_par_O3 PRIVATE -O3)
target_compile_options(graph_generator_O3 PRIVATE -O3)

target_compile_features(program_seq_O3 PRIVATE c_std_11)
target_compile_features(program_par_O3 PRIVATE c_std_11)
target_compile_features(graph_generator_O3 PRIVATE c_std_11)

# ---------------------------------------- TEST -----------------------------------------
# add_executable(test test/test.c src/utils.c)
# target_include_directories(mm_test PRIVATE include)

# add_test(NAME mm_test
# 	COMMAND mm_test )   


# ---------------------------------- GENERATE MEASURES ----------------------------------
add_custom_target(
	 generate_measures
	 COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/measures/measures.bash ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating measures [${CMAKE_CURRENT_SOURCE_DIR}/measures/measures.bash ${CMAKE_CURRENT_BINARY_DIR}]"
    DEPENDS	
        program_seq_O3
        program_par_O3
        graph_generator_O3
)



# --------------------------------- MEASURES EXTRACTION ---------------------------------
find_package(Python3 COMPONENTS Interpreter REQUIRED)
find_program(PipEnv pipenv REQUIRED)

add_custom_target(
	 install_pipenv
	 COMMAND PIPENV_PIPFILE=${CMAKE_CURRENT_SOURCE_DIR}/Pipfile ${PipEnv} install --ignore-pipfile
    COMMENT "Installing pipenv dependencies [${PipEnv} install]"
    DEPENDS	${CMAKE_CURRENT_SOURCE_DIR}/Pipfile.lock
)

add_custom_target(
    extract_measures
    COMMAND PIPENV_PIPFILE=${CMAKE_CURRENT_SOURCE_DIR}/Pipfile ${PipEnv} run python ${CMAKE_CURRENT_SOURCE_DIR}/measures/extract.py
    COMMENT "Generating version header [${PipEnv} run python ${CMAKE_CURRENT_SOURCE_DIR}/measures/extract.py]"
    DEPENDS	
		install_pipenv
		${CMAKE_CURRENT_SOURCE_DIR}/measures/extract.py
)