# Problema dos Leitores e Escritores — C++

Este projeto demonstra o clássico **Problema dos Leitores e Escritores** em programação concorrente, utilizando C++ moderno. Ele ilustra técnicas de sincronização eficientes, garantindo acesso simultâneo a leitores e exclusividade aos escritores.

## Descrição

- Múltiplos leitores podem acessar o recurso compartilhado ao mesmo tempo, desde que não haja escritor ativo.
- Escritores possuem acesso exclusivo ao recurso, bloqueando leitores e outros escritores.
- Sincronização implementada com `std::mutex` e `std::condition_variable`.
- Impressões no console são feitas via função `safe_print` para evitar mensagens embaralhadas entre threads.

## Bibliotecas Utilizadas

- `<iostream>`: Saída e impressão.
- `<thread>`: Criação e gerenciamento das threads (leitores e escritores).
- `<mutex>`: Exclusão mútua e sincronização.
- `<condition_variable>`: Controle do acesso condicional.
- `<chrono>`: Simulação de tempo nas operações de leitura e escrita.

## Estrutura

- Threads para leitores e escritores.
- Funções dedicadas para operação de leitura e escrita.
- Função de impressão sincronizada (`safe_print`).
- Controle de acesso ao recurso compartilhado através das primitivas de sincronização.

## Requisitos

- **C++11** ou superior (compatível com `std::mutex`, `std::condition_variable`).

## Compilação e Execução

```bash
g++ -std=c++11 -pthread main.cpp -o leitores_escritores
./leitores_escritores
```

## Exemplo de Execução

```
Leitor 1 está lendo...
Escritor 1 está escrevendo...
Leitor 2 está lendo...
...
```

## Autor

- Luciano Rovanni
- Data: 04/10/2025

---

Este projeto tem fins **educacionais** e demonstra técnicas de sincronização segura entre leitores e escritores usando threads em C++. Colabore ou sugira melhorias!
