const config_module = require('./config')
const Redis = require('ioredis')

const RedisCli = new Redis({
    host: config_module.redis_host,
    port: config_module.redis_port,
    password: config_module.redis_pass,
});

/**
 * @brief 监听错误信息
 */
RedisCli.on("error", function(err) {
    console.log(`RedisCli connect error.`);
    RedisCli.quit();
});

async function getRedis(key) {
    try {
        const result = await RedisCli.get(key);
        if (result === null) {
            console.log(`getRedis: value is <${result}>. This key cannot be find...`);
            return null;
        }
        console.log(`getRedis: value is <${result}>. Get key success...`);
        return result;
    }
    catch (error) {
        console.log(`getRedis: error is <${error}>`);
        return null;
    }
}

async function queryRedis(key) {
    try {
        const result = await RedisCli.exists(key);
        if (result == 0) {
            console.log(`queryRedis: result is <${result}>. This key is null...`);
            return null;
        }
        console.log(`queryRedis: result is <${result}>. With this value...`);
        return result;
    }
    catch (error) {
        console.log(`queryRedis: error is ${error}`);
        return null;
    }
}

async function setRedisExpire(key, value, expire) {
    try {
        await RedisCli.set(key, value);
        await RedisCli.expire(key, expire)
        return true;
    }
    catch (error) {
        console.log(`setRedisExpire: error is ${error}`);
        return false;
    }
}

function quit() {
    RedisCli.quit();
}

module.exports = { getRedis, queryRedis, quit, setRedisExpire };
