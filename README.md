<h1>
  Path Finding and Data Structures
</h1>

This repository contains the implementation of the lowest-cost path search connecting the coordinates of two branches for order delivery using the A* algorithm. These branches will be stored in a binary search tree (BST), and their orders will be stored in a max heap to efficiently find the highest priority orders. Additionally, we decided to implement a minimum spanning tree (MST) that will connect the branches, with the weight of its edges representing the number of orders delivered between them.
<br>  <br/>
<div align="center">
    <img src="https://i.sstatic.net/1shiF.png" title="Graphical demonstration of the shortest path using A*"
       style="width: 35vw; height: auto;" />
</div>
<br>  <br/>
<div align="center">
    <img src="https://userscontent2.emaze.com/images/09933cdc-12a0-48e2-b3fb-1b2fe076a43e/e468e33d-8957-4713-917f-a0f459d81b8a.png" title="Graphical demonstration of a minimun spanning tree (MST)."
       style="width: 35vw; height: auto;" />
</div>
<br>  <br/>

 <h2> Contents: </h2>

- Description
- Documents
- Requirements
- Installation
- Contributors
- Usage
- Code Structure
- License

<h2> Description: </h2>

This project includes the implementation of fundamental data structures:

1. **A"*" Path finding**: Use of the A* algorithm for finding the shortest path on a predefined and scalable map.
2. **Binary Search Tree**: Implementation of a binary search tree that sorts the branches alphabetically to facilitate their search.
3. **Max Heap**: Use of a max heap for storing orders, primarily used to facilitate the search for the highest priority order.
4. **Minimun Spanning Tree**: Each graph represents a branch and its edges are the orders delivered between them, used in finding the most traveled path between the branches.

Each data structure is implemented as a class in C++, utilizing OOP principles to encapsulate data and behavior.

<h2> Documents </h2>

1. [ALGORITHMIC COMPLEXITY REPORT](https://docs.google.com/document/d/1hwWNvfIS35NLt1AiILlnDoYkv0icz2lv1zsoENiJqP8/edit?usp=sharing)
2. [PROGRAM DEMONSTRATION VIDEO](https://youtu.be/yYmCdmJCWj8?si=6FLtTx7sO4nx-9l8)


<h2> Requeriments: </h2>

- C++11 or higher
- A C++ compiler (e.g., g++, clang++)

<h2> Installation: </h2> 

1. Clone this repository to your local machine:
    ```bash
    git clone https://github.com/your-username/your-repo.git
    ```
2. Navigate to the project directory:
    ```bash
    cd your-repo
    ```
3. Compile the source files:
    ```bash
    g++ -I ./include -I ./include/a_estrella -I include/objetos_mapa -I include/aem -I include/minijuego -o test main.cpp src/.cpp src/a_estrella/.cpp src/objetos_mapa/* src/aem/* src/minijuego/*
    ./test
    ```
<h2> Contributors:</h2>

- Telmo Lautaro
- Aloisi Leandro
- Koziupa Matias
- Condori Hector 
- Santiago Fardini

 <h2> Usage: </h2>

Here is an example of how you can use the classes implemented in this project:

```cpp
#include "interfaz_de_usuario.hpp"

int main() {
    interfaz_de_usuario menu;
    menu.iniciar();
}
```

