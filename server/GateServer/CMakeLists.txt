project(GateServer)

add_executable(${PROJECT_NAME}
		"singleton.h"
		"ulti.h" "ulti.cpp"
		"GateServer.h" "GateServer.cpp"
		"CServer.h" "CServer.cpp"
		"HttpConnection.h" "HttpConnection.cpp"
		"LogicSystem.h" "LogicSystem.cpp"
		"message.pb.h" "message.pb.cc"
		"message.grpc.pb.h" "message.grpc.pb.cc"
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${Boost_INCLUDES}
	${jsoncpp_INCLUDE_DIR}
	${gRPC_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	${Boost_LIBRARIES}
	${jsoncpp_LIBRARY_DIR}/libjsoncpp.a
	gRPC::grpc++
)
