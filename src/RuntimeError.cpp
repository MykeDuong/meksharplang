#include "./include/RuntimeError.h"

RuntimeError::RuntimeError(const Token* token, const std::string& message) : std::runtime_error(message) {
  this->token = token;
}
