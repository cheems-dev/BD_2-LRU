#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

int main()
{
  // Número de frames en memoria
  int size = 4;

  // Cadena de referencia de páginas
  std::vector<char> reference_string = {'c', 'a', 'd', 'b', 'e', 'b', 'a', 'b', 'c', 'd'};

  // Lista para almacenar las páginas actuales en memoria
  std::list<char> pages;

  // Contadores de fallos y aciertos de página
  int faults = 0;
  int hits = 0;

  // Imprimir el estado actual de las páginas  de referencia
  std::cout << "Listado de paginas de referencia: ";
  for (char rf : reference_string)
  {
    std::cout << rf << " ";
  }
  std::cout << std::endl;

  // Iterar sobre la cadena de referencia de páginas
  for (char ref_page : reference_string)
  {
    // Buscar la página en la lista de páginas
    auto it = std::find(pages.begin(), pages.end(), ref_page);

    // Si la página ya está en la lista (hit)
    if (it != pages.end())
    {
      // Eliminar la página de su posición actual
      pages.erase(it);
      // Agregarla al final (más recientemente usada)
      pages.push_back(ref_page);
      // Incrementar los hits
      hits++;
    }
    // Si la página no está en la lista (fallo de página)
    else
    {
      // Incrementar los fallos de página
      faults++;

      // Si la memoria está llena
      if (pages.size() == size)
      {
        // Eliminar la página más antigua (al frente)
        pages.pop_front();
      }

      // Añadir la nueva página al final
      pages.push_back(ref_page);
    }

    // Imprimir el estado actual de las páginas en memoria
    std::cout << "Memoria actual: ";
    for (char page : pages)
    {
      std::cout << page << " ";
    }
    std::cout << std::endl;
  }

  // Mostrar el total de hits y fallos
  std::cout << "Total de Page Hits: " << hits << std::endl;
  std::cout << "Total de Page Faults: " << faults << std::endl;

  return 0;
}