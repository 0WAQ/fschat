project(GateServer)

add_executable(${PROJECT_NAME}
		"main.cpp"
		"singleton.h"
		"ulti.h" "ulti.cpp"
		"GateServer.h" "GateServer.cpp"
		"HttpConnection.h" "HttpConnection.cpp"
		"LogicSystem.h" "LogicSystem.cpp"
		"message.pb.h" "message.pb.cc"
		"message.grpc.pb.h" "message.grpc.pb.cc"
		"message.proto"
		"GetVerifyCodeRpcClient.h" "GetVerifyCodeRpcClient.cpp"
		"ConfigManager.h" "ConfigManager.cpp"
		"AsioIOContextPool.h" "AsioIOContextPool.cpp"
		"RedisManager.h" "RedisManager.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${Boost_INCLUDES}
	${jsoncpp_INCLUDE_DIR}
	${gRPC_INCLUDE_DIR}
	${HIREDIS_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${Boost_LIBRARIES}
	${jsoncpp_LIBRARY_DIR}/libjsoncpp.a
	gRPC::grpc++
	${HIREDIS_LIBRARY_DIR}/libhiredis.a
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_CURRENT_SOURCE_DIR}/config.ini
	$<TARGET_FILE_DIR:${PROJECT_NAME}>/config.ini
	COMMENT "Copying config.ini to build directory"
)