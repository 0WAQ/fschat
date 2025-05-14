project(common)

add_library(${PROJECT_NAME} STATIC
		"base/noncopyable.h"
		"base/singleton.h"
		"base/logger.h"
		"base/ulti.h"					"base/ulti.cpp"
		"base/ConfigManager.h"			"base/ConfigManager.cpp"

		"redis/RedisManager.h"			"redis/RedisManager.cpp"
		"redis/RedisConnectionPool.h"	"redis/RedisConnectionPool.cpp"

		"mysql/SqlConnection.h"			"mysql/SqlConnection.cpp"
		"mysql/SqlConnectionPool.h"		"mysql/SqlConnectionPool.cpp"
		"mysql/MysqlDAO.h"				"mysql/MysqlDAO.cpp"
		"mysql/MysqlManager.h"			"mysql/MysqlManager.cpp"

		"rpc/message.pb.h"				"rpc/message.pb.cc"
		"rpc/message.grpc.pb.h"			"rpc/message.grpc.pb.cc"
		"rpc/message.proto"
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${MYSQL_INCLUDE_DIRS}
	${HIREDIS_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
	spdlog::spdlog
	protobuf::libprotobuf
	gRPC::grpc++
	Boost::system Boost::thread Boost::filesystem
	OpenSSL::SSL OpenSSL::Crypto
	JsonCpp::JsonCpp
	${MYSQL_LIBRARY}
	${HIREDIS_LIBRARY}
)