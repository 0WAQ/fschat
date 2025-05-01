# include_directories(${Boost_INCLUDE_DIRS})
# link_libraries(${Boost_LIBRARY_DIRS})

add_executable(GateServer "GateServer.h" "GateServer.cpp")

target_include_directories(GateServer PRIVATE
	${Boost_INCLUDES}
	${JSONCPP_INCLUDE_DIR}
)

target_link_libraries(GateServer PRIVATE
	${Boost_LIBRARIES}
	${JSONCPP_LIBRARY_DIR}/jsoncpp_static.lib
)
