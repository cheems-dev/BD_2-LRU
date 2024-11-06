#include <iostream>
#include <vector>

struct Page
{
  char value;
  bool reference_bit;
};

class Clock
{
private:
  std::vector<Page> pages;
  int size;
  int hand;

public:
  Clock(int size) : size(size), hand(0)
  {
    pages.resize(size);
    for (int i = 0; i < size; i++)
    {
      pages[i].reference_bit = false; // Inicialmente, todos los bits de referencia están en 0
    }
  }

  void access_page(char page_value)
  {
    for (int i = 0; i < size; i++)
    {
      // Si la página ya está en memoria (hit)
      if (pages[i].value == page_value)
      {
        pages[i].reference_bit = true; // Se actualiza el bit de referencia
        std::cout << "Hit: " << page_value << std::endl;
        return;
      }
    }

    // Si no está en memoria (fallo de página)
    while (true)
    {
      // Verificar la página en la posición del puntero
      if (!pages[hand].reference_bit)
      {
        // Reemplazar la página
        pages[hand].value = page_value;
        pages[hand].reference_bit = true; // Se establece el bit de referencia
        hand = (hand + 1) % size;         // Mover el puntero hacia la siguiente posición
        std::cout << "Fault: " << page_value << " replaced in frame " << hand << std::endl;
        return;
      }
      else
      {
        // Restablecer el bit de referencia y mover el puntero
        pages[hand].reference_bit = false;
        hand = (hand + 1) % size;
      }
    }
  }

  void print_memory()
  {
    std::cout << "Current pages in memory: ";
    for (const auto &page : pages)
    {
      if (page.reference_bit)
      {
        std::cout << "[" << page.value << "] ";
      }
      else
      {
        std::cout << page.value << " ";
      }
    }
    std::cout << std::endl;
  }
};

int main()
{
  // Número de frames en memoria
  int size = 4;

  // Cadena de referencia de páginas
  std::vector<char> reference_string = {'c', 'a', 'd', 'b', 'e', 'b', 'a', 'b', 'c', 'd'};

  // Crear una instancia del algoritmo Clock
  Clock clock(size);

  // Imprimir el estado actual de las páginas de referencia
  std::cout << "Listado de paginas de referencia: ";
  for (char rf : reference_string)
  {
    std::cout << rf << " ";
  }
  std::cout << std::endl;

  // Iterar sobre la cadena de referencia de páginas
  for (char ref_page : reference_string)
  {
    clock.access_page(ref_page);
    clock.print_memory();
  }

  return 0;
}
