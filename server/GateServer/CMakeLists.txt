project(GateServer)

add_executable(${PROJECT_NAME}
		"AsioIOContextPool.h"			"AsioIOContextPool.cpp"
		"GateServer.h"					"GateServer.cpp"
		"GetVerifyCodeRpcClient.h"		"GetVerifyCodeRpcClient.cpp"
		"HttpConnection.h"				"HttpConnection.cpp"
		"LogicSystem.h"					"LogicSystem.cpp"

		"main.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE common)

# 拷贝 config.ini
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/config.ini
		$<TARGET_FILE_DIR:${PROJECT_NAME}>/config.ini
	COMMENT "Copying config.ini to build directory"
)