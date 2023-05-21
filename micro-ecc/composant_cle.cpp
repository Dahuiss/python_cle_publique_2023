#include <iostream>
#include <string>
#include <vector>
#include "micro-ecc/uECC.h"

class Key {
private:
    std::vector<uint8_t> privateKey;
    std::vector<uint8_t> publicKey;

public:
    void initialize(const std::string& number) {
        privateKey.resize(32);
        publicKey.resize(65);

        for (int i = 0; i < 32; ++i) {
            sscanf(number.substr(i * 2, 2).c_str(), "%02hhx", &privateKey[i]);
        }

        uECC_compute_public_key(privateKey.data(), publicKey.data(), uECC_secp256k1());
    }

    std::string getPrivateKey() const {
        std::string result;
        for (const auto& byte : privateKey) {
            char buf[3];
            snprintf(buf, sizeof(buf), "%02x", byte);
            result += buf;
        }
        return result;
    }

    std::string getPublicKey() const {
        std::string result;
        for (const auto& byte : publicKey) {
            char buf[3];
            snprintf(buf, sizeof(buf), "%02x", byte);
            result += buf;
        }
        return result;
    }
};

// Interface Python

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "key.h"

namespace py = pybind11;

PYBIND11_MODULE(composant_cle, m) {
py::class_<Key>(m, "cle")
.def(py::init<>())
.def("initialize", &Key::initialize)
.def("getPrivateKey", &Key::getPrivateKey)
.def("getPublicKey", &Key::getPublicKey);
}
