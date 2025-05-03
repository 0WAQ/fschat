project(GateServer)

add_executable(${PROJECT_NAME}
		"singleton.h"
		"ulti.h" "ulti.cpp"
		"GateServer.h" "GateServer.cpp"
		"CServer.h" "CServer.cpp"
		"HttpConnection.h" "HttpConnection.cpp"
		"LogicSystem.h" "LogicSystem.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${Boost_INCLUDES}
	${JSONCPP_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${Boost_LIBRARIES}
	${JSONCPP_LIBRARY_DIR}/${JSONCPP_LIBRARY}
)
