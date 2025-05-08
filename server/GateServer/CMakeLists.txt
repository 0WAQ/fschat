project(GateServer)

add_executable(${PROJECT_NAME}
		"base/singleton.h"
		"base/noncopyable.h"
		"base/ulti.h"					"base/ulti.cpp"
		"base/ConfigManager.h"			"base/ConfigManager.cpp"

		"redis/RedisManager.h"			"redis/RedisManager.cpp"
		"redis/RedisConnectionPool.h"	"redis/RedisConnectionPool.cpp"

		"rpc/message.pb.h"				"rpc/message.pb.cc"
		"rpc/message.grpc.pb.h"			"rpc/message.grpc.pb.cc"
		"rpc/message.proto"

		"AsioIOContextPool.h"			"AsioIOContextPool.cpp"
		"GateServer.h"					"GateServer.cpp"
		"GetVerifyCodeRpcClient.h"		"GetVerifyCodeRpcClient.cpp"
		"HttpConnection.h"				"HttpConnection.cpp"
		"LogicSystem.h"					"LogicSystem.cpp"

		"main.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${spdlog_INCLUDE_DIR}
	${Boost_INCLUDES}
	${jsoncpp_INCLUDE_DIR}
	${gRPC_INCLUDE_DIR}
	${HIREDIS_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	spdlog::spdlog
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