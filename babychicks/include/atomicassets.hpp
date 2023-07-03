#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

using namespace eosio;

/**
 * @brief Namespace for the atomicassets contract
 * Copied from:
 https://github.com/pinknetworkx/atomicassets-contract/blob/master/include/atomicassets-interface.hpp#L173
 */
namespace atomicassets {
static constexpr name ATOMICASSETS_ACCOUNT = name("atomicassets");

// Custom vector types need to be defined because otherwise a bug in the ABI
// serialization would cause the ABI to be invalid
typedef std::vector<int8_t> INT8_VEC;
typedef std::vector<int16_t> INT16_VEC;
typedef std::vector<int32_t> INT32_VEC;
typedef std::vector<int64_t> INT64_VEC;
typedef std::vector<uint8_t> UINT8_VEC;
typedef std::vector<uint16_t> UINT16_VEC;
typedef std::vector<uint32_t> UINT32_VEC;
typedef std::vector<uint64_t> UINT64_VEC;
typedef std::vector<float> FLOAT_VEC;
typedef std::vector<double> DOUBLE_VEC;
typedef std::vector<std::string> STRING_VEC;

typedef std::variant<
    int8_t,
    int16_t,
    int32_t,
    int64_t,
    uint8_t,
    uint16_t,
    uint32_t,
    uint64_t,
    float,
    double,
    std::string,
    INT8_VEC,
    INT16_VEC,
    INT32_VEC,
    INT64_VEC,
    UINT8_VEC,
    UINT16_VEC,
    UINT32_VEC,
    UINT64_VEC,
    FLOAT_VEC,
    DOUBLE_VEC,
    STRING_VEC>
    ATOMIC_ATTRIBUTE;

typedef std::map<std::string, ATOMIC_ATTRIBUTE> ATTRIBUTE_MAP;
} // namespace atomicassets
