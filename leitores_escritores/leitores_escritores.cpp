/******************************************************************************
 * Problema dos Leitores e Escritores - C++
 *
 * Este programa implementa o problema clássico dos leitores e escritores, onde
 * múltiplos leitores podem acessar um recurso compartilhado simultaneamente,
 * desde que nenhum escritor esteja escrevendo. Escritores têm acesso exclusivo,
 * garantindo exclusão mútua contra leitores e outros escritores.
 *
 * A sincronização é realizada através de mutexes e condition_variable para
 * coordenar o acesso das threads. Para evitar impressões embaralhadas no console,
 * utiliza-se uma função de impressão segura (safe_print).
 *
 * Desenvolvido para fins educacionais e demonstração de técnicas de
 * sincronização de threads em C++ moderno.
 *
 * Autor: Luciano Rovanni
 * Data: 04/10/2025
 *****************************************************************************/

 /*
     ========================
     == BIBLIOTECAS UTILIZADAS
     ========================
 */

#include <iostream> //Para imprimir mensagens no console.
#include <thread> // Para criação e gerenciamento das threads.
#include <mutex>    // Para exclusão mútua e proteção das variáveis compartilhadas.
#include <condition_variable>   //  Para bloqueio e liberação condicional de threads.
#include <vector>   // Para armazenar e gerenciar as threads criadas dinamicamente.
#include <chrono>   //  Para simular o tempo da seção crítica com pausas temporizadas.
#include <windows.h> // Para corrigir acentuação no console do Windows.

 // ==============================================================================
 // Variáveis globais de sincronização
 // ==============================================================================

std::mutex mtx;                 // Protege acesso às variáveis compartilhadas
std::condition_variable cv;     // Para bloquear/desbloquear threads
int readers = 0;                // Número de leitores ativos
bool writer_active = false;     // Indica se há escritor ativo

std::mutex print_mtx;           // Protege impressões no console

// ==============================================================================
// Função auxiliar de impressão segura
// ==============================================================================

void safe_print(const std::string& msg) {
    std::lock_guard<std::mutex> lock(print_mtx);
    std::cout << msg << std::endl;
}

// ==============================================================================
// Função do leitor
// ==============================================================================

void reader(int id) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return !writer_active; });
        ++readers;
    }

    // --- Seção crítica de leitura ---
    safe_print("Leitor " + std::to_string(id) + " lendo");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    {
        std::unique_lock<std::mutex> lock(mtx);
        --readers;
        if (readers == 0) {
            cv.notify_all();
        }
    }
}

// ==============================================================================
// Função do escritor
// ==============================================================================

void writer(int id) {
    std::unique_lock<std::mutex> lock(mtx);

    cv.wait(lock, [] { return readers == 0 && !writer_active; });
    writer_active = true;

    // --- Seção crítica de escrita ---
    safe_print("Escritor " + std::to_string(id) + " escrevendo");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    writer_active = false;
    cv.notify_all();
}

// ==============================================================================
// Função principal
// ==============================================================================

int main() {
    SetConsoleOutputCP(CP_UTF8); // Corrige acentuação no Windows

    std::vector<std::thread> threads;

    // Cria threads de leitores
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(reader, i + 1);
    }

    // Cria threads de escritores
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(writer, i + 1);
    }

    // Aguarda todas as threads
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    safe_print("Execucao finalizada!");
    return 0;
}
