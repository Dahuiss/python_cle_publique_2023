#include <iostream>
#include <string>
#include <vector>
#include "ecc.h"

class Key {
private:
    std::string private_key;
    std::string public_key;

public:
    void initialize(const std::string& number) {
        private_key = number;
        // Calculer la clé publique à partir de la clé privée
        std::vector<uint8_t> private_key_bytes = hex_to_bytes(private_key);
        std::vector<uint8_t> public_key_bytes = get_public_key(private_key_bytes);
        public_key = bytes_to_hex(public_key_bytes);
    }

    std::string getPrivateKey() const {
        return private_key;
    }

    std::string getPublicKey() const {
        return public_key;
    }
};

// Interface Python

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(composant_cle, m) {
py::class_<Key>(m, "cle")
.def(py::init<>())
.def("initialize", &Key::initialize)
.def("getPrivateKey", &Key::getPrivateKey)
.def("getPublicKey", &Key::getPublicKey);
}