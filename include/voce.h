#ifndef VOCE_H_
#define VOCE_H_
#include <ostream>
#include <string>

struct voce {
  std::string nome;
  std::string telefono;

  voce(std::string n, std::string tel) : nome(n), telefono(tel)
  {
    //
  }
};

std::ostream &operator<<(std::ostream &stream, const voce &voce) {
  stream << "[" << voce.nome << ": " << voce.telefono << "]";
  return stream;
};

#endif // VOCE_H_
